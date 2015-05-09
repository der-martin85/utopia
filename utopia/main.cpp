#include "SDL2/SDL.h"

#include <iostream>
#include <pthread.h>

#include "Map.h"
#include "RenderThread.h"
#include "SoundThread.h"
#include "Menu.h"

//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 800;

int main(int argc, char* argv[]) {

    SDL_Event event;

    const int fieldx = 200;
    const int fieldy = 200;

    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 800;
    bool FullScreen = false;

    if (argc == 3) {
    	SCREEN_WIDTH = atoi(argv[1]);
    	SCREEN_HEIGHT = atoi(argv[2]);
    	FullScreen = true;
    }

	//Map f = Map(fieldx, fieldy);
	//f.generateMap();
    Game game(fieldx, fieldy);
    game.generateMap(rand() % 16, rand() % 3, (rand() % 40) + 50);

	RenderThread* renderThread = RenderThread::startThread(SCREEN_WIDTH, SCREEN_HEIGHT, &game);
	if (renderThread == NULL) {
		return 0;
	}

	if (FullScreen) {
		renderThread->changeToFullScreen();
	}
	SoundThread* soundThread = SoundThread::startThread();

	Menu menu;

	while (!menu.quit)
	{
	   SDL_WaitEvent(&event);

	   int mX, mY;
	   SDL_GetMouseState(&mX, &mY);

	   game.setMouseState(mX, mY);
	   menu.setMouseState(mX, mY);

	   switch(event.type)
	   {
	   case SDL_QUIT:
		   menu.quit = true;
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
			   if (mX >= 100) {
				   if (mbe->button == SDL_BUTTON_RIGHT) {
					   game.startDragging();
				   }
				   if (mbe->button == SDL_BUTTON_LEFT) {
					   // Feld markieren
					   game.startSelecting();
				   }
			   } else {
				   if (mbe->button == SDL_BUTTON_LEFT) {
					   menu.click();
				   }
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
				   menu.quit = true;
			   }
			   if (state[SDL_SCANCODE_L]) {
				   game.changeAngle(true);
			   }
			   if (state[SDL_SCANCODE_R]) {
				   game.changeAngle(false);
			   }
			   if (state[SDL_SCANCODE_G]) {
				   game.generateMap(rand() % 16, rand() % 3, (rand() % 40) + 50);
			   }
			   break;
		   }
	   }
	   game.signalChange();
	}
	if (renderThread != NULL) {
	   delete renderThread;
	}
	if (soundThread != NULL) {
	   delete soundThread;
	}
	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
