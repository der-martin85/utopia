/*
 * field.h
 *
 *  Created on: 20.07.2010
 *      Author: Martin Ringwelski
 */

#ifndef MAP_H_
#define MAP_H_

#include "Field.h"
#include "SDL2/SDL_stdinc.h"

class Game;
#include "Game.h"

class Map {
public:
	enum oceans_t {
		OCEAN_NONE	= 0,
		OCEAN_NORTH	= 1,
		OCEAN_WEST	= 2,
		OCEAN_SOUTH	= 4,
		OCEAN_EAST	= 8
	};
	enum river_t {
		RIVER_NONE			= 0,
		RIVER_NORTHSOUTH	= 1,
		RIVER_EASTWEST		= 2
	};

	Map(int x, int y);
	Map(char* data, int length);
	~Map();
	void generateMap(Uint8 oceans, Uint8 river, Uint8 waterLevel);

	const Field* getField(int x, int y) const {
		return &(map[x][y]);
	}
	Field* getFieldForChange(int x, int y) {
		return &(map[x][y]);
	}
	bool loadMedia(SDL_Renderer* renderer);
	void renderMap(SDL_Renderer* renderer, Game* game, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void close();

	const int maxX;
	const int maxY;

private:
	bool checkLimit(int a, int max);
	void generateCoast(oceans_t ocean, int waterLevel);
	void generateRiver(river_t river, int waterLevel);

	SDL_Rect isoTo2D(int x, int y, Game* game);

	Field** map;

};

#endif /* MAP_H_ */
