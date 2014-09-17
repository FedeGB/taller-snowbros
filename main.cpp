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

bool init();
bool loadInitialValues(std::string& sConfig);
bool windowInit(int widthScreen, int heightScreen, float wRatio, float hRatio);
void worldInit(float w,float h);
bool loopPrincipal();
void wClose();

Window* w;
b2World *worldB2D;


int main() {

	init();
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

bool windowInit(int widthScreen, int heightScreen, float wRatio, float hRatio, std::string path_fondo) {
	w = new Window();
	bool statusOK = w->init(widthScreen, heightScreen, wRatio, hRatio, path_fondo);
	w->insertarPersonaje(100, 100, 32, 32);
	statusOK = true;
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
			} else if(event.key.keysym.sym  == SDLK_r) {
				wClose();
				init();
				break;
			} else {
				w->handleEvent(event);
			}
		}

		worldB2D->Step(1.0f/60.0f, 8, 3);
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
	b2Vec2 gravedad(0, 10);
	worldB2D = new b2World(gravedad, true);
	//crear paredes piso y techo

	return;
}

bool init(){

	std::string sConfig;
	bool statusOK = true;
	statusOK = loadInitialValues(sConfig);
	if(!statusOK) {
		return LOADERROR;
	}
	int heightScreen=get_node("alto-px","escenario",sConfig,480);
	int widthScreen=get_node("ancho-px","escenario",sConfig,640);

	float heightWorld=get_node("alto-un","escenario",sConfig,10.0f);
	float widthWorld=get_node("ancho-un","escenario",sConfig,10.0f);

	std::string path_fondo = get_node("imagen-fondo","escenario",sConfig,"imagenes/fondo2.png");

	float heightRatio=heightScreen/heightWorld;
	float widthRatio=widthScreen/widthWorld;

	worldInit(widthWorld,heightWorld);

	statusOK = windowInit(widthScreen, heightScreen, widthRatio, heightRatio, path_fondo);
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

	return true;
}
