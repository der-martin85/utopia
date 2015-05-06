/*
 * field.h
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#ifndef MAP_H_
#define MAP_H_

#include "Field.h"

class Map {
public:
	Map(int x, int y);
	~Map();
	void generateMap();

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
