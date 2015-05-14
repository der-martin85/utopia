#include "SDL2/SDL.h"

#include <iostream>
#include <pthread.h>

#include "Map.h"
#include "RenderThread.h"
#include "SoundThread.h"
#include "menu/Menu.h"
#include <boost/filesystem.hpp>
#include <fstream>

//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 800;

int main(int argc, char* argv[]) {

    SDL_Event event;

    const int fieldx = 200;
    const int fieldy = 200;

    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 800;
    bool FullScreen = false;
    bool BackgroundMusic = true;
	boost::filesystem::path configFile("./config.ini");

    if (argc == 3) {
    	SCREEN_WIDTH = atoi(argv[1]);
    	SCREEN_HEIGHT = atoi(argv[2]);
    	FullScreen = true;
    } else {
    	if (boost::filesystem::exists(configFile) &&
    			boost::filesystem::is_regular_file(configFile))
    	{
    		std::ifstream cFile;
    		cFile.open(configFile.c_str());
    		cFile >> SCREEN_WIDTH >> SCREEN_HEIGHT >> FullScreen >> BackgroundMusic;
    		cFile.close();
    	}
    }


	//Map f = Map(fieldx, fieldy);
	//f.generateMap();
    Game game(fieldx, fieldy);
    game.generateMap(rand() % 16, rand() % 3, (rand() % 40) + 50);

	Menu menu;

	RenderThread* renderThread = RenderThread::startThread(SCREEN_WIDTH, SCREEN_HEIGHT, &game, &menu);
	if (renderThread == NULL) {
		return 0;
	}
	menu.setRenderThread(renderThread);
	game.setRenderThread(renderThread);

	if (FullScreen) {
		renderThread->changeToFullScreen();
	}
	SoundThread* soundThread = SoundThread::startThread(BackgroundMusic);

	while (!menu.quit)
	{
	   SDL_WaitEvent(&event);

	   int mX, mY;
	   SDL_GetMouseState(&mX, &mY);

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
			   if (!menu.click(mX, mY, mbe->button)) {
				   if (mbe->button == SDL_BUTTON_RIGHT) {
					   game.startDragging();
				   }
				   if (mbe->button == SDL_BUTTON_LEFT) {
					   // Feld markieren
					   game.startSelecting();
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
	   case SDL_MOUSEMOTION:
		   game.setMouseState(mX, mY);
		   break;
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
	   renderThread->signalChange();
	}

	std::ofstream cFile;
	cFile.open(configFile.c_str());
	cFile << renderThread->getScreenWidth() << std::endl;
	cFile << renderThread->getScreenHeight() << std::endl;
	cFile << renderThread->isFullscreen() << std::endl;
	cFile << soundThread->backgroundMusicOn() << std::endl;
	cFile.close();

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
