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
	bool quit = false;
private:
	bool init();
	void close();

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	Map* map;
	SDL_Thread* thread;

	static int threadMethod(void* param);
	RenderThread(int screenWidth, int screenHeight, Map* map);
};

#endif /* RENDERTHREAD_H_ */
