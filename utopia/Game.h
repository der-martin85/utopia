/*
 * Game.h
 *
 *  Created on: 20.07.2010
 *      Author: Martin Ringwelski
 */

#include <pthread.h>
#include "SDL2/SDL.h"

#include "GameDate.h"

#ifndef GAME_H_
#define GAME_H_

class RenderThread;
#include "RenderThread.h"
class Map;
#include "Map.h"

class Game {
public:
	Game(int x, int y);
	virtual ~Game();

	void setMouseState(int mX, int mY);

	void changeZoom(int change);
	void changeAngle(bool left);
	void changePosX(int change);
	void changePosY(int change);

	void startSelecting();
	void doneSelecting();

	void startDragging();
	void doneDragging();

	void lock();
	void unlock();

	Map* getMap();
	void generateMap(Uint8 oceans, Uint8 river, Uint8 waterLevel);
	int getSelectedStartX() const {
		return selected[0];
	}
	int getSelectedStartY() const {
		return selected[1];
	}
	int getSelectedEndX() const {
		if (selected[2] == -1) return selected[0];
		return selected[2];
	}
	int getSelectedEndY() const {
		if (selected[3] == -1) return selected[1];
		return selected[3];
	}
	int getAngle() const {
		return angle;
	}
	int getZoom() const {
		return zoom;
	}
	int getPosX() const {
		return posX;
	}
	int getPosY() const {
		return posY;
	}
	int getMaxPosX();
	int getMaxPosY();
	void setRenderThread(RenderThread* rt) {
		this->rt = rt;
	}


protected:
	void correctPosY() {
		   if (posY < -getMaxPosY()) {
			   posY = -getMaxPosY();
		   } else if (posY > getMaxPosY()) {
			   posY = getMaxPosY();
		   }
	}
	void correctPosX() {
		   if (posX < -getMaxPosX()) {
			   posX = -getMaxPosX();
		   } else if (posX > getMaxPosX()) {
			   posX = getMaxPosX();
		   }
	}

	int		evolutionLevel;
	unsigned int		speed;
	GameDate	actualDate;
	Map*		map;
	int selected[4];
	Sint32 mX, mY, oldMX, oldMY;
	int posX;
	int posY;
	int zoom;
	int angle;

	bool buttonDown;

	bool selectable;
	int selectionXSize, selectionYSize;

	pthread_mutex_t mutex;
	RenderThread* rt;
};

#endif /* GAME_H_ */
