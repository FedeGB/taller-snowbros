#include <iostream>
#include <Box2D/Box2D.h>

#include "control/HandlerDeEventos.h"
#include "control/ContactListener.h"

#include "Window.h"
#include "Inicializador.h"

using namespace std;

bool loopPrincipal();
void wClose();

Window* w;
b2World *worldB2D;
Inicializador inicializador;
ContactListener contactListener;
HandlerDeEventos wHandlerEventos;

int main() {

	inicializador.init(&w, &worldB2D, &contactListener, &wHandlerEventos);
	loopPrincipal();
	wClose();

	return 0;
}

bool loopPrincipal() {
	SDL_Event event;
	bool quit = false;
	bool statusOK = true;

	while( !quit )
	{
		while( SDL_PollEvent( &event ) != 0 ) {
			switch(event.type){
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym  == SDLK_r){
					wClose();
					inicializador.init(&w, &worldB2D, &contactListener, &wHandlerEventos);
				} else if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
				else wHandlerEventos.manejarEventoTeclado(event.key);
				break;
			case SDL_KEYUP:
				wHandlerEventos.manejarEventoTeclado(event.key);
				break;
			}
		}

		worldB2D->Step(1.0f/60.0f, 8, 5);
		statusOK = w->updateWindow(worldB2D);

		if(!statusOK) {
			if (w) {
				delete w;
				w = NULL;
			}
			return -1;
		}

		SDL_Delay(25);
	}

	return statusOK;
}

void wClose() {
	if(w) {
		delete w;
		w = NULL;
	}
	if(worldB2D) {
		delete worldB2D;
		worldB2D = NULL;
	}
}

