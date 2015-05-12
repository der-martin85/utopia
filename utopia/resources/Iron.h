/*
 * Iron.h
 *
 *  Created on: 12.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef RESOURCES_IRON_H_
#define RESOURCES_IRON_H_

#include "Resource.h"

class Iron: public Resource {
public:
	static const ResourceType_t TYPE = 4;

	Iron();
	virtual ~Iron();

	ResourceType_t getResourceType() {
		return TYPE;
	}

	unsigned int getIron() const {
		return iron;
	}

	void setIron(unsigned int iron) {
		this->iron = iron;
	}

private:
	unsigned int iron;
};

#endif /* RESOURCES_IRON_H_ */
