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
				settings->getScreenWidth(),
				settings->getScreenHeight(),
				SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Get renderer
			renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
}

void RenderThread::close() {
	game->getMap()->close();
	menu->close();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Destroy window
	if (window != NULL) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
}

RenderThread* RenderThread::startThread(Settings* settings, Game* game, Menu* menu) {
	RenderThread* ret = new RenderThread(settings, game, menu);
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
	t->game->getMap()->loadMedia(t->renderer);
	t->menu->loadMedia(t->renderer);

	pthread_mutex_lock(&(t->mutex));
	do {
		if (t->fullscreen != t->settings->isFullscreen()) {
			if (t->settings->isFullscreen()) {
				SDL_SetWindowFullscreen(t->window, SDL_WINDOW_FULLSCREEN);
				t->fullscreen = true;
			} else {
				SDL_SetWindowFullscreen(t->window, 0);
				t->fullscreen = false;
			}
		}
		pthread_mutex_unlock(&(t->mutex));

		SDL_RenderClear(t->renderer);
//		std::cout << "render" << std::endl;
		t->game->getMap()->renderMap(t->renderer, t->game, t->settings->getScreenWidth(), t->settings->getScreenHeight());
		t->menu->renderMenu(t->renderer, t->settings->getScreenHeight());

		SDL_RenderPresent(t->renderer);

		pthread_mutex_lock(&(t->mutex));
		if (!t->change) {
			pthread_cond_wait(&(t->refresh), &(t->mutex));
			t->change = false;
		}
	} while(!t->quit); //while(f->testAndDecrease());
	pthread_mutex_unlock(&(t->mutex));

//	std::cout << "done render" << std::endl;

	return 0;
}

RenderThread::RenderThread(Settings* settings, Game* game, Menu* menu):
		quit(false),
		fullscreen(false),
		settings(settings),
		window(NULL), renderer(NULL),
		game(game),
		menu(menu),
		thread(NULL),
		change(false)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&refresh, NULL);
}

RenderThread::~RenderThread() {
	quit = true;
	signalChange();
	SDL_WaitThread(thread, NULL);
	thread = NULL;
	close();
}
