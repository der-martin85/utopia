/*
 * RenderThread.cpp
 *
 *  Created on: 04.05.2015
 *      Author: jentin
 */

#include "RenderThread.h"

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
    SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

RenderThread* RenderThread::startThread(int screenWidth, int screenHeight, Map* map) {
	RenderThread* ret = new RenderThread(screenWidth, screenHeight, map);
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
	t->map->loadMedia(t->renderer);

	do {

		SDL_RenderClear(t->renderer);
//		std::cout << "render" << std::endl;
		t->map->render(t->renderer, t->SCREEN_WIDTH, t->SCREEN_HEIGHT);
		SDL_RenderPresent(t->renderer);

		t->map->waitForChange();
	} while(!t->quit); //while(f->testAndDecrease());

//	std::cout << "done render" << std::endl;

	t->close();

	return 0;
}

RenderThread::RenderThread(int screenWidth, int screenHeight, Map* map):
		window(NULL), screenSurface(NULL), renderer(NULL),
		SCREEN_WIDTH(screenWidth),
		SCREEN_HEIGHT(screenHeight),
		map(map),
		thread(NULL)
{
}

RenderThread::~RenderThread() {
	SDL_WaitThread(thread, NULL);
}

