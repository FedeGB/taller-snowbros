#include <iostream>
#include "Window.h"

using namespace std;

Window w;

void init();
bool loopPrincipal();
bool close();

int main() {

	init();
	loopPrincipal();
	close();

	return 0;
}

void init() {
	w.init(640, 480);
}

bool loopPrincipal() {

	SDL_Event event;
	bool quit = false;

	while( !quit )
	{
		while( SDL_PollEvent( &event ) != 0 )
		{
			if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE )
				quit = true;
			w.handleEvent(event);
		}
		w.updateWindow();
	}

	return 0;
}

bool close() {}
