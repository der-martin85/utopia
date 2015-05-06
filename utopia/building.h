/*
 * building.h
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#include "GameDate.h"

#ifndef BUILDING_H_
#define BUILDING_H_

class building {
public:
	building();
	virtual ~building();
protected:
	GameDate	buildDate;
};

#endif /* BUILDING_H_ */
