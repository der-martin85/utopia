/*
 * game.h
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#include "Map.h"
#include <pthread.h>
#include "SDL2/SDL.h"

#include "GameDate.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game(int x, int y);
	virtual ~Game();

	void setMouseState();

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

	void waitForChange();
	void signalChange();

	const Map* getMap() const {
		return &map;
	}
	void generateMap() {
		map.generateMap();
	}
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


protected:
	void correctPosY() {
		   if (posY < -getMaxY()) {
			   posY = -getMaxY();
		   } else if (posY > getMaxY()) {
			   posY = getMaxY();
		   }
	}
	void correctPosX() {
		   if (posX < 0) {
			   posX = 0;
		   } else if (posX > getMaxX()) {
			   posX = getMaxX();
		   }
	}
	int getMaxX() {
		return (map.maxY + map.maxX)*2;
	}
	int getMaxY() {
		return (map.maxY + map.maxX) / 2;
	}

	int		evolutionLevel;
	unsigned int		speed;
	GameDate	actualDate;
	Map		map;
	int selected[4];
	Sint32 mX, mY, oldMX, oldMY;
	int posX;
	int posY;
	int zoom;
	int angle;
	pthread_mutex_t mutex;
	pthread_cond_t refresh;
};

#endif /* GAME_H_ */
