/*
 * RenderThread.cpp
 *
 *  Created on: 04.05.2015
 *      Author: Martin Ringwelski
 */

#include "RenderThread.h"
#include "SDL2/SDL_image.h"

bool RenderThread::init() {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Create window
		window = SDL_CreateWindow( "Utopia 3",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );
			renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
}

void RenderThread::close() {
    for (int i = 0; i < 4; i++) {
    	SDL_DestroyTexture(groundTextures[i]);
    	//Deallocate surface
    	SDL_FreeSurface(groundIMG[i]);
    }

	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

bool RenderThread::loadMedia()
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


RenderThread* RenderThread::startThread(int screenWidth, int screenHeight, Game* game) {
	RenderThread* ret = new RenderThread(screenWidth, screenHeight, game);
	if (ret != NULL) {
		ret->thread = SDL_CreateThread(RenderThread::threadMethod, "RenderThread", (void *)(ret));
		if (ret->thread == NULL) {
			delete ret;
			return NULL;
		}
	}
	return ret;
}

int RenderThread::threadMethod(void* param) {
	RenderThread* t = (RenderThread*)param;

//	std::cout << "start render" << std::endl;

	t->init();
	t->loadMedia();

	do {

		pthread_mutex_lock(&(t->mutex));
		if (t->changeFullscreen) {
			SDL_SetWindowFullscreen(t->window, SDL_WINDOW_FULLSCREEN);
			t->changeFullscreen = false;
		} else if (t->changeWindow) {
			SDL_SetWindowFullscreen(t->window, 0);
			t->changeWindow = false;
		}
		pthread_mutex_unlock(&(t->mutex));

		SDL_RenderClear(t->renderer);
//		std::cout << "render" << std::endl;
		t->render();
		SDL_RenderPresent(t->renderer);

		t->game->waitForChange();
	} while(!t->quit); //while(f->testAndDecrease());

//	std::cout << "done render" << std::endl;

	t->close();

	return 0;
}

RenderThread::RenderThread(int screenWidth, int screenHeight, Game* game):
		quit(false),
		changeFullscreen(false),
		changeWindow(false),
		window(NULL), screenSurface(NULL), renderer(NULL),
		SCREEN_WIDTH(screenWidth),
		SCREEN_HEIGHT(screenHeight),
		game(game),
		thread(NULL)
{
	pthread_mutex_init(&mutex, NULL);
}

RenderThread::~RenderThread() {
	SDL_WaitThread(thread, NULL);
}

void RenderThread::render() {

	for (int y = 0; y < game->getMap()->maxY; y++) {
		for (int x = game->getMap()->maxX-1; x >= 0 ; x--) {
			SDL_Rect dstrect = isoTo2D(x, y);
			if (dstrect.x + dstrect.w > 0 && dstrect.y + dstrect.h > 0 &&
				   dstrect.x < SCREEN_WIDTH && dstrect.y < SCREEN_HEIGHT) {
				game->lock();
			   SDL_RenderCopy(renderer, groundTextures[game->getMap()->getField(x, y)->getTextureNumber()], NULL, &dstrect);
			   if ((((x >= game->getSelectedStartX() && x <= game->getSelectedEndX()) ||
							   (x <= game->getSelectedStartX() && x >= game->getSelectedEndX())) &&
					   ((y >= game->getSelectedStartY() && y <= game->getSelectedEndY()) ||
							   (y <= game->getSelectedStartY() && y >= game->getSelectedEndY())))) {
				   SDL_Rect sdstrect = {dstrect.x, dstrect.y+(dstrect.h/2),
						   (game->getZoom() * 4), (game->getZoom() * 2)};
				   SDL_RenderCopy(renderer, selectedTexture, NULL, &sdstrect);
			   }
			   game->unlock();
		   }
	   }
   }

}

SDL_Rect RenderThread::isoTo2D(int x, int y) {

	switch (game->getAngle()) {
	case 1: {
		int tmp = x;
		x = game->getMap()->maxY - y;
		y = tmp;
		break; }
	case 2: {
		x = game->getMap()->maxX - x;
		y = game->getMap()->maxY - y;
		break; }
	case 3: {
		int tmp = y;
		y = game->getMap()->maxX - x;
		x = tmp;
		break; }
	case 0:
	default: {
		break; }
	}

	SDL_Rect dstrect = {0, 0, (game->getZoom() * 4), (game->getZoom() * 4) };
	dstrect.x = (y + x - (game->getPosX() + game->getMaxPosX())) * 2 * game->getZoom();
	dstrect.y = (y - x + game->getPosY()) * game->getZoom();
	return dstrect;
}
