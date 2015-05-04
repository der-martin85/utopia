#include "SDL2/SDL.h"

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <pthread.h>

#include "Map.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Renderer * renderer = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

bool init() {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Create window
		gWindow = SDL_CreateWindow( "Utopia 3",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
			renderer = SDL_CreateRenderer(gWindow, 0, SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
}

void close() {
    SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}
bool quit = false;

static int rendererThread(void* param) {
	Map* f = (Map*)param;

//	std::cout << "start render" << std::endl;

	init();
	f->loadMedia(renderer);

	do {

		SDL_RenderClear(renderer);
//		std::cout << "render" << std::endl;
		f->render(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		SDL_RenderPresent(renderer);

		f->waitForChange();
	} while(!quit); //while(f->testAndDecrease());

//	std::cout << "done render" << std::endl;

	close();

	return 0;
}

int main(int argc, char* argv[]) {

    SDL_Event event;

    const int fieldx = 100;
    const int fieldy = 100;

	Map f = Map(fieldx, fieldy);
	f.generateMap();

    SDL_Thread *renderThread = NULL;

    renderThread = SDL_CreateThread(rendererThread, "RenderThread", (void *)(&f));

	while (!quit)
	{
	   SDL_WaitEvent(&event);

	   f.setMouseState();

	   switch(event.type)
	   {
	   case SDL_QUIT:
		   quit = true;
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
				   quit = true;
			   }
			   break;
		   }
	   }
	   f.signalChange();
	}
   if (renderThread != NULL) {
	   SDL_WaitThread(renderThread, NULL);
	   renderThread = NULL;
   }

	return 0;
}
