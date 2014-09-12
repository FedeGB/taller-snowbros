#include <iostream>
#include "Window.h"
#include <Box2D/Box2D.h>
#include <list>
#include "formasbox2d/shapes.h"

#include "parser/parser.h"

using namespace std;

bool init();
void worldInit();
bool loopPrincipal();
bool close();

Window* w = new Window();
int heightScreen;
int widthScreen;
b2World *worldB2D;


int main() {
	//abre el json y lo carga a un string
	fstream fConfig;
	fConfig.open("config.json",ios_base::in);
	string sConfig((std::istreambuf_iterator<char>(fConfig)), std::istreambuf_iterator<char>());;
	fConfig.close();

	heightScreen=get_node("alto-px","escenario",sConfig,480);
	widthScreen=get_node("ancho-px","escenario",sConfig,640);

	worldInit();
	list<shapes> _shapes;
	int formas =get_size("objetos",sConfig);
	for(int i=0;i<formas;i++){
		shapes temp(sConfig,worldB2D,i);
		_shapes.push_back(temp);
	}

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
	bool statusOK = w->init(widthScreen, heightScreen);
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

void worldInit(){
	b2Vec2 gravedad(0, -9.8);
	worldB2D = new b2World(gravedad);
	return;
}
