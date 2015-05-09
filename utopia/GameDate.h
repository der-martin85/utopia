/*
 * date.h
 *
 *  Created on: 27.08.2010
 *      Author: jentin
 */

#ifndef GAMEDATE_H_
#define GAMEDATE_H_

class GameDate {
public:
	GameDate(int year = 0, int month = 1, int day = 1);
	virtual ~GameDate();
protected:
	int year;
	int month;
	int day;
};

#endif /* GAMEDATE_H_ */
