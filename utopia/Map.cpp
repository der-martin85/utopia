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
						if (r < waterLevel / 2) {
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
						if (r < waterLevel / 2) {
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
						if (r < waterLevel / 2) {
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
						if (r < waterLevel / 2) {
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

    // Create Meadows, Trees, Forests and Sand Dunes
    for (int x = 0; x < maxX; x++) {
    	for (int y = 0; y < maxY; y++) {
        	if (((rand() % 100) < 5)) {
        		switch (rand() % 6) {
        		case 0:
        			map[x][y].setStone((rand() % 70) + 1);
        			break;
        		case 1:
        			map[x][y].setGold((rand() % 50) + 1);
        			break;
        		case 2:
        			map[x][y].setIron((rand() % 60) + 1);
        			break;
        		case 3:
        			map[x][y].setCopper((rand() % 55) + 1);
        			break;
        		case 4:
        			map[x][y].setCoal((rand() % 50) + 1);
        			break;
        		case 5:
        			map[x][y].setOil((rand() % 50) + 1);
        			break;
        		}

        	}


        	if (map[x][y].getType()) {
        		if (	(x == 0 || !map[x-1][y].getType() || (map[x-1][y].getType() && map[x-1][y].getMoist())) ||
        				(y == 0 || !map[x][y-1].getType() || (map[x][y-1].getType() && map[x][y-1].getMoist()))) {
        			map[x][y].setMoist((rand() % 10) < 9);
        		} else {
        			map[x][y].setMoist((rand() % 10) < 8);
        		}
        		if (map[x][y].getMoist() &&
        				map[x][y].getStone() < 20 &&
						map[x][y].getGold() < 20 &&
						map[x][y].getIron() < 20 &&
						map[x][y].getCopper() < 20 &&
						map[x][y].getCoal() < 20 &&
						map[x][y].getOil() < 20) {
                	if (((rand() % 10) < 6)) {
                		map[x][y].setTrees((rand() % 4) + 1);
                	}
        		}
        	}
    	}
    }

}

bool Map::loadMedia(SDL_Renderer* renderer)
{
    //Loading success flag
    bool success = true;

    SDL_Surface* groundIMG[4] = {NULL, NULL, NULL, NULL};
	SDL_Surface* treesIMG[4] = {NULL, NULL, NULL, NULL};
	SDL_Surface* stoneIMG[3] = {NULL, NULL, NULL};
	SDL_Surface* goldIMG[3] = {NULL, NULL, NULL};
	SDL_Surface* selectedIMG = NULL;

	groundIMG[0] = IMG_Load("./images/sand.png");
    groundIMG[1] = IMG_Load("./images/gras.png");
    groundIMG[2] = IMG_Load("./images/water0.png");
    groundIMG[3] = IMG_Load("./images/water1.png");

    treesIMG[0] = IMG_Load("./images/trees1.png");
    treesIMG[1] = IMG_Load("./images/trees2.png");
    treesIMG[2] = IMG_Load("./images/trees3.png");
    treesIMG[3] = IMG_Load("./images/trees4.png");

    stoneIMG[0] = IMG_Load("./images/stone1.png");
    stoneIMG[1] = IMG_Load("./images/stone2.png");
    stoneIMG[2] = IMG_Load("./images/stone3.png");

    goldIMG[0] = IMG_Load("./images/gold1.png");
    goldIMG[1] = IMG_Load("./images/gold2.png");
    goldIMG[2] = IMG_Load("./images/gold3.png");


    for (int i = 0; i < 4; i++) {
    	groundTextures[i] = SDL_CreateTextureFromSurface(renderer, groundIMG[i]);
    	SDL_FreeSurface(groundIMG[i]);
    	treesTextures[i] = SDL_CreateTextureFromSurface(renderer, treesIMG[i]);
    	SDL_FreeSurface(treesIMG[i]);
    }
    for (int i = 0; i < 3; i++) {
    	stoneTextures[i] = SDL_CreateTextureFromSurface(renderer, stoneIMG[i]);
    	SDL_FreeSurface(stoneIMG[i]);
    	goldTextures[i] = SDL_CreateTextureFromSurface(renderer, goldIMG[i]);
    	SDL_FreeSurface(goldIMG[i]);
    }

    selectedIMG = IMG_Load("./images/selected.png");
    selectedTexture = SDL_CreateTextureFromSurface(renderer, selectedIMG);
	SDL_FreeSurface(selectedIMG);

    return success;
}

void Map::close() {
    for (int i = 0; i < 4; i++) {
    	SDL_DestroyTexture(groundTextures[i]);
    	groundTextures[i] = NULL;

    	SDL_DestroyTexture(treesTextures[i]);
    	treesTextures[i] = NULL;
    }
    for (int i = 0; i < 3; i++) {
    	SDL_DestroyTexture(stoneTextures[i]);
    	stoneTextures[i] = NULL;

    	SDL_DestroyTexture(goldTextures[i]);
    	goldTextures[i] = NULL;
    }

	SDL_DestroyTexture(selectedTexture);
	selectedTexture = NULL;
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
				const Field* field = game->getMap()->getField(x, y);
				if (field->getType()) {
					if (field->getMoist()) {
						   SDL_RenderCopy(renderer, groundTextures[1], NULL, &dstrect);
					} else {
						   SDL_RenderCopy(renderer, groundTextures[0], NULL, &dstrect);
					}
					if (field->getStone() > 20) {
						int num = (field->getStone() - 20) / 10;
						if (num > 2) {
							num = 2;
						}
						SDL_RenderCopy(renderer, stoneTextures[num], NULL, &dstrect);
					}
					if (field->getGold() > 20) {
						int num = (field->getGold() - 20) / 10;
						if (num > 2) {
							num = 2;
						}
						SDL_RenderCopy(renderer, goldTextures[num], NULL, &dstrect);
					}
					if (field->getTrees() > 0) {
						int num = field->getTrees() - 1;
						if (num > 3) {
							num = 3;
						}
						SDL_RenderCopy(renderer, treesTextures[num], NULL, &dstrect);
					}
				} else {
					if (field->getMoist()) {
						   SDL_RenderCopy(renderer, groundTextures[3], NULL, &dstrect);
					} else {
						   SDL_RenderCopy(renderer, groundTextures[2], NULL, &dstrect);
					}
				}
			   if ((((x >= game->getSelectedStartX() && x <= game->getSelectedEndX()) ||
							   (x <= game->getSelectedStartX() && x >= game->getSelectedEndX())) &&
					   ((y >= game->getSelectedStartY() && y <= game->getSelectedEndY()) ||
							   (y <= game->getSelectedStartY() && y >= game->getSelectedEndY())))) {
				   SDL_Rect sdstrect = {dstrect.x, dstrect.y+(dstrect.h/2),
						   (game->getZoom() * 4), (game->getZoom() * 2)};
				   SDL_RenderCopy(renderer, selectedTexture, NULL, &sdstrect);
			   }
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
