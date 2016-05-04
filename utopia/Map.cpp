/*
 * field.cpp
 *
 *  Created on: 20.07.2010
 *      Author: Martin Ringwelski
 */

#include "Map.h"
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL_image.h"
#include "buildings/Tree.h"
#include "resources/Stone.h"
#include "resources/Gold.h"
#include "resources/Iron.h"
#include "resources/Copper.h"
#include "resources/Coal.h"
#include "resources/Oil.h"


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

bool Map::checkLimit(int a, int max) {
	if (a >= 0 && a < max) {
		return true;
	}
	return false;
}

void Map::generateCoast(oceans_t ocean, int waterLevel) {
	int aStart = 0;
	int bStart = 0;
	int aMax, bMax;
	int aAdd = 1;
	int bAdd = 1;
	int addOtherXa = 1;
	int addOtherXb = -1;
	int addOtherYa = -1;
	int addOtherYb = -1;
	if (ocean == OCEAN_NORTH) {
		aMax = maxY;
		bMax = maxX;
	} else if (ocean == OCEAN_WEST) {
		aMax = maxX;
		bMax = maxY;
		addOtherXa = -1;
		addOtherYa = 1;
	} else if (ocean == OCEAN_SOUTH) {
		aStart = (maxY - 1);
		aAdd = -1;
		aMax = maxY;
		bMax = maxX;
		addOtherYa = 1;
		addOtherYb = 1;
	} else if (ocean == OCEAN_EAST) {
		aStart = (maxX - 1);
		aAdd = -1;
		aMax = maxX;
		bMax = maxY;
		addOtherXb = 1;
		addOtherYa = 1;
	}
	for (int a = aStart; checkLimit(a, aMax); a += aAdd) {
		for (int b = bStart; checkLimit(b, bMax); b += bAdd) {
			int x, y, ox, oy;
			if (ocean == OCEAN_NORTH) {
				x = b;
				y = a;
				ox = x;
				oy = y - 1;
			} else if (ocean == OCEAN_WEST) {
				x = a;
				y = b;
				ox = x - 1;
				oy = y;
			} else if (ocean == OCEAN_SOUTH) {
				x = b;
				y = a;
				ox = x;
				oy = y + 1;
			} else if (ocean == OCEAN_EAST) {
				x = a;
				y = b;
				ox = x + 1;
				oy = y;
			}
			if (a == aStart) {
    			map[x][y].setType(false);
    		} else if (!(map[ox][oy].getType())) {
				int r = rand() % 100;
				if ((b == (bMax - 1) || !(map[x+addOtherXa][y+addOtherYa].getType())) &&
						((b == 0) || !(map[x+addOtherXb][y+addOtherYb].getType())))
				{
					if (r < waterLevel) {
						map[x][y].setType(false);
					}
				} else {
					if (r < waterLevel / 2) {
						map[x][y].setType(false);
					}
				}
    		}
    	}
    }
}

void Map::generateRiver(river_t river, int waterLevel) {
	int aMax = maxY;
	int bMax = maxX;
	if (river == RIVER_NORTHSOUTH) {
		aMax = maxX;
		bMax = maxY;
	}

	int middle = (rand() %( bMax/3)) + (rand() %( bMax/3)) + (rand() %( bMax/3));
	int oldspana, oldspanb;
	for (int a = 0; a < aMax; a++) {
		int x, y;
		if (river == RIVER_EASTWEST) {
			y = a;
		} else {
			x = a;
		}
		int spana = 1;
		for (int i = 0; i < 4; i++ ) {
			spana += (rand() % ((bMax*waterLevel)/2400));
		}
		int spanb = 1;
		for (int i = 0; i < 4; i++ ) {
			spanb += (rand() % ((bMax*waterLevel)/2400));
		}
		if (a == 0) {
			for (int add = 1; add > -2; add -= 2) {
				for (int b = middle; checkLimit(b, bMax) && b < (middle + spana) && b >= (middle - spanb); b += add) {
					if (river == RIVER_EASTWEST) {
						x = b;
					} else {
						y = b;
					}
					map[x][y].setType(false);
				}
			}
		} else {
			spana = (spana + oldspana) / 2;
			spanb = (spanb + oldspanb) / 2;
			for (int add = 1; add > -2; add -= 2) {
				for (int b = middle; checkLimit(b, bMax) && b < (middle + spana) && b >= (middle - spanb); b += add) {
					int xa, ya;
					int xb, yb;
					if (river == RIVER_EASTWEST) {
						x = b;
						xa = x;
						ya = y - 1;
						xb = x - add;
						yb = y;
					} else {
						y = b;
						xa = x - 1;
						ya = y;
						xb = x;
						yb = y - add;
					}
					if (!(map[xa][ya].getType()) || !checkLimit(b - add, bMax) || !(map[xb][yb].getType())) {
						map[x][y].setType(false);
					} else {
						int r = rand() % 100;
						if (r < waterLevel) {
							map[x][y].setType(false);
						}
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

void Map::generateMap(Uint8 oceans, Uint8 river, Uint8 waterLevel) {
    time_t t;
    time(&t);
    srand((unsigned int)t);

    for (int x = 0; x < maxX; x++) {
    	for (int y = 0; y < maxY; y++) {
    		map[x][y].reset();
    	}
    }

    // TODO: Work on Code duplication!
    // Create Coasts
	if (oceans & OCEAN_NORTH) {
		generateCoast(OCEAN_NORTH, waterLevel);
	}
	if (oceans & OCEAN_WEST) {
		generateCoast(OCEAN_WEST, waterLevel);
	}
	if (oceans & OCEAN_SOUTH) {
		generateCoast(OCEAN_SOUTH, waterLevel);
	}
	if (oceans & OCEAN_EAST) {
		generateCoast(OCEAN_EAST, waterLevel);
	}

	// Create River

    if (river == RIVER_EASTWEST) {
    	generateRiver(RIVER_EASTWEST, waterLevel);
    } else if (river == RIVER_NORTHSOUTH) {
    	generateRiver(RIVER_NORTHSOUTH, waterLevel);
    }

    // Create Lakes
    for (int r = rand() % 100; r < waterLevel; r = rand() % 100) {
    	int xs = rand() % maxX;
    	int ys = rand() % maxY;
    	int maxSpan = maxX > maxY ? maxY : maxX;
		int span = 1;
		for (int i = 0; i < 4; i++ ) {
			span += (rand() % ((maxSpan*waterLevel)/1600));
		}
    	map[xs][ys].setType(false);
        for (int x = xs; x < maxX && x < (xs + span); x++) {
        	for (int y = ys; y < maxY && y < (ys + span); y++) {
        		if (map[x][y].getType() && (
        				(x == 0 || !map[x-1][y].getType()) ||
        				(y == 0 || !map[x][y-1].getType()))) {
        			map[x][y].setType((rand() % 100) < waterLevel);
        		}
        	}
        }
    }

    // Create deep Water, Meadows, Trees, Forests and Sand Dunes
    for (int x = 0; x < maxX; x++) {
    	for (int y = 0; y < maxY; y++) {
        	if (((rand() % 100) < 5)) {
        		switch (rand() % 6) {
        		case 0:
        			map[x][y].setStone((rand() % Stone::MAX_AMOUNT) + 1);
        			break;
        		case 1:
        			map[x][y].setGold((rand() % Gold::MAX_AMOUNT) + 1);
        			break;
        		case 2:
        			map[x][y].setIron((rand() % Iron::MAX_AMOUNT) + 1);
        			break;
        		case 3:
        			map[x][y].setCopper((rand() % Copper::MAX_AMOUNT) + 1);
        			break;
        		case 4:
        			map[x][y].setCoal((rand() % Coal::MAX_AMOUNT) + 1);
        			break;
        		case 5:
        			map[x][y].setOil((rand() % Oil::MAX_AMOUNT) + 1);
        			break;
        		}

        	}

    		if (!(map[x][y].getType())) {
    			if (	(x == 0 || !(map[x-1][y].getType())) &&
    					(y == 0 || !(map[x][y-1].getType())) &&
						(x == (maxX - 1) || !(map[x+1][y].getType())) &&
						(y == (maxY - 1) || !(map[x][y+1].getType())))
    			{
    				map[x][y].setMoist(true);
    			}
    		} else {
        		if (	(x == 0 || !map[x-1][y].getType() || (map[x-1][y].getType() && map[x-1][y].getMoist())) ||
        				(y == 0 || !map[x][y-1].getType() || (map[x][y-1].getType() && map[x][y-1].getMoist()))) {
        			map[x][y].setMoist((rand() % 10) < 9);
        		} else {
        			map[x][y].setMoist((rand() % 10) < 8);
        		}
        		if (map[x][y].getMoist() &&
        				map[x][y].getStone() == 0 &&
						map[x][y].getGold() == 0 &&
						map[x][y].getIron() == 0 &&
						map[x][y].getCopper() == 0 &&
						map[x][y].getCoal() == 0 &&
						map[x][y].getOil() == 0) {
                	if (((rand() % 10) < 6)) {
                		map[x][y].setTrees((rand() % Tree::MAX_NUM_TREES) + 1);
                	}
        		}

    		}
    	}
    }

}

bool Map::loadMedia(SDL_Renderer* renderer)
{
    return Field::loadMedia(renderer);
}

void Map::close() {
	Field::close();
}

bool checkXY(int add, int xy, int xyMax) {
	if (add > 0) {
		return (xy < xyMax);
	}
	return (xy >= 0);
}

void Map::renderMap(SDL_Renderer* renderer, Game* game, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	int yStart = 0;
	int xStart = maxX-1;
	int xAdd = -1;
	int yAdd = 1;
	if (game->getAngle() == 1) {
		xStart = 0;
		xAdd = 1;
	} else if (game->getAngle() == 2) {
		xStart = 0;
		xAdd = 1;
		yStart = maxY-1;
		yAdd = -1;
	} else if (game->getAngle() == 3) {
		yStart = maxY-1;
		yAdd = -1;
	}

	for (int y = yStart; checkXY(yAdd, y, game->getMap()->maxY); y += yAdd) {
		for (int x = xStart; checkXY(xAdd, x, game->getMap()->maxX); x += xAdd) {
			SDL_Rect dstrect = isoTo2D(x, y, game);
			if (dstrect.x + dstrect.w > 0 && dstrect.y + dstrect.h > 0 &&
				   dstrect.x < SCREEN_WIDTH && dstrect.y < SCREEN_HEIGHT)
			{
				bool selected = false;
				if ((((x >= game->getSelectedStartX() && x <= game->getSelectedEndX()) ||
							   (x <= game->getSelectedStartX() && x >= game->getSelectedEndX())) &&
					   ((y >= game->getSelectedStartY() && y <= game->getSelectedEndY()) ||
							   (y <= game->getSelectedStartY() && y >= game->getSelectedEndY())))) {
				   selected = true;
				}
				const Field* field = game->getMap()->getField(x, y);
				field->renderField(renderer, dstrect, game->getZoom(), selected);
		   }
	   }
   }

}

SDL_Rect Map::isoTo2D(int x, int y, Game* game) {

	switch (game->getAngle()) {
	case 1: {
		int tmp = x;
		x = maxY - y;
		y = tmp;
		break; }
	case 2: {
		x = maxX - x;
		y = maxY - y;
		break; }
	case 3: {
		int tmp = y;
		y = maxX - x;
		x = tmp;
		break; }
	case 0:
	default: {
		break; }
	}

	SDL_Rect dstrect = {0, 0, (game->getZoom() * 4), (game->getZoom() * 4) };
	dstrect.x = (y + x - (game->getPosX() + game->getMaxPosX())) * 2 * game->getZoom() + 100;
	dstrect.y = (y - x + game->getPosY()) * game->getZoom();
	return dstrect;
}

void Map::writeFile(std::ofstream* fstream) {
	char data[4] = {
			maxX >> 8,
			maxX,
			maxY >> 8,
			maxY
	};
	fstream->write(data, 4);
	for (int x = 0; x < maxX; x++) {
		for (int y = 0; y < maxY; y++) {
			map[x][y].writeFile(fstream);
		}
	}
}

Map* Map::loadMap(std::ifstream* fstream) {
	char data[4];
	fstream->read(data, 4);

	int maxX = ((int)(data[0])) << 8 | (unsigned char)data[1];
	int maxY = ((int)(data[2])) << 8 | (unsigned char)data[3];

	Map* ret = new Map(maxX, maxY);

	for (int x = 0; x < maxX; x++) {
		for (int y = 0; y < maxY; y++) {
			ret->map[x][y].readFile(fstream);
		}
	}

	return ret;
}

void Map::timeChange(int days) {
    for (int x = 0; x < maxX; x++) {
    	for (int y = 0; y < maxY; y++) {
    		map[x][y].timeChange(days);
    	}
    }
}
