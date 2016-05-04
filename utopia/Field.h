/*
 * Field.h
 *
 *  Created on: 04.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef FIELD_H_
#define FIELD_H_

#include "SDL2/SDL.h"
#include "buildings/Building.h"
#include "resources/Resource.h"

class Field {
public:
	Field();
	void reset();

	static bool loadMedia(SDL_Renderer* renderer);
	static void close();
	void renderField(SDL_Renderer* renderer, SDL_Rect rect, int zoom, bool selected) const;

	void setType(bool land);
	void setMoist(bool moist);
	void setTrees(unsigned int trees);
	void setStone(unsigned int stone);
	void setGold(unsigned int gold);
	void setIron(unsigned int iron);
	void setCopper(unsigned int copper);
	void setCoal(unsigned int coal);
	void setOil(unsigned int oil);

	bool getType() const;
	bool getMoist() const;
	unsigned int getTrees() const;
	unsigned int getStone() const;
	unsigned int getGold() const;
	unsigned int getIron() const;
	unsigned int getCopper() const;
	unsigned int getCoal() const;
	unsigned int getOil() const;

	Resource* getResource() {
		return resource;
	}
	void setResource(Resource* res) {
		if (resource != NULL) {
			delete resource;
		}
		resource = res;
	}
	void timeChange(int days);

	void writeFile(std::ofstream* fstream);
	void readFile(std::ifstream* fstream);

	virtual ~Field();
private:
	bool land;
	bool moist;			// Used to determine deep water or moist ground

	Resource*	resource;
	Building*	building;

	static SDL_Texture* sand;
	static SDL_Texture* gras;
	static SDL_Texture* water;
	static SDL_Texture* deepwater;

};

#endif /* FIELD_H_ */
