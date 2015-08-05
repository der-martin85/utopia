/*
 * date.h
 *
 *  Created on: 27.08.2010
 *      Author: jentin
 */

#ifndef GAMEDATE_H_
#define GAMEDATE_H_

#include <string>

class GameDate {
public:
	GameDate(int year = 0, char month = 1, char day = 1);
	virtual ~GameDate();

	void addDays(int days);

	int getYear() {
		return year;
	}
	char getMonth() {
		return month;
	}
	char getDay() {
		return day;
	}

	std::string getDateString() {
		std::string ret = "";
		ret += std::to_string((int)day);
		ret += ".";
		ret += std::to_string((int)month);
		ret += ".";
		ret += std::to_string(year);
		return ret;
	}
protected:
	int year;
	char month;
	char day;
};

#endif /* GAMEDATE_H_ */
