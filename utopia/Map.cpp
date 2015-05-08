/*
 * field.cpp
 *
 *  Created on: 20.07.2010
 *      Author: Martin Ringwelski
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

void Map::generateMap(Uint8 oceans, river_t river, Uint8 waterLevel) {
    time_t t;
    time(&t);
    srand((unsigned int)t);

    for (int x = 0; x < maxX; x++) {
    	for (int y = 0; y < maxY; y++) {
    		map[x][y].reset();
    	}
    }

    // Create Coasts

	if (oceans & OCEAN_NORTH) {
    	for (int y = 0; y < maxY; y++) {
    		for (int x = 0; x < maxX; x++) {
	    		if (y == 0) {
	    			map[x][y].setType(false);
	    		} else if (!(map[x][y-1].getType())) {
					int r = rand() % 100;
					if ((x == (maxX - 1) || !(map[x+1][y-1].getType())) &&
							((x == 0) || !(map[x-1][y-1].getType())))
					{
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
					} else {
						if (r < waterLevel / 3) {
							map[x][y].setType(false);
						}
					}
	    		}
	    	}
	    }
	}
	if (oceans & OCEAN_WEST) {
	    for (int x = 0; x < maxX; x++) {
	    	for (int y = 0; y < maxY; y++) {
	    		if (x == 0) {
	    			map[x][y].setType(false);
	    		} else if (!(map[x-1][y].getType())) {
					int r = rand() % 100;
					if ((y == (maxY - 1) || !(map[x-1][y+1].getType())) &&
							((y == 0) || !(map[x-1][y-1].getType())))
					{
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
					} else {
						if (r < waterLevel / 3) {
							map[x][y].setType(false);
						}
					}
	    		}
	    	}
	    }
	}
	if (oceans & OCEAN_SOUTH) {
		for (int y = (maxY - 1); y >= 0; y--) {
			for (int x = 0; x < maxX; x++) {
	    		if (y == (maxY - 1)) {
	    			map[x][y].setType(false);
	    		} else if (!(map[x][y+1].getType())) {
					int r = rand() % 100;
					if ((x == (maxX - 1) || !(map[x+1][y+1].getType())) &&
							((x == 0) || !(map[x-1][y+1].getType())))
					{
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
					} else {
						if (r < waterLevel / 3) {
							map[x][y].setType(false);
						}
					}
	    		}
	    	}
	    }
	}
	if (oceans & OCEAN_EAST) {
	    for (int x = (maxX - 1); x >= 0; x--) {
	    	for (int y = 0; y < maxY; y++) {
	    		if (x == (maxX - 1)) {
	    			map[x][y].setType(false);
	    		} else if (!(map[x+1][y].getType())) {
					int r = rand() % 100;
					if ((y == (maxY - 1) || !(map[x+1][y+1].getType())) &&
							((y == 0) || !(map[x+1][y-1].getType())))
					{
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
					} else {
						if (r < waterLevel / 3) {
							map[x][y].setType(false);
						}
					}
	    		}
	    	}
	    }
	}

	// Create River

    if (river == RIVER_EASTWEST) {
    	int middle = (rand() %( maxX/3)) + (rand() %( maxX/3)) + (rand() %( maxX/3));
    	int oldspana, oldspanb;
    	for (int y = 0; y < maxY; y++) {
			int spana = 1;
			for (int i = 0; i < 4; i++ ) {
				spana += (rand() % ((maxX*waterLevel)/2400));
			}
			int spanb = 1;
			for (int i = 0; i < 4; i++ ) {
				spanb += (rand() % ((maxX*waterLevel)/2400));
			}
    		if (y == 0) {
    			for (int x = middle; x < maxX && x < (middle + spana); x++) {
        			map[x][y].setType(false);
    			}
    			for (int x = middle; x >= 0 && x >= (middle - spanb); x--) {
        			map[x][y].setType(false);
    			}
    		} else {
    			spana = (spana + oldspana) / 2;
    			spanb = (spanb + oldspanb) / 2;
    			for (int x = middle; x < maxX && x < (middle + spana); x++) {
    				if (!(map[x][y-1].getType()) || x == 0 || !(map[x-1][y].getType())) {
    					map[x][y].setType(false);
    				} else {
    					int r = rand() % 100;
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
    				}
    			}
    			for (int x = middle; x >= 0 && x >= (middle - spanb); x--) {
    				if (!(map[x][y-1].getType()) || x == (maxX - 1) || !(map[x+1][y].getType())) {
    					map[x][y].setType(false);
    				} else {
    					int r = rand() % 100;
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
    				}
    			}
    		}
    		oldspana = middle;
    		oldspanb = middle;
    		middle = middle + ((spana - spanb) / 2);
    		oldspana = middle - oldspana + spana;
    		oldspanb = middle - oldspanb + spanb;
    	}
    } else if (river == RIVER_NORTHSOUTH) {
    	int middle = (rand() %( maxX/3)) + (rand() %( maxX/3)) + (rand() %( maxX/3));
    	int oldspana, oldspanb;
    	for (int x = 0; x < maxX; x++) {
			int spana = 1;
			for (int i = 0; i < 4; i++ ) {
				spana += (rand() % ((maxX*waterLevel)/2400));
			}
			int spanb = 1;
			for (int i = 0; i < 4; i++ ) {
				spanb += (rand() % ((maxX*waterLevel)/2400));
			}
    		if (x == 0) {
    			for (int y = middle; y < maxY && y < (middle + spana); y++) {
        			map[x][y].setType(false);
    			}
    			for (int y = middle; y >= 0 && y >= (middle - spanb); y--) {
        			map[x][y].setType(false);
    			}
    		} else {
    			spana = (spana + oldspana) / 2;
    			spanb = (spanb + oldspanb) / 2;
    			for (int y = middle; y < maxY && y < (middle + spana); y++) {
    				if (!(map[x-1][y].getType()) || y == 0 || !(map[x][y-1].getType())) {
    					map[x][y].setType(false);
    				} else {
    					int r = rand() % 100;
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
    				}
    			}
    			for (int y = middle; y >= 0 && y >= (middle - spanb); y--) {
    				if (!(map[x-1][y].getType()) || y == (maxY - 1) || !(map[x][y+1].getType())) {
    					map[x][y].setType(false);
    				} else {
    					int r = rand() % 100;
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
    				}
    			}
    		}
    		oldspana = middle;
    		oldspanb = middle;
    		middle = middle + ((spana - spanb) / 2);
    		oldspana = middle - oldspana + spana;
    		oldspanb = middle - oldspanb + spanb;
    	}
    }

    // Create Lakes
    for (int r = rand() % 100; r < waterLevel; r = rand() % 100) {
    	int xs = rand() % maxX;
    	int ys = rand() % maxY;
    	map[xs][ys].setType(false);

    }

    // Create deep Water
    for (int x = 0; x < maxX; x++) {
    	for (int y = 0; y < maxY; y++) {
    		if (!(map[x][y].getType())) {
    			if (	(x == 0 || !(map[x-1][y].getType())) &&
    					(y == 0 || !(map[x][y-1].getType())) &&
						(x == (maxX - 1) || !(map[x+1][y].getType())) &&
						(y == (maxY - 1) || !(map[x][y+1].getType())))
    			{
    				map[x][y].setMoist(true);
    			}
    		}
    	}
    }

    // Create Meadows
    for (int r = rand() % 100; r < waterLevel; r = rand() % 100) {
    	int xs = rand() % maxX;
    	int ys = rand() % maxY;
    	if (map[xs][ys].getType()) {
    		map[xs][ys].setMoist(true);
    	}
    }

    // Create Forests
    for (int r = rand() % 100; r < waterLevel; r = rand() % 100) {
    	int xs = rand() % maxX;
    	int ys = rand() % maxY;
    	if (map[xs][ys].getType()) {
    		map[xs][ys].setTrees(rand() % 5);
    	}
    }

}
