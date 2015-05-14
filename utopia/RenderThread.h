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

class RenderThread {
public:
	~RenderThread();
	static RenderThread* startThread(int screenWidth, int screenHeight, Game* game, Menu* menu);
	void changeToFullScreen() {
		pthread_mutex_lock(&mutex);
		changeFullscreen = true;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&refresh);
		FullScreen = true;
	}

	void changeToWindow() {
		pthread_mutex_lock(&mutex);
		changeWindow = true;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&refresh);
		FullScreen = false;
	}
	void signalChange() {
		pthread_mutex_lock(&mutex);
		change = true;
		pthread_cond_signal(&refresh);
		pthread_mutex_unlock(&mutex);
	}

	int getScreenWidth() {
		return SCREEN_WIDTH;
	}
	int getScreenHeight() {
		return SCREEN_HEIGHT;
	}
	bool isFullscreen() {
		return FullScreen;
	}

private:
	bool init();
	void close();

	bool quit;
	bool changeFullscreen;
	bool changeWindow;
	bool FullScreen;
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	Game* game;
	Menu* menu;
	SDL_Thread* thread;
	pthread_mutex_t mutex;
	pthread_cond_t refresh;
	bool change;

	static int threadMethod(void* param);
	RenderThread(int screenWidth, int screenHeight, Game* game, Menu* menu);
};

#endif /* RENDERTHREAD_H_ */
