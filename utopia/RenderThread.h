/*
 * RenderThread.h
 *
 *  Created on: 04.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RENDERTHREAD_H_
#define RENDERTHREAD_H_

#include "Game.h"
#include "SDL2/SDL.h"

class RenderThread {
public:
	~RenderThread();
	static RenderThread* startThread(int screenWidth, int screenHeight, Game* game);
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
	bool loadMedia();
	void close();
	void render();
	SDL_Rect isoTo2D(int x, int y);

	bool changeFullscreen;
	bool changeWindow;
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	Game* game;
	SDL_Thread* thread;
	pthread_mutex_t mutex;

	SDL_Texture* groundTextures[4] = {NULL,NULL,NULL,NULL};

	SDL_Texture* treesTextures[4] = {NULL,NULL,NULL,NULL};

	SDL_Texture* stoneTextures[3] = {NULL,NULL,NULL};

	SDL_Texture* goldTextures[3] = {NULL,NULL,NULL};

	SDL_Texture* selectedTexture = NULL;

	static int threadMethod(void* param);
	RenderThread(int screenWidth, int screenHeight, Game* game);
};

#endif /* RENDERTHREAD_H_ */
