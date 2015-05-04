#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <stdio.h>
#include <time.h>
#include <iostream>

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

//The image we will load and show on the screen
SDL_Surface* ground[6] = {NULL, NULL, NULL, NULL, NULL, NULL};

SDL_Surface* selected = NULL;

SDL_Texture* groundTextures[6] = {NULL,NULL,NULL,NULL, NULL, NULL};

SDL_Texture* selectedTexture = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;

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

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    //gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
    ground[0] = IMG_Load("./images/sand.png");
    ground[1] = IMG_Load("./images/gras.png");
    ground[2] = IMG_Load("./images/trees.png");
    ground[3] = IMG_Load("./images/forest.png");
    ground[4] = IMG_Load("./images/water0.png");
    ground[5] = IMG_Load("./images/water1.png");

    selected = IMG_Load("./images/selected.png");
    if(ground[0] == NULL )
    {
        printf( "Unable to load image");
        success = false;
    }

    for (int i = 0; i < 6; i++) {
    	groundTextures[i] = SDL_CreateTextureFromSurface(renderer, ground[i]);
    }

    selectedTexture = SDL_CreateTextureFromSurface(renderer, selected);;

    return success;
}

void close() {
    for (int i = 0; i < 4; i++) {
    	SDL_DestroyTexture(groundTextures[i]);
    	//Deallocate surface
    	SDL_FreeSurface(ground[i]);
    }
    SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

int posX = 0;
int posY = 0;
int zoom = 16;

SDL_Rect isoTo2D(int x, int y) {
	SDL_Rect dstrect = {0, 0, zoom*4, zoom*4 };
	dstrect.x = (y + x)*2*zoom - posX*zoom;
	dstrect.y = (y - x)*zoom + posY*zoom;
	return dstrect;
}

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

int main(int argc, char* argv[]) {

    bool quit = false;
    SDL_Event event;

    const int fieldx = 100;
    const int fieldy = 100;

    int field[fieldx][fieldy];

    time_t t;
    time(&t);
    srand((unsigned int)t);              /* Zufallsgenerator initialisieren */


    for (int x = 0; x < fieldx; x++) {
        for (int y = 0; y < fieldy; y++) {
        	if (x > 0) {
        		if (y > 0) {
        			if (x < (fieldx-1)) {
        				field[x][y] = getField(field[x-1][y], field[x][y-1], field[x+1][y-1], field[x-1][y-1]);
        			} else {
        				field[x][y] = getField(field[x-1][y], field[x][y-1], field[x][y-1], field[x-1][y-1]);
        			}
        		} else {
       				field[x][y] = getField(field[x-1][y], field[x-1][y], field[x-1][y], field[x-1][y]);
        		}
        	} else if (y > 0) {
    			if (x < (fieldx-1)) {
    				field[x][y] = getField(field[x][y-1], field[x][y-1], field[x+1][y-1], field[x][y-1]);
    			} else {
    				field[x][y] = getField(field[x][y-1], field[x][y-1], field[x][y-1], field[x][y-1]);
    			}
    		} else {
        		field[x][y] = (rand() % 2) * 4;
    		}
        }
    }

	//Start up SDL and create window
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	} else {
		//Load media
		if( !loadMedia() ) {
			printf( "Failed to load media!\n" );
		} else {
			//Apply the image
			//SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			 //Update the surface
			//SDL_UpdateWindowSurface( gWindow );
			//Wait two seconds

		   int mX, mY;

			Sint32 mouseX;
			Sint32 mouseY;

			posX = (fieldy + fieldx);

			int selectedFields[4] = {-1, -1, -1, -1};

	        while (!quit)
	        {
	           SDL_WaitEvent(&event);

			   SDL_GetMouseState(&mX, &mY);
			   // Auf welchem Feld sind wir?
			   int mrX = mX + (posX * zoom);
			   int mrY = mY - (posY * zoom);
			   int miX = (mrX - ((mrY - (zoom*3))*2) ) / (4 * zoom);
			   int miY = ((mrX/2) + mrY - (zoom*3)) / (2 * zoom);

			   selectedFields[0] = miX;
			   selectedFields[1] = miY;

	           switch(event.type)
	           {
	           case SDL_QUIT:
	               quit = true;
	               break;
	           case SDL_MOUSEWHEEL:
	           	   {
					   const SDL_MouseWheelEvent* mwe = (SDL_MouseWheelEvent*)(&event);

					   int zoomOld = zoom;

					   zoom += mwe->y;
					   if (zoom < 3) {
						   zoom = 3;
					   }
					   if (zoom > 32) {
						   zoom = 32;
					   }

					   if (zoomOld != zoom) {
						   posX += (mX/zoomOld) - (mX/zoom);
						   posY -= (mY/zoomOld) - (mY/zoom);

						   if (posX < 0) {
							   posX = 0;
						   } else if (posX > (fieldy + fieldx)*2) {
							   posX = (fieldy + fieldx)*2;
						   }
						   if (posY < -(fieldy + fieldx) / 2) {
							   posY = -(fieldy + fieldx) / 2;
						   } else if (posY > (fieldy + fieldx) / 2) {
							   posY = (fieldy + fieldx) / 2;
						   }
					   }
					   break;
	           	   }
	           case SDL_MOUSEBUTTONDOWN:
	           	   {
	           		   const SDL_MouseButtonEvent* mbe = (SDL_MouseButtonEvent*)(&event);
	           		   if (mbe->button == SDL_BUTTON_RIGHT) {
	           			   mouseX = mbe->x;
	           			   mouseY = mbe->y;
	           		   }
	           		   if (mbe->button == SDL_BUTTON_LEFT) {
	           			   // Feld markieren
	           			   if (selectedFields[0] >= 0 &&
	           					   selectedFields[1] >= 0 &&
								   selectedFields[0] < fieldx &&
								   selectedFields[1] < fieldy) {
		    	        	   selectedFields[2] = selectedFields[0];
		    	        	   selectedFields[3] = selectedFields[1];
	           			   }
	           		   }
	           		   break;
	           	   }
	           case SDL_MOUSEBUTTONUP:
	           	   {
	           		   const SDL_MouseButtonEvent* mbe = (SDL_MouseButtonEvent*)(&event);
	           		   if (mbe->button == SDL_BUTTON_RIGHT) {
	           			   Sint32 changeX = (mouseX - mbe->x) / zoom;
	           			   Sint32 changeY = (mbe->y - mouseY) / zoom;
	           			   posX += changeX;
	           			   posY += changeY;
	           			   if (posX < 0) {
	           				   posX = 0;
	           			   } else if (posX > (fieldy + fieldx)*2) {
	           				   posX = (fieldy + fieldx)*2;
	           			   }
	           			   if (posY < -(fieldy + fieldx) / 2) {
	           				   posY = -(fieldy + fieldx) / 2;
	           			   } else if (posY > (fieldy + fieldx) / 2) {
	           				   posY = (fieldy + fieldx) / 2;
	           			   }
	           		   }
	           		   if (mbe->button == SDL_BUTTON_LEFT) {
	           			   // Feld markieren
	           			   if (selectedFields[2] > -1) {
							   const int minX = selectedFields[0] > selectedFields[2] ? selectedFields[2] : selectedFields[0];
							   const int minY = selectedFields[1] > selectedFields[3] ? selectedFields[3] : selectedFields[1];
							   const int maxX = selectedFields[0] > selectedFields[2] ? selectedFields[0] : selectedFields[2];
							   const int maxY = selectedFields[1] > selectedFields[3] ? selectedFields[1] : selectedFields[3];

							   for (int iX = minX; iX <= maxX; iX++) {
								   for (int iY = minY; iY <= maxY; iY++) {
									   field[iX][iY] = 0;
								   }
							   }

							   selectedFields[2] = -1;
							   selectedFields[3] = -1;
	           			   }
	           		   }
	           		   break;
	           	   }
	           case SDL_KEYDOWN:
	           	   {
					   const Uint8 *state = SDL_GetKeyboardState(NULL);
					   if (state[SDL_SCANCODE_RIGHT]) {
						   if (posX < (fieldy + fieldx)*2) {
							   posX += 2;
						   }
					   }
					   if (state[SDL_SCANCODE_UP]) {
						   if (posY < (fieldy + fieldx) / 2) {
							   posY += 1;
						   }
					   }
					   if (state[SDL_SCANCODE_DOWN]) {
						   if (posY > -(fieldy + fieldx) / 2) {
							   posY -= 1;
						   }
					   }
					   if (state[SDL_SCANCODE_LEFT]) {
						   if (posX > 0) {
							   posX -= 2;
						   }
					   }
					   if (state[SDL_SCANCODE_W]) {
						   if (zoom > 3) {
							   zoom--;
						   }
					   }
					   if (state[SDL_SCANCODE_N]) {
						   if (zoom < 32) {
							   zoom++;
						   }
					   }
					   if (state[SDL_SCANCODE_F]) {
						   SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
					   }
					   if (state[SDL_SCANCODE_X]) {
						   SDL_SetWindowFullscreen(gWindow, 0);
					   }
					   if (state[SDL_SCANCODE_Q]) {
						   quit = true;
					   }
					   break;
	           	   }
	           }

	           SDL_RenderClear(renderer);

        	   for (int y = 0; y < fieldy; y++) {
        		   for (int x = fieldx-1; x >= 0 ; x--) {
        	           SDL_Rect dstrect = isoTo2D(x, y);
        	           if (dstrect.x + dstrect.w > 0 && dstrect.y + dstrect.h > 0 &&
        	        		   dstrect.x < SCREEN_WIDTH && dstrect.y < SCREEN_HEIGHT) {
        	        	   SDL_RenderCopy(renderer, groundTextures[field[x][y]], NULL, &dstrect);
        	        	   if (((selectedFields[2] > -1) &&
        	        			   ((x >= selectedFields[0] && x <= selectedFields[2]) ||
        	        					   (x <= selectedFields[0] && x >= selectedFields[2])) &&
								   ((y >= selectedFields[1] && y <= selectedFields[3]) ||
           	        					   (y <= selectedFields[1] && y >= selectedFields[3]))) ||
        	        			   (x == selectedFields[0] && y == selectedFields[1])) {
        	    			   SDL_Rect sdstrect = {dstrect.x, dstrect.y+(dstrect.h/2), zoom*4, zoom*2 };
        	    			   SDL_RenderCopy(renderer, selectedTexture, NULL, &sdstrect);
        	        	   }
        	           }
        		   }
        	   }

	           SDL_RenderPresent(renderer);
	        }

		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
