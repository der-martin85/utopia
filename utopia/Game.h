/*
 * Game.h
 *
 *  Created on: 20.07.2010
 *      Author: Martin Ringwelski
 */

#ifndef GAME_H_
#define GAME_H_

#include <pthread.h>
#include <string>
#include "SDL2/SDL.h"

#include "GameDate.h"

#include "Settings.h"

class RenderThread;
#include "RenderThread.h"
class Map;
#include "Map.h"
#include "gui/Label.h"

class Game {
public:
	Game(int x, int y, Settings* settings);
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

	void loadGame(std::string fileName);
	void saveGame(std::string fileName);

	static Uint32 timeChange (Uint32 interval, void *param);

	bool loadMedia(SDL_Renderer* renderer);
	void close();
	void renderDate(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

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

	std::string cityName;
	std::string mayorName;

	unsigned int		evolutionLevel;
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
	Settings* settings;

	static TTF_Font *Font;
	static SDL_Color TextColor;
	Label*	dateLabel;
	SDL_TimerID timer;
};

#endif /* GAME_H_ */
