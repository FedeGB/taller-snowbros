#include <iostream>
#include "Window.h"
#include <Box2D/Box2D.h>
#include <list>
#include "formasbox2d/shapes.h"
#include "utiles/Logger.h"
#include "parser/parser.h"

#define OKEXIT 0
#define LOADERROR -1

using namespace std;

bool loadInitialValues(std::string& sConfig);
bool windowInit(int widthScreen, int heightScreen);
void worldInit();
bool loopPrincipal();
void close();

Window* w = new Window();
b2World *worldB2D;


int main() {
	std::string sConfig;
	bool statusOK = true;
	statusOK = loadInitialValues(sConfig);
	if(!statusOK) {
		return LOADERROR;
	}
	int heightScreen=get_node("alto-px","escenario",sConfig,480);
	int widthScreen=get_node("ancho-px","escenario",sConfig,640);

	worldInit();
	list<shapes> _shapes;
	int formas =get_size("objetos",sConfig);
	for(int i=0;i<formas;i++){
		shapes temp(sConfig,worldB2D,i);
		_shapes.push_back(temp);
	}

	statusOK = windowInit(widthScreen, heightScreen);
	if(!statusOK) {
		return -1;
	}
	loopPrincipal();
	close();

	return OKEXIT;
}

bool loadInitialValues(std::string& sConfig) {
	Logger& log = * Logger::Instancia();
	//abre el json y lo carga a un string
	fstream fConfig;
	fConfig.open("config.json",ios_base::in);
	if(!fConfig.is_open()) {
		if (!log.abrirLog(MAINLOG)){
			std::cout << "Error al abrir archivo de log "<< MAINLOG << std::endl;
			return false;
		}

		log.escribirLog("ERROR", "No se pudo encontrar o abrir el archivo config.json");
		log.cerrarLog();
		return false;
	}
	std::string newStr((std::istreambuf_iterator<char>(fConfig)), std::istreambuf_iterator<char>());
	sConfig = newStr;
	fConfig.close();
	return true;
}

bool windowInit(int widthScreen, int heightScreen) {
	bool statusOK = w->init(widthScreen, heightScreen, "imagenes/fondo2.png");
	statusOK = w->insertarPersonaje(100, 100, 60, 50);
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

void close() {
	if(w) {
		delete w;
		w = NULL;
	}
	if(worldB2D) {
		delete worldB2D;
		worldB2D = NULL;
	}
}

void worldInit(){
	b2Vec2 gravedad(0, -9.8);
	worldB2D = new b2World(gravedad);
	return;
}
