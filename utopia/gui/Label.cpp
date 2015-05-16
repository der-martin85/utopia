/*
 * Label.cpp
 *
 *  Created on: 15.05.2015
 *      Author: Martin Ringwelski
 */

#include "Label.h"

Label::Label(const char* text, TTF_Font* font, const SDL_Color& color, int posX, int posY):
	text(text),
	font(font),
	color(color)
{
	rect = {
			posX,
			posY,
			0,
			0
	};
	TTF_SizeText(font, this->text.c_str(), &(rect.w), &(rect.h));
}

Label::~Label() {
}

void Label::render(SDL_Renderer* renderer) {
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, this->text.c_str(), color);
	TTF_SizeText(font, this->text.c_str(), &(rect.w), &(rect.h));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surfaceMessage);
}

bool Label::checkClick(int x, int y) {
	if (x >= rect.x && x < rect.x + rect.w) {
		if (y >= rect.y && y < rect.y + rect.h) {
			return true;
		}
	}
	return false;
}
