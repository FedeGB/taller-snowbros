
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
    TCPStream * stream =  connector->connect("127.0.0.1", 2020);
    if (!stream){
    	std::cout << "Hubo un problema al conectar al servidor" << std::endl;
    	return -1;
    }

    std::string buffer;
    int len;
	// Recibo mi numero de cliente
	len = stream->receive(buffer);
	int clientNumber = atoi(buffer.c_str());

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
				else if (event.key.keysym.sym == SDLK_UP) outMessage = "UPPRESSED";
				else if (event.key.keysym.sym == SDLK_LEFT) outMessage = "LEFTPRESSED";
				else if (event.key.keysym.sym == SDLK_RIGHT) outMessage = "RIGHTPRESSED";
				else if (event.key.keysym.sym == SDLK_KP_PLUS) outMessage = "ZOOMINPRESSED";
				else if (event.key.keysym.sym == SDLK_KP_MINUS) outMessage = "ZOOMOUTPRESSED";
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP) outMessage = "UPRELEASED";
				else if (event.key.keysym.sym == SDLK_LEFT) outMessage = "LEFTRELEASED";
				else if (event.key.keysym.sym == SDLK_RIGHT) outMessage = "RIGHTRELEASED";
				else if (event.key.keysym.sym == SDLK_KP_PLUS) outMessage = "ZOOMINRELEASED";
				else if (event.key.keysym.sym == SDLK_KP_MINUS) outMessage = "ZOOMOUTRELEASED";
				break;
			}

			if (!outMessage.empty()) stream->send(outMessage);
		}

		// Informa que no hay mas eventos para esta iteracion.
		outMessage = "DONE";
		stream->send(outMessage);

		// Obtiene la metadata necesaria:
		inMessage.clear();
		len = stream->receive(inMessage);
		// Saltea si se recibe directamente DONE, ya que indica que todavia
		// no se cargo el PJ en el servidor.
		if (inMessage == "DONE") continue;
		WorldItem * item = Deserializador::deserializar(inMessage);
		// Escala de coordenadas mundo->ventana.
		float escala = ((Metadata*)item)->escala;

		// Recibe los mensajes correspondientes a lo que se debe dibujar.
		inMessage = "NOTDONE";
		while (inMessage != "DONE"){
			inMessage.clear();
			len = stream->receive(inMessage);
			if (len <= 0) {
				quit = true;
				break;
			}
			if(inMessage != "DONE") {
				item = Deserializador::deserializar(inMessage);
				itemList.push_back(item);
			}
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
