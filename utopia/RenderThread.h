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
#include "Menu.h"
#include "SDL2/SDL.h"

class RenderThread {
public:
	~RenderThread();
	static RenderThread* startThread(int screenWidth, int screenHeight, Game* game, Menu* menu);
	void changeToFullScreen() {
		pthread_mutex_lock(&mutex);
		changeFullscreen = true;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&refresh);
	}

	void changeToWindow() {
		pthread_mutex_lock(&mutex);
		changeWindow = true;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&refresh);
	}
	void signalChange() {
		pthread_cond_signal(&refresh);
	}
private:
	bool init();
	void close();

	bool quit;
	bool changeFullscreen;
	bool changeWindow;
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	Game* game;
	Menu* menu;
	SDL_Thread* thread;
	pthread_mutex_t mutex;
	pthread_cond_t refresh;

	static int threadMethod(void* param);
	RenderThread(int screenWidth, int screenHeight, Game* game, Menu* menu);
};

#endif /* RENDERTHREAD_H_ */
