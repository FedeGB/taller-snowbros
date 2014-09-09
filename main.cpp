#include <iostream>
#include "Window.h"

#include "parser/parser.h"

using namespace std;

bool init();
bool loopPrincipal();
bool close();

Window* w = new Window();

int main() {

	fstream fConfig;
	fConfig.open("config.json",ios_base::in);
	string sConfig((std::istreambuf_iterator<char>(fConfig)), std::istreambuf_iterator<char>());;
	fConfig.close();
	int altoPx=atoi(get_node("alto-px","escenario",sConfig,"200").c_str());
	int anchoPx=atoi(get_node("ancho-px","escenario",sConfig,"200").c_str());

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
		statusOK = w->updateWindow();
		if(!statusOK) {
			if (w) {
				delete w;
				w = NULL;
			}
			return -1;
		}
		SDL_Delay(25);
	}

	return 0;
}

bool close() {
	if(w) {
		delete w;
	}
	return true;
}
