/*
 * Menu.cpp
 *
 *  Created on: 09.05.2015
 *      Author: Martin Ringwelski
 */

#include "Menu.h"

Menu::Menu():
	quit(false),
	mX(0), mY(0)
{
}

Menu::~Menu() {
}

void Menu::click() {
	if (mX > 10 && mX < 90) {
		if (mY > 10 && mY < 60) {
			quit = true;
		}
	}
}
