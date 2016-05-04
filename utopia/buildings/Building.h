/*
 * Building.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include "SDL2/SDL.h"
#include <fstream>

typedef int BuildingType_t;

class Building {
public:
	Building(): texture(NULL) {}
	virtual ~Building() {}

	void renderBuilding(SDL_Renderer* renderer, SDL_Rect rect, int zoom, bool selected) const {
		if (texture != NULL && *texture != NULL) {
			if (selected) {
				SDL_SetTextureColorMod(*texture, 128, 128, 255);
			}
			SDL_RenderCopy(renderer, *texture, NULL, &rect);
			if (selected) {
				SDL_SetTextureColorMod(*texture, 255, 255, 255);
			}
		}
	}

	virtual void changeTime(int days);

	virtual BuildingType_t getBuildingType() = 0;

	virtual void writeBuilding(std::ofstream* file) = 0;
	static Building* loadBuilding(std::ifstream* file);

protected:
	SDL_Texture** texture;

};

#endif /* BUILDING_H_ */
