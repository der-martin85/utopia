/*
 * RenderThread.h
 *
 *  Created on: 04.05.2015
 *      Author: jentin
 */

#ifndef RENDERTHREAD_H_
#define RENDERTHREAD_H_

#include "Map.h"
#include "SDL2/SDL.h"

class RenderThread {
public:
	~RenderThread();
	static RenderThread* startThread(int screenWidth, int screenHeight, Map* map);
	void changeToFullScreen() {
		pthread_mutex_lock(&mutex);
		changeFullscreen = true;
		pthread_mutex_unlock(&mutex);
	}

	void changeToWindow() {
		pthread_mutex_lock(&mutex);
		changeWindow = true;
		pthread_mutex_unlock(&mutex);
	}
	bool quit;
private:
	bool init();
	void close();

	bool changeFullscreen;
	bool changeWindow;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	Map* map;
	SDL_Thread* thread;
	pthread_mutex_t mutex;

	static int threadMethod(void* param);
	RenderThread(int screenWidth, int screenHeight, Map* map);
};

#endif /* RENDERTHREAD_H_ */
