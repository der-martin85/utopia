/*
 * RadioButton.h
 *
 *  Created on: 15.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef GUI_RADIOBUTTON_H_
#define GUI_RADIOBUTTON_H_

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class RadioButton {
public:
	RadioButton(int* value, int checkValue, const char* text, TTF_Font* font, const SDL_Color& color, int posX, int posY);
	virtual ~RadioButton();

	void render(SDL_Renderer* renderer);
	bool checkClick(int x, int y);

	SDL_Color getColor() const {
		return color;
	}

	void setColor(SDL_Color color) {
		this->color = color;
	}

	const TTF_Font* getFont() const {
		return font;
	}

	void setFont(TTF_Font* font) {
		this->font = font;
	}

	void setPos(int x, int y) {
		this->boxRect.x = x+3;
		this->boxRect.y = y+3;
		this->textRect.x = x + this->textRect.h;
		this->textRect.y = y;
	}

	int getHeigth() const {
		return textRect.h;
	}

	const std::string& getText() const {
		return text;
	}

	void setText(const std::string& text) {
		this->text = text;
	}

private:
	std::string text;
	SDL_Rect boxRect;
	SDL_Rect textRect;
	TTF_Font* font;
	SDL_Color color;
	int*	value;
	int		checkValue;
};

#endif /* GUI_RADIOBUTTON_H_ */
