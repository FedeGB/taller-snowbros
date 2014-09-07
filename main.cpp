#include <iostream>
#include "Window.h"

using namespace std;

bool init();
bool loopPrincipal();
bool close();

Window* w = new Window();

int main() {
	bool statusOK = true;
	statusOK = init();
	if(!statusOK) {
		return -1;
	}
	loopPrincipal();
	close();

	return 0;
}

bool init() {

	bool statusOK = w->init(640, 480);
	return statusOK;
}

bool loopPrincipal() {

	SDL_Event event;
	bool quit = false;
	bool statusOK = true;

	while( !quit )
	{
		while( SDL_PollEvent( &event ) != 0 )
		{
			if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE )
				quit = true;
			w->handleEvent(event);
		}
		statusOK =w->updateWindow();
		if(!statusOK) {
			if (w) {
				delete w;
			}
			return -1;
		}

	}

	return 0;
}

bool close() {
	delete w;
	return true;
}
