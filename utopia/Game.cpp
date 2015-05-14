/*
 * Game.cpp
 *
 *  Created on: 20.07.2010
 *      Author: Martin Ringwelski
 */

#include "Game.h"

Game::Game(int x, int y, Settings* settings):
		evolutionLevel(0),
		speed(0),
		map(NULL),
		selected{-1, -1, -1, -1},
		mX(0), mY(0), oldMX(-1), oldMY(-1),
		posX(-16), posY(16),
		zoom(16),
		angle(0),
		buttonDown(false),
		rt(NULL),
		settings(settings)
{
	pthread_mutex_init(&mutex, NULL);
	map = new Map(x, y);
}

Game::~Game() {
}

void Game::setMouseState(int mX, int mY) {
	this->mX = mX;
	this->mY = mY;

	if (buttonDown) {
		if (mX < 150) {
			changePosX(-1);
		}
		if (mY < 50) {
			changePosY(+1);
		}
		if (mX > (settings->getScreenWidth() - 50)) {
			changePosX(+1);
		}
		if (mY > (settings->getScreenHeight() - 50)) {
			changePosY(-1);
		}
	}

	if (mX >= 100) {
		// On which field are we?
		int mrX = mX + ((posX + getMaxPosX()) * zoom * 2) - 100;
		int mrY = mY - (posY * zoom);
		int miX = (mrX - ((mrY - (zoom*3))*2) ) / (4 * zoom);
		int miY = ((mrX/2) + mrY - (zoom*3)) / (2 * zoom);

		switch (angle) {
		case 1: {
			if (miX >= map->maxY) miX = map->maxY-1;
			if (miX < 0) miX = 0;
			if (miY >= map->maxX) miY = map->maxX-1;
			if (miY < 0) miY = 0;
			int tmp = miY;
			miY = map->maxY - miX;
			miX = tmp;
			break; }
		case 2: {
			miX = map->maxX - miX;
			miY = map->maxY - miY;
			break; }
		case 3: {
			if (miX >= map->maxY) miX = map->maxY-1;
			if (miX < 0) miX = 0;
			if (miY >= map->maxX) miY = map->maxX-1;
			if (miY < 0) miY = 0;
			int tmp = miX;
			miX = map->maxX - miY;
			miY = tmp;
			break; }
		case 0:
		default: {
			break; }
		}

		if (miX >= map->maxX) miX = map->maxX-1;
		if (miY >= map->maxY) miY = map->maxY-1;
		if (miX < 0) miX = 0;
		if (miY < 0) miY = 0;
		selected[0] = miX;
		selected[1] = miY;
	}
}

void Game::changeZoom(int change) {
	int zoomOld = zoom;

	zoom += change;
	if (zoom < 3) {
		zoom = 3;
	}
	if (zoom > 64) {
		zoom = 64;
	}

	if (zoomOld != zoom) {
		posX += ((mX-100)/(2 * zoomOld)) - ((mX-100)/(2 * zoom));
		posY -= (mY/zoomOld) - (mY/zoom);

		correctPosX();
		correctPosY();
	}
}

void Game::changePosX(int change) {
	posX += change;
	correctPosX();
}

void Game::changePosY(int change) {
	posY += change;
	correctPosY();
}

void Game::startSelecting() {
	if (mX >= 100) {
		lock();
		buttonDown = true;
		if (selected[0] >= 0 &&
			   selected[1] >= 0 &&
			   selected[0] < map->maxX &&
			   selected[1] < map->maxY) {
		   selected[2] = selected[0];
		   selected[3] = selected[1];
		}
		unlock();
	}
}

void Game::doneSelecting() {
	lock();
	buttonDown = false;
	if (selected[2] > -1) {
	   const int minX = selected[0] > selected[2] ? selected[2] : selected[0];
	   const int minY = selected[1] > selected[3] ? selected[3] : selected[1];
	   const int maxX = selected[0] > selected[2] ? selected[0] : selected[2];
	   const int maxY = selected[1] > selected[3] ? selected[1] : selected[3];

	   for (int iX = minX; iX <= maxX; iX++) {
		   for (int iY = minY; iY <= maxY; iY++) {
			   map->getFieldForChange(iX, iY)->reset();
		   }
	   }

	   selected[2] = -1;
	   selected[3] = -1;
	}
	unlock();
}

void Game::startDragging() {
   oldMX = mX;
   oldMY = mY;
}

void Game::doneDragging() {
	if (oldMX != -1) {
		changePosX((oldMX - mX) / zoom);
		changePosY((mY - oldMY) / zoom);
	}
	oldMX = -1;
	oldMY = -1;
}

void Game::lock() {
	pthread_mutex_lock(&mutex);
}
void Game::unlock() {
	pthread_mutex_unlock(&mutex);
}

void Game::changeAngle(bool left) {
	int tmp = posX;
	if (left) {
		angle++;
		posX = posY - ((getMaxPosX() * 3)/zoom);
		posY = -tmp;
		if (angle > 3) {
			angle = 0;
		}
	} else {
		angle--;
		posX = -posY;
		posY = tmp + ((getMaxPosY() * 3)/zoom);
		if (angle < 0) {
			angle = 3;
		}
	}
	correctPosX();
	correctPosY();
}

Map* Game::getMap() {
	return map;
}

void Game::generateMap(Uint8 oceans, Uint8 river, Uint8 waterLevel) {
	map->generateMap(oceans, river, waterLevel);
}

int Game::getMaxPosX() {
	return (map->maxY + map->maxX) / 2;
}

int Game::getMaxPosY() {
	return (map->maxY + map->maxX) / 2;
}
