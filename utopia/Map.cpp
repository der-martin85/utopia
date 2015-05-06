/*
 * field.cpp
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#include "Map.h"
#include <stdlib.h>
#include <time.h>

Map::Map(int x, int y):
		maxX(x), maxY(y)
{
	map = new Field*[x];
	for (int i = 0; i < x; i++) {
		map[i] = new Field[y];
	}
}
Map::~Map() {
	for (int i = 0; i < maxX; i++) {
		delete[] map[maxX];
	}
	delete[] map;
}

void Map::generateMap() {
    time_t t;
    time(&t);
    srand((unsigned int)t);

    const int probabilities[9] = {
    		3,
    		65,
    		30,
    		85,
    		30,
    		40,
    		30,
    		99,
			50
    };

    for (int s = 0; s < maxX && s < maxY; s++) {
    	if (s < maxX) {
    		int x = s;
			for (int y = s; y < maxY; y++) {
				int r = rand() % 100;
				int p = 0;
				if (y > 0) {
					if (x > 0) {
						if (y < (maxY-1)) {
							if (map[x][y-1].getType()) p += 1;
							if (map[x-1][y].getType()) p += 2;
							if (map[x-1][y+1].getType()) p += 4;
						} else {
							if (map[x][y-1].getType()) p += 1;
							if (map[x-1][y].getType()) p += 6;
						}
					} else {
						if (map[x][y-1].getType()) p += 7;
					}
				} else if (x > 0) {
					if (y < (maxY-1)) {
						if (map[x-1][y].getType()) p += 3;
						if (map[x-1][y+1].getType()) p += 4;
					} else {
						if (map[x-1][y].getType()) p += 7;
					}
				} else {
					p = 8;
				}
				map[x][y].setType(r < probabilities[p]);
			}
    	}
    	if (s < maxY) {
    		int y = s;
    		for (int x = s+1; x < maxX; x++) {
				int r = rand() % 100;
				int p = 0;
				if (x > 0) {
					if (y > 0) {
						if (x < (maxX-1)) {
							if (map[x-1][y].getType()) p += 1;
							if (map[x][y-1].getType()) p += 2;
							if (map[x+1][y-1].getType()) p += 4;
						} else {
							if (map[x-1][y].getType()) p += 1;
							if (map[x][y-1].getType()) p += 6;
						}
					} else {
						if (map[x-1][y].getType()) p += 7;
					}
				} else if (y > 0) {
					if (x < (maxX-1)) {
						if (map[x][y-1].getType()) p += 3;
						if (map[x+1][y-1].getType()) p += 4;
					} else {
						if (map[x][y-1].getType()) p += 7;
					}
				} else {
					p = 8;
				}
				map[x][y].setType(r < probabilities[p]);
    		}
    	}
    }
}
