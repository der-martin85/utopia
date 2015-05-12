/*
 * Gold.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_GOLD_H_
#define RESOURCES_GOLD_H_

#include "Resource.h"

class Gold: public Resource {
public:
	static const ResourceType_t TYPE = 3;

	Gold();
	virtual ~Gold();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	unsigned int getGold() const {
		return gold;
	}

	void setGold(unsigned int gold) {
		this->gold = gold;
	}

private:
	unsigned int gold;
};

#endif /* RESOURCES_GOLD_H_ */
