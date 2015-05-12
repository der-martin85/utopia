/*
 * Coal.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_COAL_H_
#define RESOURCES_COAL_H_

#include "Resource.h"

class Coal: public Resource {
public:
	static const ResourceType_t TYPE = 6;

	Coal(unsigned int coal);
	virtual ~Coal();

	virtual ResourceType_t getResourceType() {
		return TYPE;
	}

	unsigned int getCoal() const {
		return coal;
	}

	void setCoal(unsigned int coal) {
		this->coal = coal;
	}

	virtual void loadMedia(SDL_Renderer* renderer);
	virtual void close();
	virtual void renderFieldResource(SDL_Renderer* renderer, SDL_Rect rect);

private:
	unsigned int coal;
};

#endif /* RESOURCES_COAL_H_ */
