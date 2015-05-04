/*
 * field.h
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#ifndef MAP_H_
#define MAP_H_

#include <pthread.h>
#include "SDL2/SDL.h"
#include "Field.h"

class Map {
public:
	Map(int x, int y);
	~Map();
	void generateMap();

	bool loadMedia(SDL_Renderer * renderer);

	void setMouseState();

	void render(SDL_Renderer * renderer, int screenWidth, int screenHeight);

	void changeZoom(int change);
	void changePosX(int change);
	void changePosY(int change);

	void startSelecting();
	void doneSelecting();

	void startDragging();
	void doneDragging();

	void lock();
	void unlock();

	void changeToFullScreen();
	void changeToWindow();

	void waitForChange();
	void signalChange();

	const int fx;
	const int fy;

private:
	SDL_Rect isoTo2D(int x, int y);

	Field** map;
	int selected[4];
	Sint32 mX, mY, oldMX, oldMY;
	int posX;
	int posY;
	int zoom;
	pthread_mutex_t mutex;
	pthread_cond_t refresh;

	SDL_Surface* groundIMG[6] = {NULL, NULL, NULL, NULL, NULL, NULL};

	SDL_Surface* selectedIMG = NULL;

	SDL_Texture* groundTextures[6] = {NULL,NULL,NULL,NULL, NULL, NULL};

	SDL_Texture* selectedTexture = NULL;

};

#endif /* MAP_H_ */
