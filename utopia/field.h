/*
 * field.h
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#ifndef FIELD_H_
#define FIELD_H_

#include <pthread.h>
#include "SDL2/SDL.h"

class field {
public:
	field(int x, int y);
	~field();
	bool stillRunning();
	void increaseRuns();
	bool testAndDecrease();

	void setMouseState();

	void render();

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

	int** map;
	int selected[4];
	const int fx;
	const int fy;
private:
	SDL_Rect isoTo2D(int x, int y);

	Sint32 mX, mY, oldMX, oldMY;
	int posX;
	int posY;
	int zoom;
	unsigned int runs;
	pthread_mutex_t mutex;

};

#endif /* FIELD_H_ */
