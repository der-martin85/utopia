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

#include <iostream>

void Map::generateMap(Uint8 oceans, river_t river, Uint8 waterLevel) {
    time_t t;
    time(&t);
    srand((unsigned int)t);

    for (int x = 0; x < maxX; x++) {
    	for (int y = 0; y < maxY; y++) {
    		map[x][y].setType(true);
    	}
    }

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

    if (river == RIVER_EASTWEST) {
    	int middle = (rand() %( maxX/3)) + (rand() %( maxX/3)) + (rand() %( maxX/3));
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
    		middle = middle + ((spana - spanb) / 2);
    	}
    } else if (river == RIVER_NORTHSOUTH) {
    	int middle = (rand() %( maxX/3)) + (rand() %( maxX/3)) + (rand() %( maxX/3));
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
    		middle = middle + ((spana - spanb) / 2);
    	}
    }

//    const int probabilities[9] = {
//    		3,
//    		65,
//    		30,
//    		85,
//    		30,
//    		40,
//    		30,
//    		99,
//			50
//    };
//
//    for (int s = 0; s < maxX && s < maxY; s++) {
//    	if (s < maxX) {
//    		int x = s;
//			for (int y = s; y < maxY; y++) {
//				int r = rand() % 100;
//				int p = 0;
//				if (y > 0) {
//					if (x > 0) {
//						if (y < (maxY-1)) {
//							if (map[x][y-1].getType()) p += 1;
//							if (map[x-1][y].getType()) p += 2;
//							if (map[x-1][y+1].getType()) p += 4;
//						} else {
//							if (map[x][y-1].getType()) p += 1;
//							if (map[x-1][y].getType()) p += 6;
//						}
//					} else {
//						if (map[x][y-1].getType()) p += 7;
//					}
//				} else if (x > 0) {
//					if (y < (maxY-1)) {
//						if (map[x-1][y].getType()) p += 3;
//						if (map[x-1][y+1].getType()) p += 4;
//					} else {
//						if (map[x-1][y].getType()) p += 7;
//					}
//				} else {
//					p = 8;
//				}
//				map[x][y].setType(r < probabilities[p]);
//			}
//    	}
//    	if (s < maxY) {
//    		int y = s;
//    		for (int x = s+1; x < maxX; x++) {
//				int r = rand() % 100;
//				int p = 0;
//				if (x > 0) {
//					if (y > 0) {
//						if (x < (maxX-1)) {
//							if (map[x-1][y].getType()) p += 1;
//							if (map[x][y-1].getType()) p += 2;
//							if (map[x+1][y-1].getType()) p += 4;
//						} else {
//							if (map[x-1][y].getType()) p += 1;
//							if (map[x][y-1].getType()) p += 6;
//						}
//					} else {
//						if (map[x-1][y].getType()) p += 7;
//					}
//				} else if (y > 0) {
//					if (x < (maxX-1)) {
//						if (map[x][y-1].getType()) p += 3;
//						if (map[x+1][y-1].getType()) p += 4;
//					} else {
//						if (map[x][y-1].getType()) p += 7;
//					}
//				} else {
//					p = 8;
//				}
//				map[x][y].setType(r < probabilities[p]);
//    		}
//    	}
//    }
}
