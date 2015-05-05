/*
 * field.cpp
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#include "Map.h"

#include "SDL2/SDL_image.h"

bool Map::loadMedia(SDL_Renderer * renderer)
{
    //Loading success flag
    bool success = true;

    //Load splash image
    //gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
    groundIMG[0] = IMG_Load("./images/sand.png");
    groundIMG[1] = IMG_Load("./images/gras.png");
    groundIMG[2] = IMG_Load("./images/trees.png");
    groundIMG[3] = IMG_Load("./images/forest.png");
    groundIMG[4] = IMG_Load("./images/water0.png");
    groundIMG[5] = IMG_Load("./images/water1.png");

    selectedIMG = IMG_Load("./images/selected.png");
    if(groundIMG[0] == NULL )
    {
        printf( "Unable to load image");
        success = false;
    }

    for (int i = 0; i < 6; i++) {
    	groundTextures[i] = SDL_CreateTextureFromSurface(renderer, groundIMG[i]);
    }

    selectedTexture = SDL_CreateTextureFromSurface(renderer, selectedIMG);

    return success;
}


Map::Map(int x, int y):
		fx(x), fy(y),
		selected{-1, -1, -1, -1},
		mX(0), mY(0), oldMX(0), oldMY(0),
		posX((y + x)), posY(0),
		zoom(16)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&refresh, NULL);
	map = new Field*[x];
	for (int i = 0; i < x; i++) {
		map[i] = new Field[y];
	}
}
Map::~Map() {
    for (int i = 0; i < 4; i++) {
    	SDL_DestroyTexture(groundTextures[i]);
    	//Deallocate surface
    	SDL_FreeSurface(groundIMG[i]);
    }

	for (int i = 0; i < fx; i++) {
		delete[] map[fx];
	}
	delete[] map;
}

void Map::generateMap() {
    time_t t;
    time(&t);
    srand((unsigned int)t);              /* Zufallsgenerator initialisieren */

    const int probabilities[17] = {
    		90,
			99,
			70,
			100,
			60,
			80,
			40,
			30,
			60,
			50,
			20,
			1,
			1,
			50,
			1,
			90,
			50
    };

	for (int x = 0; x < fx; x++) {
        for (int y = 0; y < fy; y++) {
        	int r = rand() % 100;
			int p = 0;
        	if (x > 0) {
        		if (y > 0) {
        			if (x < (fx-1)) {
        				if (map[x-1][y].getType()) p += 1;
        				if (map[x][y-1].getType()) p += 2;
        				if (map[x+1][y-1].getType()) p += 4;
        				if (map[x-1][y-1].getType()) p += 8;
        			} else {
        				if (map[x-1][y].getType()) p += 1;
        				if (map[x][y-1].getType()) p += 6;
        				if (map[x-1][y-1].getType()) p += 8;
        			}
        		} else {
        			if (map[x-1][y].getType()) p += 15;
        		}
        	} else if (y > 0) {
    			if (x < (fx-1)) {
    				if (map[x][y-1].getType()) p += 2;
    				if (map[x+1][y-1].getType()) p += 4;
    			} else {
    				if (map[x][y-1].getType()) p += 15;
    			}
    		} else {
    			p = 16;
    		}
    		map[x][y].setType(r < probabilities[p]);
        }
    }
}

void Map::setMouseState() {
	   SDL_GetMouseState(&mX, &mY);
	   // Auf welchem Feld sind wir?
	   int mrX = mX + (posX * zoom);
	   int mrY = mY - (posY * zoom);
	   int miX = (mrX - ((mrY - (zoom*3))*2) ) / (4 * zoom);
	   int miY = ((mrX/2) + mrY - (zoom*3)) / (2 * zoom);

	   switch (angle) {
		case 1: {
			if (miX >= fy) miX = fy-1;
			if (miX < 0) miX = 0;
			if (miY >= fx) miY = fx-1;
			if (miY < 0) miY = 0;
			int tmp = miY;
			miY = fy - miX;
			miX = tmp;
			break; }
		case 2: {
			miX = fx - miX;
			miY = fy - miY;
			break; }
		case 3: {
			if (miX >= fy) miX = fy-1;
			if (miX < 0) miX = 0;
			if (miY >= fx) miY = fx-1;
			if (miY < 0) miY = 0;
			int tmp = miX;
			miX = fx - miY;
			miY = tmp;
			break; }
		case 0:
		default: {
			break; }
	   }

	   if (miX >= fx) miX = fx-1;
	   if (miY >= fy) miY = fy-1;
	   if (miX < 0) miX = 0;
	   if (miY < 0) miY = 0;
	   selected[0] = miX;
	   selected[1] = miY;
}
void Map::render(SDL_Renderer * renderer, int screenWidth, int screenHeight) {

	for (int y = 0; y < fy; y++) {
		for (int x = fx-1; x >= 0 ; x--) {
			SDL_Rect dstrect = isoTo2D(x, y);
			if (dstrect.x + dstrect.w > 0 && dstrect.y + dstrect.h > 0 &&
				   dstrect.x < screenWidth && dstrect.y < screenHeight) {
				lock();
			   SDL_RenderCopy(renderer, groundTextures[map[x][y].getTextureNumber()], NULL, &dstrect);
			   if (((selected[2] > -1) &&
					   ((x >= selected[0] && x <= selected[2]) ||
							   (x <= selected[0] && x >= selected[2])) &&
					   ((y >= selected[1] && y <= selected[3]) ||
							   (y <= selected[1] && y >= selected[3]))) ||
					   (x == selected[0] && y == selected[1])) {
				   SDL_Rect sdstrect = {dstrect.x, dstrect.y+(dstrect.h/2), zoom*4, zoom*2 };
				   SDL_RenderCopy(renderer, selectedTexture, NULL, &sdstrect);
			   }
			   unlock();
		   }
	   }
   }

}

void Map::changeZoom(int change) {
   int zoomOld = zoom;

   zoom += change;
   if (zoom < 4) {
	   zoom = 4;
   }
   if (zoom > 32) {
	   zoom = 32;
   }

   if (zoomOld != zoom) {
	   posX += (mX/zoomOld) - (mX/zoom);
	   posY -= (mY/zoomOld) - (mY/zoom);

	   correctPosX();
	   correctPosY();
   }
}

void Map::changePosX(int change) {
	   posX += change;
	   correctPosX();
}

void Map::changePosY(int change) {
	   posY += change;
	   correctPosY();
}

void Map::startSelecting() {
   lock();
   if (selected[0] >= 0 &&
		   selected[1] >= 0 &&
		   selected[0] < fx &&
		   selected[1] < fy) {
	   selected[2] = selected[0];
	   selected[3] = selected[1];
   }
   unlock();
}

void Map::doneSelecting() {
   lock();
   if (selected[2] > -1) {
	   const int minX = selected[0] > selected[2] ? selected[2] : selected[0];
	   const int minY = selected[1] > selected[3] ? selected[3] : selected[1];
	   const int maxX = selected[0] > selected[2] ? selected[0] : selected[2];
	   const int maxY = selected[1] > selected[3] ? selected[1] : selected[3];

	   for (int iX = minX; iX <= maxX; iX++) {
		   for (int iY = minY; iY <= maxY; iY++) {
			   map[iX][iY].setType(true);
		   }
	   }

	   selected[2] = -1;
	   selected[3] = -1;
   }
   unlock();
}

void Map::startDragging() {
   oldMX = mX;
   oldMY = mY;
}

void Map::doneDragging() {
   changePosX((oldMX - mX) / zoom);
   changePosY((mY - oldMY) / zoom);
}

void Map::lock() {
	pthread_mutex_lock(&mutex);
}
void Map::unlock() {
	pthread_mutex_unlock(&mutex);
}
void Map::waitForChange() {
	lock();
	pthread_cond_wait(&refresh, &mutex);
	unlock();
}
void Map::signalChange() {
	pthread_cond_signal(&refresh);
}

void Map::changeAngle(bool left) {
	if (left) {
		angle++;
		int tmp = posX;
		posX = (posY*2 + (fy + fx));
		posY = -((tmp/2) - (fy + fx));
		correctPosX();
		correctPosY();
		if (angle > 3) {
			angle = 0;
		}
	} else {
		angle--;
		int tmp = posX;
		posX = (2*(fy + fx))-(posY*2 + (fy + fx));
		posY = ((tmp/2) - (fy + fx));
		if (angle < 0) {
			angle = 3;
		}
	}
}

SDL_Rect Map::isoTo2D(int x, int y) {

	switch (angle) {
	case 1: {
		int tmp = x;
		x = fy - y;
		y = tmp;
		break; }
	case 2: {
		x = fx - x;
		y = fy - y;
		break; }
	case 3: {
		int tmp = y;
		y = fx - x;
		x = tmp;
		break; }
	case 0:
	default: {
		break; }
	}

	SDL_Rect dstrect = {0, 0, zoom*4, zoom*4 };
	dstrect.x = (y + x)*2*zoom - posX*zoom;
	dstrect.y = (y - x)*zoom + posY*zoom;
	return dstrect;
}
