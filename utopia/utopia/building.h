/*
 * building.h
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#include "date.h"

#ifndef BUILDING_H_
#define BUILDING_H_

class building {
public:
	building();
	virtual ~building();
protected:
	date	buildDate;
};

#endif /* BUILDING_H_ */
