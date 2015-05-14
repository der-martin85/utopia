/*
 * RenderThread.h
 *
 *  Created on: 04.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RENDERTHREAD_H_
#define RENDERTHREAD_H_

class Game;
class Menu;

#include "Game.h"
#include "menu/Menu.h"
#include "SDL2/SDL.h"
#include "Settings.h"

class RenderThread {
public:
	~RenderThread();
	static RenderThread* startThread(Settings* settings, Game* game, Menu* menu);
	void signalChange() {
		pthread_mutex_lock(&mutex);
		change = true;
		pthread_cond_signal(&refresh);
		pthread_mutex_unlock(&mutex);
	}

private:
	bool init();
	void close();

	bool quit;
	bool fullscreen;
	Settings* settings;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Game* game;
	Menu* menu;
	SDL_Thread* thread;
	pthread_mutex_t mutex;
	pthread_cond_t refresh;
	bool change;

	static int threadMethod(void* param);
	RenderThread(Settings* settings, Game* game, Menu* menu);
};

#endif /* RENDERTHREAD_H_ */
