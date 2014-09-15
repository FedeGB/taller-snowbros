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
void worldInit(float w,float h);
bool loopPrincipal();
void close();

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

	float heightWorld=get_node("alto-un","escenario",sConfig,10.0f);
	float widthWorld=get_node("ancho-un","escenario",sConfig,10.0f);

	float heightRelation=heightScreen/heightWorld;
	float widthRelation=widthScreen/widthWorld;

	worldInit(widthWorld,heightWorld);
	list<shapes> _shapes;
	int formas =get_size("objetos",sConfig);
	for(int i=0;i<formas;i++){
		shapes temp(sConfig,worldB2D,i);
	}

	statusOK = windowInit(widthScreen, heightScreen);
	if(!statusOK) {
		return -1;
	}

	PoligonoDibujable* poligono = new PoligonoDibujable();
	int numero_de_vertices = 4;
	Sint16* vx = new Sint16[numero_de_vertices]; vx[0] = 100; vx[1] = 80; vx[2] = 60; vx[3] = 40;
	Sint16* vy = new Sint16[numero_de_vertices]; vy[0] = 80; vy[1] = 120; vy[2] = 120; vy[3] = 80;
	poligono->setVertices(vx, vy, numero_de_vertices);
	SDL_Color color = { 255, 0 , 0, 255 };
	poligono->color(color);
	w->insertarFigura(poligono);

	CirculoDibujable* circulo = new CirculoDibujable();
	circulo->setRadio(10);
	circulo->color(color);
	circulo->posicion(350,240);
	circulo->angulo(20);
	w->insertarFigura(circulo);

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
	w = new Window();
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
			if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE ) {
				quit = true;
				break;
			} else if(event.key.keysym.sym  == SDLK_r) {
				close();
				std::string sConfig;
				loadInitialValues(sConfig);
				int heightScreen=get_node("alto-px","escenario",sConfig,480);
				int widthScreen=get_node("ancho-px","escenario",sConfig,640);
				w = new Window();
				windowInit(widthScreen, heightScreen);
			} else {
				w->handleEvent(event);
			}
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

void worldInit(float w,float h){
	b2Vec2 gravedad(0, -9.8);
	worldB2D = new b2World(gravedad);
	//crear paredes piso y techo
	return;
}
