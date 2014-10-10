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
string configFile;

int main(int argc, char *argv[]) {

	Logger& log = *Logger::Instancia();

	log.log(MAINLOG,OK,"Iniciando SnowBros...");

	if (argc < 2) {
		log.log(MAINLOG,ERROR,"No se proporciono archivo de configuracion. Cargando mapa por defecto.");
		configFile = "defaultConfig.json";
	} else configFile = argv[1];

	if (inicializador.init(configFile, &w, &worldB2D, &contactListener, &wHandlerEventos) ) loopPrincipal();
	wClose();

	log.log(MAINLOG,OK,"SnowBros ha finalizado correctamente.");

	return 0;
}

bool loopPrincipal() {
	Logger& log = *Logger::Instancia();

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
					if (!log.abrirLog(MAINLOG))
						std::cout << "Error al abrir archivo de log " << MAINLOG << std::endl;
					else {
						log.escribirLog(OK, "Reiniciando SnowBros...");
						log.cerrarLog();
					}
					inicializador.init(configFile, &w, &worldB2D, &contactListener, &wHandlerEventos);
				} else if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
				else wHandlerEventos.manejarEventoTeclado(event.key);
				break;
			case SDL_KEYUP:
				wHandlerEventos.manejarEventoTeclado(event.key);
				break;
			}
		}
		for(int i=0;i<10;i++)
			worldB2D->Step(1.0f/600.0f, 8, 5);
		statusOK = w->updateWindow(worldB2D);

		if(!statusOK) {
			wClose();
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

