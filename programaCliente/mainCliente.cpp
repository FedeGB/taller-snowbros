
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

int isNumber(const char* string);
bool ipValid(string ip);
bool isValidIPNumber(string token);
bool isValidPort(int puerto);

Window * window;
std::list<WorldItem*> itemList;
TCPStream * stream;

bool esperarPorMasJugadores(){

	ssize_t len;
	std::string inMessage;
	SDL_Event event;

	// Espera a que el server arranque la simulacion, mostrando una pantalla de espera.
	while(inMessage != "SERVER-LISTO") {

		std::cout << "estoy esperando... recibi: " << inMessage << std::endl;

		len = stream->receive(inMessage);
		if (len <= 0) {
			std::cout << "conexion perdida con el servidor" << std::endl;
			return false;
		}

		while( SDL_PollEvent( &event ) != 0 ) {
			switch(event.type){
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) return false;
			}
		}

		Metadata * pantallaIntroFondo = new Metadata();;
		Metadata * pantallaIntroHUD = new Metadata();;
		pantallaIntroFondo->posXCamara = 0;
		pantallaIntroFondo->posYCamara = 0;
		pantallaIntroFondo->anchoCamara = 1;
		pantallaIntroFondo->altoCamara = 1;
		pantallaIntroFondo->tamanioXMundo = 720;
		pantallaIntroFondo->tamanioYMundo = 640;
		pantallaIntroFondo->tipo = METADATAFONDO;
		pantallaIntroHUD->vidas[0] = pantallaIntroHUD->vidas[1] =
				pantallaIntroHUD->vidas[2] = pantallaIntroHUD->vidas[3] = 0;
		pantallaIntroHUD->users[0] = "offline"; //username;
		pantallaIntroHUD->users[1] = pantallaIntroHUD->users[2] = pantallaIntroHUD->users[3] = "offline";
		pantallaIntroHUD->puntaje = 0;
		pantallaIntroHUD->mensaje.clear();
		pantallaIntroHUD->mensaje = "NOMESSAGE-Esperando-mas-conexiones...";

		itemList.push_back(pantallaIntroFondo);
		itemList.push_back(pantallaIntroHUD);

		window->updateWindow(itemList,1.0f);
	}

	return true;
}

bool protocoloFinDePartida(resultado_t resultado){

	SDL_Event event;
	bool quit = false;
	bool continuePlaying = false;
	std::string outMessage;

	// Espera a que el jugador de una respuesta.
	while(!quit) {

		while( SDL_PollEvent( &event ) != 0 ) {
			switch(event.type){
			case SDL_QUIT:
				outMessage = "STOPPLAYING";
				stream->send(outMessage);
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					outMessage = "STOPPLAYING";
					stream->send(outMessage);
					quit = true;
				}
				if (event.key.keysym.sym == SDLK_y) {
					outMessage = "CONTINUEPLAYING";
					stream->send(outMessage);
					continuePlaying = true;
					quit = true;
				}
				if (event.key.keysym.sym == SDLK_n) {
					outMessage = "STOPPLAYING";
					stream->send(outMessage);
					quit = true;
				}
			}
		}

		stream->send("DONE");

		Metadata * pantallaIntroFondo = new Metadata();;
		Metadata * pantallaIntroHUD = new Metadata();;
		pantallaIntroFondo->posXCamara = 0;
		pantallaIntroFondo->posYCamara = 0;
		pantallaIntroFondo->anchoCamara = 1;
		pantallaIntroFondo->altoCamara = 1;
		pantallaIntroFondo->tamanioXMundo = 720;
		pantallaIntroFondo->tamanioYMundo = 640;
		pantallaIntroFondo->tipo = METADATAFONDO;
		pantallaIntroHUD->vidas[0] = pantallaIntroHUD->vidas[1] =
				pantallaIntroHUD->vidas[2] = pantallaIntroHUD->vidas[3] = 0;
		pantallaIntroHUD->users[0] = "offline"; //username;
		pantallaIntroHUD->users[1] = pantallaIntroHUD->users[2] = pantallaIntroHUD->users[3] = "offline";
		pantallaIntroHUD->puntaje = 0;
		pantallaIntroHUD->mensaje.clear();
		if (resultado == GANARON) pantallaIntroHUD->mensaje = "NOMESSAGE-Ganaron!&Deseas-jugar-de-nuevo?-Y/N";
		else pantallaIntroHUD->mensaje = "NOMESSAGE-Han sido derrotados.&Deseas-jugar-de-nuevo?-Y/N";

		itemList.push_back(pantallaIntroFondo);
		itemList.push_back(pantallaIntroHUD);

		window->updateWindow(itemList,1.0f);
	}

	if(continuePlaying == true) {
		std::cout << "voy a esperar al resto" << std::endl;
		return esperarPorMasJugadores();
	}

	std::cout << "me cago en todo." << std::endl;
	return false;
}

int main(int argc, char * argv[]){

	if ( argc != 7 ) {
		printf("Uso: %s -u <username> -p <Puerto> -i <IP>\n", argv[0]);
		return -1;
	}

	// Process command line arguments
	int opt, uflag, pflag, iflag, port;
	opt = uflag = pflag = iflag = port = 0;
	std::string username (" "); // username
	std::string ip (""); // IP en el que escucha.

	while( (opt = getopt(argc, argv, "u:p:i:")) != -1 ) {
		switch(opt) {
		case 'u':
			uflag = 1;
			username = std::string(optarg);
			break;
		case 'p':
			if(!isNumber(optarg)) {
				printf("El puerto %s especificado debe ser un numero\n", optarg);
				return -1;
			}
			pflag = 1;
			port = atoi(optarg); // Puerto en el que escucha a las conexiones.
			printf("puerto ingresado: %i\n", port);
			break;
		case 'i':
			iflag = 1;
			ip = std::string(optarg);
			break;
		case '?':
			if(optopt == 'u') {
				printf("Al parametro -u le falta el username\n");
			}
			else if(optopt == 'p') {
				printf("Al parametro -p le falta especificar el puerto\n");
			}
			else if(optopt == 'i') {
				printf("Al parametro -i le faltaria especificar una ip, si no quiere especificar una, no utilice el argumento -i\n");
			}
			else {
				printf("Parametro -%c no reconocido\n", optopt);
			}
			return -1;
		default:
			printf("Error no esperado en el procesamiento de comandos\n");
			exit(-1);
		}
   }
	if (!pflag) {
	   printf("No se especifico puerto con el comando -p\n");
	   return -1;
	} else {
		if(!isValidPort(port)) {
			printf("El puerto %d no es valido, ingrese un puerto entre 1024 y 49151\n", port);
			return -1;
		}
	}

	if (iflag) {
		if(!ipValid(ip)){
			printf("la ip ingresada es invalida\n");
			return -1;
		}
	}

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
    stream =  connector->connect(ip.c_str(), port);
    if (!stream){
    	std::cout << "Hubo un problema al conectar al servidor" << std::endl;
    	return -1;
    }

    int len;
	// Inicia la comunicacion enviando el nombre de usuario.
	len = stream->send(username);
	if (len <= 0) {
		//TODO: error handling
		std::cout << "error al enviar username" << std::endl;
		return 1;
	}

	// Espero por mensaje de OK o RECHAZO.
	std::string inMessage;
	len = stream->receive(inMessage);
	if (inMessage == "RECHAZADA-FULL"){
		printf ("Conexion rechazada por el servidor.\n");
		printf ("Numero de conexiones maximas alcanzadas.\n");
		return 0;
	}else if (inMessage == "RECHAZADA-USR"){
		printf ("Conexion rechazada por el servidor.\n");
		printf ("El usuario elegido esta online.\n");
		return 0;
	}else if (inMessage == "OK"){
		printf ("Conexion con el server establecida.\n");
	}

    // Loop de recoleccion de eventos y envio de mensajes.
	SDL_Event event;
	bool quit = false;
	bool gameOver =false;
	std::string outMessage;

	// Espera a que el server arranque la simulacion, mostrando una pantalla de espera.
	quit = !esperarPorMasJugadores();

	while( !quit ){

		std::cout << "entre al main loop" << std::endl;

		// Analiza los eventos que sean relevantes para enviarlos al servidor.
		while( SDL_PollEvent( &event ) != 0 ) {
			//continue;
			outMessage.clear();
			switch(event.type){
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
				else if (event.key.keysym.sym == SDLK_UP) outMessage = SSTR(ARRIBA);
				else if (event.key.keysym.sym == SDLK_LEFT) outMessage = SSTR(IZQUIERDA);
				else if (event.key.keysym.sym == SDLK_RIGHT) outMessage = SSTR(DERECHA);
				else if (event.key.keysym.sym == SDLK_PAGEUP) outMessage = SSTR(ZOOMIN);
				else if (event.key.keysym.sym == SDLK_PAGEDOWN) outMessage = SSTR(ZOOMOUT);
				else if (event.key.keysym.sym == SDLK_SPACE) outMessage = SSTR(SPACE);
				else if (event.key.keysym.sym == SDLK_a) outMessage = SSTR(a);
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP) outMessage = SSTR(SOLTOARRIBA);
				else if (event.key.keysym.sym == SDLK_LEFT) outMessage = SSTR(SOLTOIZQUIERDA);
				else if (event.key.keysym.sym == SDLK_RIGHT) outMessage = SSTR(SOLTODERECHA);
				else if (event.key.keysym.sym == SDLK_SPACE) outMessage = SSTR(SOLTOSPACE);
				break;
			}
			std::cout << "estoy polleando eventos: " << outMessage << std::endl;

			if (!outMessage.empty()) stream->send(outMessage);
		}

		std::cout << "termine de pollear eventos. " << std::endl;


		// Informa que no hay mas eventos para esta iteracion.
		outMessage = "DONE";
		stream->send(outMessage);

		std::cout << "envie el fin de poll de eventos" << std::endl;


		// Obtiene la pantalla serializada, con cada elemento separado por %.
		inMessage.clear();
		len = stream->receive(inMessage);
		if (len <= 0) {
			quit = true;
			std::cout << "conexion perdida con el servidor" << std::endl;
			continue;
		}

		std::cout << "se recibio el siguiente escenario: " << inMessage << std::endl;

		// Saltea si se recibe un mensaje vacio, ya que indica que todavia
		// no se cargo el PJ en el servidor.
		if (inMessage == "EMPTY") continue;

		std::cout << "voy a separar los elementos recibidos." << std::endl;

		// Separa todos los elementos para deserializarlos uno por uno.
		std::vector<std::string> buff;
		split(buff, inMessage, "%", no_empties);

		// Si recibe "GAMEENDED" indica que se tiene que iniciar el protocolo de fin de partida.
		if(buff[0] == "GAMEENDED"){
			quit = !protocoloFinDePartida((resultado_t) strtol(buff[1].c_str(),NULL,10));
			continue;
		}

		std::cout << "deserializando la escala del mundo." << std::endl;

		// El primer elemento es metadata.
		WorldItem * item = Deserializador::deserializar(buff[0]);
		// Escala de coordenadas mundo->ventana.
		float escala = ((Metadata*)item)->escala;
		delete item;
		item = NULL;

		std::cout << "iterando sobre todas las cosas del mundo a deserializar." << std::endl;

		// Itera sobre todos los elementos restantes.
		for (std::vector<std::string>::iterator it = buff.begin(); it != buff.end(); it++){
			item = Deserializador::deserializar((*it));
			if (!item) continue;
			itemList.push_back(item);
			/*if(item->tipo==METADATAHUD){
				for(int i=0;i<4;i++){
					if(((Metadata*)item)->users[i].compare(username)==0){
						if(((Metadata*)item)->vidas[i]==0){
							quit=true;
							gameOver=true;
							std::cout<<"Game Over"<<std::endl;
						}
					}
				}
			}*/
		}

		window->updateWindow(itemList, escala);

		float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
		if (avgFPS > 2000) {
			fpsTimer.stop();
			fpsTimer.start();
			countedFrames = 0;
		}
		//std::cout << avgFPS << " FPS avg" << std::endl;
		++countedFrames;

	}
	while(gameOver){
		window->setGameOver();
		while( SDL_PollEvent( &event ) != 0 ) {
		if(event.type== SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_ESCAPE) gameOver = false;
		}
	}

	delete window;

	return 0;
}

int isNumber(const char* string) {
	std::string var;
	if(!string) {
		return 0;
	} else {
		var  = string;
	}
	for(unsigned int i = 0; i < var.length(); i++) {
		if(!isdigit(var[i])) {
			return 0;
		}
	}
	return 1;
}

bool ipValid(string ip){
	if(ip == "localhost") return true;
	if(ip.length()<8 || ip.length()>16)
		return false;
	string token ,temp=ip;
	while (token != temp){
		token = temp.substr(0,temp.find_first_of("."));
		temp = temp.substr(temp.find_first_of(".") + 1);
		if(!isValidIPNumber(token)) {
			return false;
		}
	}
	return true;
}

bool isValidIPNumber(string token) {
	if(isNumber(token.c_str())) {
		int number = atoi(token.c_str());
		if (number < 0 || number > 255) {
			return false;
		}
	} else {
		return false;
	}
	return true;
}

bool isValidPort(int puerto) {
	if(puerto < 1024 || puerto > 49151) {
		return false;
	}
	return true;
}
