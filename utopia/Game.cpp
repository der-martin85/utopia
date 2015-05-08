/*
 * Game.cpp
 *
 *  Created on: 20.07.2010
 *      Author: Martin Ringwelski
 */

#include "Game.h"

Game::Game(int x, int y):
		evolutionLevel(0),
		speed(0),
		map(x, y),
		selected{-1, -1, -1, -1},
		mX(0), mY(0), oldMX(0), oldMY(0),
		posX(-16), posY(16),
		zoom(16),
		angle(0)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&refresh, NULL);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::setMouseState() {
	   SDL_GetMouseState(&mX, &mY);
	   // Auf welchem Feld sind wir?
	   int mrX = mX + ((posX + getMaxPosX()) * zoom * 2);
	   int mrY = mY - (posY * zoom);
	   int miX = (mrX - ((mrY - (zoom*3))*2) ) / (4 * zoom);
	   int miY = ((mrX/2) + mrY - (zoom*3)) / (2 * zoom);

	   switch (angle) {
		case 1: {
			if (miX >= map.maxY) miX = map.maxY-1;
			if (miX < 0) miX = 0;
			if (miY >= map.maxX) miY = map.maxX-1;
			if (miY < 0) miY = 0;
			int tmp = miY;
			miY = map.maxY - miX;
			miX = tmp;
			break; }
		case 2: {
			miX = map.maxX - miX;
			miY = map.maxY - miY;
			break; }
		case 3: {
			if (miX >= map.maxY) miX = map.maxY-1;
			if (miX < 0) miX = 0;
			if (miY >= map.maxX) miY = map.maxX-1;
			if (miY < 0) miY = 0;
			int tmp = miX;
			miX = map.maxX - miY;
			miY = tmp;
			break; }
		case 0:
		default: {
			break; }
	   }

	   if (miX >= map.maxX) miX = map.maxX-1;
	   if (miY >= map.maxY) miY = map.maxY-1;
	   if (miX < 0) miX = 0;
	   if (miY < 0) miY = 0;
	   selected[0] = miX;
	   selected[1] = miY;
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
	   posX += (mX/(2 * zoomOld)) - (mX/(2 * zoom));
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
   lock();
   if (selected[0] >= 0 &&
		   selected[1] >= 0 &&
		   selected[0] < map.maxX &&
		   selected[1] < map.maxY) {
	   selected[2] = selected[0];
	   selected[3] = selected[1];
   }
   unlock();
}

void Game::doneSelecting() {
   lock();
   if (selected[2] > -1) {
	   const int minX = selected[0] > selected[2] ? selected[2] : selected[0];
	   const int minY = selected[1] > selected[3] ? selected[3] : selected[1];
	   const int maxX = selected[0] > selected[2] ? selected[0] : selected[2];
	   const int maxY = selected[1] > selected[3] ? selected[1] : selected[3];

	   for (int iX = minX; iX <= maxX; iX++) {
		   for (int iY = minY; iY <= maxY; iY++) {
			   map.getFieldForChange(iX, iY)->reset();
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
   changePosX((oldMX - mX) / zoom);
   changePosY((mY - oldMY) / zoom);
}

void Game::lock() {
	pthread_mutex_lock(&mutex);
}
void Game::unlock() {
	pthread_mutex_unlock(&mutex);
}
void Game::waitForChange() {
	lock();
	pthread_cond_wait(&refresh, &mutex);
	unlock();
}
void Game::signalChange() {
	pthread_cond_signal(&refresh);
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
