
#include <iostream>
#include "sockets/TCPConnector.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <sstream>
#include <list>

#include "utiles/Deserializador.h"
#include "vista/Window.h"
#include "utiles/tipos.h"
#include "utiles/Timer.h"



Window * window;
std::list<WorldItem*> itemList;

int main(int argc, char * argv[]){


	//The frames per second timer
	Timer fpsTimer;
	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();

	// Inicializo la ventana.
	window = new Window();
	std::string path_fondo = "imagenes/fondo2.png";
	bool statusOK = window->init(720, 640, path_fondo);
	if (!statusOK) {
		std::cout << "Hubo un error al crear la ventana" << std::endl;
		return -1;
	}

	// Conecto al servidor.
    TCPConnector * connector = new TCPConnector();
    TCPStream * stream =  connector->connect("192.168.0.109", 2020);
    if (!stream){
    	std::cout << "Hubo un problema al conectar al servidor" << std::endl;
    	return -1;
    }

    std::string username = argv[1];
    int len;
	// Inicia la comunicacion enviando el nombre de usuario.
	len = stream->send(username);
	if (len <= 0) {
		//TODO: error handling
		std::cout << "error al enviar username" << std::endl;
		return 1;
	}

    // Loop de recoleccion de eventos y envio de mensajes.
	SDL_Event event;
	bool quit = false;
	std::string outMessage, inMessage;

	while( !quit ){

		// Analiza los eventos que sean relevantes para enviarlos al servidor.
		while( SDL_PollEvent( &event ) != 0 ) {
			//continue;
			outMessage.clear();
			switch(event.type){
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym  == SDLK_r) ;
				else if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
				else if (event.key.keysym.sym == SDLK_UP) outMessage = SSTR(ARRIBA);
				else if (event.key.keysym.sym == SDLK_LEFT) outMessage = SSTR(IZQUIERDA);
				else if (event.key.keysym.sym == SDLK_RIGHT) outMessage = SSTR(DERECHA);
				else if (event.key.keysym.sym == SDLK_KP_PLUS) outMessage = SSTR(ZOOMIN);
				else if (event.key.keysym.sym == SDLK_KP_MINUS) outMessage = SSTR(ZOOMOUT);
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP) outMessage = SSTR(SOLTOARRIBA);
				else if (event.key.keysym.sym == SDLK_LEFT) outMessage = SSTR(SOLTOIZQUIERDA);
				else if (event.key.keysym.sym == SDLK_RIGHT) outMessage = SSTR(SOLTODERECHA);
				break;
			}

			if (!outMessage.empty()) stream->send(outMessage);
		}

		// Informa que no hay mas eventos para esta iteracion.
		outMessage = "DONE";
		stream->send(outMessage);

		// Obtiene la pantalla serializada, con cada elemento separado por %.
		inMessage.clear();
		len = stream->receive(inMessage);
		if (len <= 0) {
			quit = true;
		}

		// Saltea si se recibe un mensaje vacio, ya que indica que todavia
		// no se cargo el PJ en el servidor.
		if (inMessage == "EMPTY") continue;

		// Separa todos los elementos para deserializarlos uno por uno.
		std::vector<std::string> buff;
		split(buff, inMessage, "%", no_empties);

		// El primer elemento es metadata.
		WorldItem * item = Deserializador::deserializar(buff[0]);
		// Escala de coordenadas mundo->ventana.
		float escala = ((Metadata*)item)->escala;

		// Itera sobre todos los elementos restantes.
		for (std::vector<std::string>::iterator it = buff.begin(); it != buff.end(); it++){
			item = Deserializador::deserializar((*it));
			itemList.push_back(item);
		}

		window->updateWindow(itemList, escala);

		float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
		if (avgFPS > 2000) {
			fpsTimer.stop();
			fpsTimer.start();
			countedFrames = 0;
		}
		std::cout << avgFPS << " FPS avg" << std::endl;
		++countedFrames;

	}

	return 0;
}
