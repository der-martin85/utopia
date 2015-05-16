/*
 * Button.h
 *
 *  Created on: 15.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef GUI_BUTTON_H_
#define GUI_BUTTON_H_

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class Button {
public:
	Button(const char* text, TTF_Font* font, const SDL_Color& color, int posX, int posY, int width, int height);
	virtual ~Button();

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

	const SDL_Rect& getRect() const {
		return rect;
	}

	void setPos(int x, int y) {
		this->rect.x = x;
		this->rect.y = y;
	}

	const std::string& getText() const {
		return text;
	}

	void setText(const std::string& text) {
		this->text = text;
	}

private:
	std::string text;
	SDL_Rect rect;
	TTF_Font* font;
	SDL_Color color;
};

#endif /* GUI_BUTTON_H_ */
