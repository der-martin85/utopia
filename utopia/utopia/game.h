/*
 * game.h
 *
 *  Created on: 20.07.2010
 *      Author: jentin
 */

#include "date.h"

#ifndef GAME_H_
#define GAME_H_

class game {
public:
	game();
	virtual ~game();
protected:
	int	evolutionLevel;
	int	speed;
	date	actualDate;
};

#endif /* GAME_H_ */
