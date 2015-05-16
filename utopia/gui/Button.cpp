/*
 * Button.cpp
 *
 *  Created on: 15.05.2015
 *      Author: Martin Ringwelski
 */

#include "Button.h"

Button::Button(const char* text, TTF_Font* font, const SDL_Color& color, int posX, int posY, int width, int height):
	text(text),
	rect{posX, posY, width, height},
	font(font),
	color(color)
{
}

Button::~Button() {
}

void Button::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderDrawRect( renderer, &rect);

	SDL_Rect Text_rect = {
			rect.x,
			rect.y,
			0,
			0
	};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	TTF_SizeText(font, text.c_str(), &(Text_rect.w), &(Text_rect.h));
	Text_rect.x = rect.x + ((rect.w - Text_rect.w) / 2);
	Text_rect.y = rect.y + ((rect.h - Text_rect.h) / 2);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_RenderCopy(renderer, Message, NULL, &Text_rect);
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}

bool Button::checkClick(int x, int y) {
	if (x >= rect.x && x < rect.x + rect.w) {
		if (y >= rect.y && y < rect.y + rect.h) {
			return true;
		}
	}
	return false;
}
