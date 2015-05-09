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

	const int maxX;
	const int maxY;

private:

	Field** map;

};

#endif /* MAP_H_ */
