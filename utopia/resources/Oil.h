/*
 * Oil.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_OIL_H_
#define RESOURCES_OIL_H_

#include "Resource.h"

class Oil: public Resource {
public:
	static const ResourceType_t TYPE = 7;

	Oil();
	virtual ~Oil();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	unsigned int getOil() const {
		return oil;
	}

	void setOil(unsigned int oil) {
		this->oil = oil;
	}

private:
	unsigned int oil;
};

#endif /* RESOURCES_OIL_H_ */
