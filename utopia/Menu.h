/*
 * Menu.h
 *
 *  Created on: 09.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
	Menu();
	virtual ~Menu();

	void setMouseState(int mX, int mY) {
		this->mX = mX;
		this->mY = mY;
	}
	void click();

	bool quit;
private:
	int mX, mY;
};

#endif /* MENU_H_ */
