#include "SDL2/SDL.h"

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <pthread.h>

#include "Map.h"
#include "RenderThread.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* argv[]) {

    SDL_Event event;

    const int fieldx = 100;
    const int fieldy = 100;

	Map f = Map(fieldx, fieldy);
	f.generateMap();

	RenderThread* renderThread = RenderThread::startThread(SCREEN_WIDTH, SCREEN_HEIGHT, &f);
	if (renderThread == NULL) {
		return 0;
	}

	while (!renderThread->quit)
	{
	   SDL_WaitEvent(&event);

	   f.setMouseState();

	   switch(event.type)
	   {
	   case SDL_QUIT:
		   renderThread->quit = true;
		   break;
	   case SDL_MOUSEWHEEL:
		   {
			   const SDL_MouseWheelEvent* mwe = (SDL_MouseWheelEvent*)(&event);

			   f.changeZoom(mwe->y);

			   break;
		   }
	   case SDL_MOUSEBUTTONDOWN:
		   {
			   const SDL_MouseButtonEvent* mbe = (SDL_MouseButtonEvent*)(&event);
			   if (mbe->button == SDL_BUTTON_RIGHT) {
				   f.startDragging();
			   }
			   if (mbe->button == SDL_BUTTON_LEFT) {
				   // Feld markieren
				   f.startSelecting();
			   }
			   break;
		   }
	   case SDL_MOUSEBUTTONUP:
		   {
			   const SDL_MouseButtonEvent* mbe = (SDL_MouseButtonEvent*)(&event);
			   if (mbe->button == SDL_BUTTON_RIGHT) {

				   f.doneDragging();
			   }
			   if (mbe->button == SDL_BUTTON_LEFT) {
				   // Feld markieren
				   f.doneSelecting();
			   }
			   break;
		   }
	   case SDL_KEYDOWN:
		   {
			   const Uint8 *state = SDL_GetKeyboardState(NULL);
			   if (state[SDL_SCANCODE_RIGHT]) {
				   f.changePosX(2);
			   }
			   if (state[SDL_SCANCODE_UP]) {
				   f.changePosY(1);
			   }
			   if (state[SDL_SCANCODE_DOWN]) {
				   f.changePosY(-1);
			   }
			   if (state[SDL_SCANCODE_LEFT]) {
				   f.changePosX(-2);
			   }
			   if (state[SDL_SCANCODE_W]) {
				   f.changeZoom(-1);
			   }
			   if (state[SDL_SCANCODE_N]) {
				   f.changeZoom(+1);
			   }
			   if (state[SDL_SCANCODE_F]) {
				   f.changeToFullScreen();
			   }
			   if (state[SDL_SCANCODE_X]) {
				   f.changeToWindow();
			   }
			   if (state[SDL_SCANCODE_Q]) {
				   renderThread->quit = true;
			   }
			   break;
		   }
	   }
	   f.signalChange();
	}
   if (renderThread != NULL) {
	   delete renderThread;
   }

	return 0;
}
