#include "SDL2/SDL.h"

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

	//Map f = Map(fieldx, fieldy);
	//f.generateMap();
    Game game(fieldx, fieldy);
    game.generateMap();

	RenderThread* renderThread = RenderThread::startThread(SCREEN_WIDTH, SCREEN_HEIGHT, &game);
	if (renderThread == NULL) {
		return 0;
	}

	while (!renderThread->quit)
	{
	   SDL_WaitEvent(&event);

	   game.setMouseState();

	   switch(event.type)
	   {
	   case SDL_QUIT:
		   renderThread->quit = true;
		   break;
	   case SDL_MOUSEWHEEL:
		   {
			   const SDL_MouseWheelEvent* mwe = (SDL_MouseWheelEvent*)(&event);

			   game.changeZoom(mwe->y);

			   break;
		   }
	   case SDL_MOUSEBUTTONDOWN:
		   {
			   const SDL_MouseButtonEvent* mbe = (SDL_MouseButtonEvent*)(&event);
			   if (mbe->button == SDL_BUTTON_RIGHT) {
				   game.startDragging();
			   }
			   if (mbe->button == SDL_BUTTON_LEFT) {
				   // Feld markieren
				   game.startSelecting();
			   }
			   break;
		   }
	   case SDL_MOUSEBUTTONUP:
		   {
			   const SDL_MouseButtonEvent* mbe = (SDL_MouseButtonEvent*)(&event);
			   if (mbe->button == SDL_BUTTON_RIGHT) {

				   game.doneDragging();
			   }
			   if (mbe->button == SDL_BUTTON_LEFT) {
				   // Feld markieren
				   game.doneSelecting();
			   }
			   break;
		   }
	   case SDL_KEYDOWN:
		   {
			   const Uint8 *state = SDL_GetKeyboardState(NULL);
			   if (state[SDL_SCANCODE_RIGHT]) {
				   game.changePosX(1);
			   }
			   if (state[SDL_SCANCODE_UP]) {
				   game.changePosY(1);
			   }
			   if (state[SDL_SCANCODE_DOWN]) {
				   game.changePosY(-1);
			   }
			   if (state[SDL_SCANCODE_LEFT]) {
				   game.changePosX(-1);
			   }
			   if (state[SDL_SCANCODE_W]) {
				   game.changeZoom(-1);
			   }
			   if (state[SDL_SCANCODE_N]) {
				   game.changeZoom(+1);
			   }
			   if (state[SDL_SCANCODE_F]) {
				   renderThread->changeToFullScreen();
			   }
			   if (state[SDL_SCANCODE_X]) {
				   renderThread->changeToWindow();
			   }
			   if (state[SDL_SCANCODE_ESCAPE]) {
				   renderThread->quit = true;
			   }
			   if (state[SDL_SCANCODE_L]) {
				   game.changeAngle(true);
			   }
			   if (state[SDL_SCANCODE_R]) {
				   game.changeAngle(false);
			   }
			   break;
		   }
	   }
	   game.signalChange();
	}
   if (renderThread != NULL) {
	   delete renderThread;
   }

	return 0;
}
