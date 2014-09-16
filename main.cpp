#include <iostream>
#include "Window.h"
#include <Box2D/Box2D.h>
#include <list>
#include "formasbox2d/shape.h"
#include "utiles/Logger.h"
#include "parser/parser.h"

#define OKEXIT 0
#define LOADERROR -1

using namespace std;

bool loadInitialValues(std::string& sConfig);
bool windowInit(int widthScreen, int heightScreen);
void worldInit(float w,float h);
bool loopPrincipal();
void wClose();

Window* w;
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

	float heightWorld=480; //get_node("alto-un","escenario",sConfig,10.0f);
	float widthWorld=640; //get_node("ancho-un","escenario",sConfig,10.0f);

	float heightRatio=heightScreen/heightWorld;
	float widthRatio=widthScreen/widthWorld;

	worldInit(widthWorld,heightWorld);

	statusOK = windowInit(widthScreen, heightScreen);
	if(!statusOK) {
		return -1;
	}

	//list<shape> objectsList;
	int formas =get_size("objetos",sConfig);
	shape * temp;
	for(int i=0;i<formas;i++){
		temp = new shape(sConfig,worldB2D,i);
		//objectsList.push_front(temp);
		w->insertarFigura(temp);
	}

	loopPrincipal();
	wClose();

	return OKEXIT;
}

bool loadInitialValues(std::string& sConfig) {
	Logger& log = * Logger::Instancia();
	//abre el json y lo carga a un string
	fstream fConfig;
	fConfig.open("config.json",ios_base::in);
	if(!fConfig.is_open()) {
		if (!log.abrirLog(MAINLOG)){
			log.crearLogs();
			std::cout << "Error al abrir archivo de log "<< MAINLOG << ", creando..."<< std::endl;
			if (!log.abrirLog(MAINLOG)) {
				std::cout << "No se pudo crear el archivo de log.";
				return false;
			}
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
	w = new Window();
	bool statusOK = w->init(widthScreen, heightScreen, "imagenes/fondo2.png");
	statusOK = true; //rrw->insertarPersonaje(100, 100, 60, 50);
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
			if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE ) {
				quit = true;
				break;
			} /*else if(event.key.keysym.sym  == SDLK_r) {
				wClose();
				std::string sConfig;
				loadInitialValues(sConfig);
				int heightScreen=get_node("alto-px","escenario",sConfig,480);
				int widthScreen=get_node("ancho-px","escenario",sConfig,640);
				worldInit(widthScreen,heightScreen);
				windowInit(widthScreen, heightScreen);
/*
				SDL_Color color = { 255, 0 , 0, 255 };
				CirculoDibujable* circulo = new CirculoDibujable();
				circulo->setRadio(10);
				circulo->color(color);
				circulo->posicion(350,240);
				circulo->angulo(20);
				circulo->esEstatico(true);
				w->insertarFigura(circulo);

			} else {
				//w->handleEvent(event);
			}*/
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

void worldInit(float w,float h){
	b2Vec2 gravedad(0, -9.8);
	worldB2D = new b2World(gravedad);
	//crear paredes piso y techo
	return;
}
