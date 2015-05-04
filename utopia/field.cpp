/*
 * field.cpp
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#include "field.h"
#include "SDL2/SDL_image.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Renderer * renderer = NULL;

//The image we will load and show on the screen
SDL_Surface* ground[6] = {NULL, NULL, NULL, NULL, NULL, NULL};

SDL_Surface* selected = NULL;

SDL_Texture* groundTextures[6] = {NULL,NULL,NULL,NULL, NULL, NULL};

SDL_Texture* selectedTexture = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

bool init() {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Create window
		gWindow = SDL_CreateWindow( "Utopia 3",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
			renderer = SDL_CreateRenderer(gWindow, 0, SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    //gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
    ground[0] = IMG_Load("./images/sand.png");
    ground[1] = IMG_Load("./images/gras.png");
    ground[2] = IMG_Load("./images/trees.png");
    ground[3] = IMG_Load("./images/forest.png");
    ground[4] = IMG_Load("./images/water0.png");
    ground[5] = IMG_Load("./images/water1.png");

    selected = IMG_Load("./images/selected.png");
    if(ground[0] == NULL )
    {
        printf( "Unable to load image");
        success = false;
    }

    for (int i = 0; i < 6; i++) {
    	groundTextures[i] = SDL_CreateTextureFromSurface(renderer, ground[i]);
    }

    selectedTexture = SDL_CreateTextureFromSurface(renderer, selected);;

    return success;
}

void close() {
    for (int i = 0; i < 4; i++) {
    	SDL_DestroyTexture(groundTextures[i]);
    	//Deallocate surface
    	SDL_FreeSurface(ground[i]);
    }
    SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

field::field(int x, int y):
		selected{-1, -1, -1, -1},
		fx(x), fy(y),
		mX(0), mY(0), oldMX(0), oldMY(0),
		posX((y + x)), posY(0),
		zoom(16),
		runs(0)
{
			//Start up SDL and create window
			if( !init() ) {
				printf( "Failed to initialize!\n" );
			} else {
				//Load media
				if( !loadMedia() ) {
					printf( "Failed to load media!\n" );
				}
			}
	pthread_mutex_init(&mutex, NULL);
	map = new int*[x];
	for (int i = 0; i < x; i++) {
		map[i] = new int[y];
	}
}
field::~field() {
	close();
	for (int i = 0; i < fx; i++) {
		delete[] map[fx];
	}
	delete[] map;
}
bool field::stillRunning() {
	bool ret = false;
	lock();
	if (runs > 0) {
		ret = true;
	}
	unlock();
	return ret;
}
void field::increaseRuns() {
	lock();
	if (runs < 2) {
		runs++;
	}
	unlock();
}
bool field::testAndDecrease() {
	bool ret = false;
	lock();
	if (runs > 0) {
		runs--;
	}
	if (runs > 0) {
		ret = true;
	}
	unlock();
	return ret;
}
void field::setMouseState() {
	   SDL_GetMouseState(&mX, &mY);
	   // Auf welchem Feld sind wir?
	   int mrX = mX + (posX * zoom);
	   int mrY = mY - (posY * zoom);
	   int miX = (mrX - ((mrY - (zoom*3))*2) ) / (4 * zoom);
	   int miY = ((mrX/2) + mrY - (zoom*3)) / (2 * zoom);

	   selected[0] = miX;
	   selected[1] = miY;
}
void field::render() {
	SDL_RenderClear(renderer);


	for (int y = 0; y < fy; y++) {
		for (int x = fx-1; x >= 0 ; x--) {
			SDL_Rect dstrect = isoTo2D(x, y);
			if (dstrect.x + dstrect.w > 0 && dstrect.y + dstrect.h > 0 &&
				   dstrect.x < SCREEN_WIDTH && dstrect.y < SCREEN_HEIGHT) {
				lock();
			   SDL_RenderCopy(renderer, groundTextures[map[x][y]], NULL, &dstrect);
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

	SDL_RenderPresent(renderer);
}

void field::changeZoom(int change) {
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

void field::changePosX(int change) {
	   posX += change;
	   if (posX < 0) {
		   posX = 0;
	   } else if (posX > (fy + fx)*2) {
		   posX = (fy + fx)*2;
	   }
}

void field::changePosY(int change) {
	   posY += change;
	   if (posY < -(fy + fx) / 2) {
		   posY = -(fy + fx) / 2;
	   } else if (posY > (fy + fx) / 2) {
		   posY = (fy + fx) / 2;
	   }
}

void field::startSelecting() {
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

void field::doneSelecting() {
   lock();
   if (selected[2] > -1) {
	   const int minX = selected[0] > selected[2] ? selected[2] : selected[0];
	   const int minY = selected[1] > selected[3] ? selected[3] : selected[1];
	   const int maxX = selected[0] > selected[2] ? selected[0] : selected[2];
	   const int maxY = selected[1] > selected[3] ? selected[1] : selected[3];

	   for (int iX = minX; iX <= maxX; iX++) {
		   for (int iY = minY; iY <= maxY; iY++) {
			   map[iX][iY] = 0;
		   }
	   }

	   selected[2] = -1;
	   selected[3] = -1;
   }
   unlock();
}

void field::startDragging() {
   oldMX = mX;
   oldMY = mY;
}

void field::doneDragging() {
   changePosX((oldMX - mX) / zoom);
   changePosY((mY - oldMY) / zoom);
}

void field::lock() {
	pthread_mutex_lock(&mutex);
}
void field::unlock() {
	pthread_mutex_unlock(&mutex);
}

void field::changeToFullScreen() {
	SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
}

void field::changeToWindow() {
	SDL_SetWindowFullscreen(gWindow, 0);
}

SDL_Rect field::isoTo2D(int x, int y) {
	SDL_Rect dstrect = {0, 0, zoom*4, zoom*4 };
	dstrect.x = (y + x)*2*zoom - posX*zoom;
	dstrect.y = (y - x)*zoom + posY*zoom;
	return dstrect;
}
