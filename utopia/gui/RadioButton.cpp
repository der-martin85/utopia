/*
 * RadioButton.cpp
 *
 *  Created on: 15.05.2015
 *      Author: Martin Ringwelski
 */

#include "RadioButton.h"

RadioButton::RadioButton(int* value, int checkValue, const char* text, TTF_Font* font, const SDL_Color& color, int posX, int posY):
	text(text),
	boxRect{posX + 3, posY + 3, 0, 0},
	textRect{posX, posY, 0, 0},
	font(font),
	color(color),
	value(value),
	checkValue(checkValue)
{
	TTF_SizeText(font, this->text.c_str(), &(textRect.w), &(textRect.h));

	boxRect.w = textRect.h - 6;
	boxRect.h = textRect.h - 6;
	textRect.x += textRect.h;
}

RadioButton::~RadioButton() {
}

bool RadioButton::checkClick(int x, int y) {
	if (x >= boxRect.x && x < boxRect.x + boxRect.w) {
		if (y >= boxRect.y && y < boxRect.y + boxRect.h) {
			return true;
		}
	}
	return false;
}

void RadioButton::render(SDL_Renderer* renderer) {
	TTF_SizeText(font, this->text.c_str(), &(textRect.w), &(textRect.h));

	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderFillRect( renderer, &boxRect );
	if (*value == checkValue) {
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_Rect check = {
				boxRect.x + 3,
				boxRect.y + 3,
				boxRect.w - 6,
				boxRect.h - 6
		};
		SDL_RenderFillRect( renderer, &check );
	}

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, this->text.c_str(), color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_RenderCopy(renderer, Message, NULL, &textRect);
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}
