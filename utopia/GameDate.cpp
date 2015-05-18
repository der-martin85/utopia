/*
 * date.cpp
 *
 *  Created on: 27.08.2010
 *      Author: jentin
 */

#include "GameDate.h"

GameDate::GameDate(int year, char month, char day):
		year(year),
		month(month),
		day(day)
{
}

GameDate::~GameDate() {
}

void GameDate::addDays(int days) {
	day += days;

	int maxDaysFeb = 28;
	if (((year % 4)) == 0 && ((year % 100) != 0 || (year % 400) == 0)) {
		maxDaysFeb++;
	}


	switch (month) {
	case 1:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (day > 31) {
			day -= 31;
			month++;
		} else if (day < 1) {
			day += 30;
			month--;
		}
		break;
	case 3:
		if (day > 31) {
			day -= 31;
			month++;
		} else if (day < 1) {
			day += maxDaysFeb;
			month--;
		}
		break;
	case 2:
		if (day > maxDaysFeb) {
			day -= maxDaysFeb;
			month++;
		} else if (day < 1) {
			day += 31;
			month--;
		}
		break;
	default:
		if (day > 30) {
			day -= 30;
			month++;
		} else if (day < 1) {
			day += 31;
			month--;
		}
		break;
	}

	if (month > 12) {
		month -= 12;
		year++;
	} else if (month < 1) {
		month += 12;
		year--;
	}
}
