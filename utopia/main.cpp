#include "SDL2/SDL.h"

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <pthread.h>
#include "field.h"

//int propabilities[17][6] = {
//		{40, 65, 85, 97, 100, 0},	// ss
//		{20, 60, 80, 97, 100, 0},	// gg
//		{10, 20, 60, 97, 100, 0},	// tt
//		{10, 30, 55, 97, 100, 0},	// ff
//		{4, 8, 12, 16, 65, 100},	// ww
//		{0, 0, 0, 0, 30, 100},	// dd
//		{30, 60, 85, 97, 100, 0},	// sg
//		{30, 50, 80, 97, 100, 0},	// st
//		{30, 50, 70, 97, 100, 0},	// sf
//		{30, 50, 60, 67, 100, 0},	// sw
//		{10, 40, 70, 97, 100, 0},	// gt
//		{10, 40, 60, 97, 100, 0},	// gf
//		{10, 40, 60, 67, 100, 0},	// gw
//		{10, 20, 50, 97, 100, 0},	// tf
//		{10, 20, 40, 65, 100, 0},	// tw
//		{10, 20, 40, 65, 100, 0},	// fw
//		{0, 0, 0, 0, 40, 100}		// wd
//};

int propabilities[16] = {
		90,
		99,
		70,
		100,
		60,
		80,
		40,
		30,
		60,
		50,
		20,
		1,
		1,
		50,
		1,
		90
};


int getField(int a, int b, int c, int d) {
	int state = (a/4)*8 + (b/4)*4 + (c/4)*2 + (d/4);
	int r = rand() % 100;
	if (r >= propabilities[state]) {
		return 4;
	}
	return 0;
}

static int renderField(void* param) {
	field* f = (field*)param;

	std::cout << "start render" << std::endl;

	do {
		std::cout << "render" << std::endl;
		f->render();
	} while(f->testAndDecrease());

	std::cout << "done render" << std::endl;

	return 0;
}

int main(int argc, char* argv[]) {

    bool quit = false;
    SDL_Event event;

    const int fieldx = 100;
    const int fieldy = 100;

	field f = field(fieldx, fieldy);

    time_t t;
    time(&t);
    srand((unsigned int)t);              /* Zufallsgenerator initialisieren */


    for (int x = 0; x < fieldx; x++) {
        for (int y = 0; y < fieldy; y++) {
//        	if (x > 0) {
//        		if (y > 0) {
//        			if (x < (fieldx-1)) {
//        				field[x][y] = getField(field[x-1][y], field[x][y-1], field[x+1][y-1], field[x-1][y-1]);
//        			} else {
//        				field[x][y] = getField(field[x-1][y], field[x][y-1], field[x][y-1], field[x-1][y-1]);
//        			}
//        		} else {
//       				field[x][y] = getField(field[x-1][y], field[x-1][y], field[x-1][y], field[x-1][y]);
//        		}
//        	} else if (y > 0) {
//    			if (x < (fieldx-1)) {
//    				field[x][y] = getField(field[x][y-1], field[x][y-1], field[x+1][y-1], field[x][y-1]);
//    			} else {
//    				field[x][y] = getField(field[x][y-1], field[x][y-1], field[x][y-1], field[x][y-1]);
//    			}
//    		} else {
        		f.map[x][y] = (rand() % 2) * 4;
//    		}
        }
    }

    SDL_Thread *renderThread = NULL;

	//f.render();

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

//	   f.render();
	   if (!f.stillRunning()) {
		   if (renderThread != NULL) {
			   SDL_WaitThread(renderThread, NULL);
			   renderThread = NULL;
		   }
		   renderThread = SDL_CreateThread(renderField, "RenderThread", (void *)(&f));
	   }
	   f.increaseRuns();

	}
   if (renderThread != NULL) {
	   SDL_WaitThread(renderThread, NULL);
	   renderThread = NULL;
   }

	return 0;
}
