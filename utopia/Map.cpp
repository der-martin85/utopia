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

	for (int x = 0; x < fx; x++) {
        for (int y = 0; y < fy; y++) {
//        	if (x > 0) {
//        		if (y > 0) {
//        			if (x < (fieldx-1)) {
//        				field[x][y] = getField(field[x-1][y], field[x][y-1], field[x+1][y-1], field[x-1][y-1]);
//        			} else {
//        				field[x][y] = getField(field[x-1][y], field[x][y-1], field[x][y-1], field[x-1][y-1]);
//        			}
//        		} else {
//       				field[x][y] = getField(field[x-1][y], field[x-1][y], field[x-1][y], field[x-1][y]);
//        		}
//        	} else if (y > 0) {
//    			if (x < (fieldx-1)) {
//    				field[x][y] = getField(field[x][y-1], field[x][y-1], field[x+1][y-1], field[x][y-1]);
//    			} else {
//    				field[x][y] = getField(field[x][y-1], field[x][y-1], field[x][y-1], field[x][y-1]);
//    			}
//    		} else {
        		map[x][y].setType((bool)(rand() % 2));
//    		}
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

	   if (posX < 0) {
		   posX = 0;
	   } else if (posX > (fy + fx)*2) {
		   posX = (fy + fx)*2;
	   }
	   if (posY < -(fy + fx) / 2) {
		   posY = -(fy + fx) / 2;
	   } else if (posY > (fy + fx) / 2) {
		   posY = (fy + fx) / 2;
	   }
   }
}

void Map::changePosX(int change) {
	   posX += change;
	   if (posX < 0) {
		   posX = 0;
	   } else if (posX > (fy + fx)*2) {
		   posX = (fy + fx)*2;
	   }
}

void Map::changePosY(int change) {
	   posY += change;
	   if (posY < -(fy + fx) / 2) {
		   posY = -(fy + fx) / 2;
	   } else if (posY > (fy + fx) / 2) {
		   posY = (fy + fx) / 2;
	   }
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

void Map::changeToFullScreen() {
//	SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
}

void Map::changeToWindow() {
//	SDL_SetWindowFullscreen(gWindow, 0);
}

SDL_Rect Map::isoTo2D(int x, int y) {
	SDL_Rect dstrect = {0, 0, zoom*4, zoom*4 };
	dstrect.x = (y + x)*2*zoom - posX*zoom;
	dstrect.y = (y - x)*zoom + posY*zoom;
	return dstrect;
}
