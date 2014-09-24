#include "Window.h"
#include <iostream>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>

float Window::wRatio, Window::hRatio;


Window::Window() {
	window = NULL;
	//wEscenario = NULL;
	error = false;
	wRenderer = NULL;
	SCREEN_WIDTH = 480;
	SCREEN_HEIGHT = 640;
	wRatio = hRatio = 1;
	background = NULL;
}

bool Window::init(int width, int height, float wRatio, float hRatio, std::string BGpath)
{
	if( !validarAnchoYAlto( width, height ) ) {
		return !error;
	}
	if (!iniciarSDL())
	{
		return !error;
	}
	else
	{
		 window = crearVentana();
		if( !window )
		{
			 return !error;
		}
		else
		{
			wRenderer = crearRenderer(window);
			if( !wRenderer ) {
				error = true;
				return !error;
			}

			background = new Fondo(width, height);
			background->setRenderer(wRenderer);
			background->cargarImagen(BGpath);
		}
	}

	this->wRatio = wRatio;
	this->hRatio = hRatio;

	return !error;
}

bool Window::updateWindow(b2World * worldB2D) {

	SDL_SetRenderDrawColor(wRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(wRenderer);

	b2Body * objeto = worldB2D->GetBodyList();
	int numObjetos = worldB2D->GetBodyCount();

	background->render();

	for( int i = 0; i < numObjetos; i++) {
		((IDibujable*)objeto->GetUserData())->setAngulo(objeto->GetAngle());
		((IDibujable*)objeto->GetUserData())->setPosicion(objeto->GetPosition());;
		((IDibujable*)objeto->GetUserData())->render();
		objeto = objeto->GetNext();
	}

	SDL_RenderPresent(wRenderer);

	return !error;
}

bool Window::validarAnchoYAlto(int width, int height)
{
	Logger& log = * Logger::Instancia();

	if (height > 0 && width > 0)
	{
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	}
	else
	{
		if (!log.abrirLog(WINDOWLOG))
		{
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}

		log.escribirLog(ERROR, "Altura y/o ancho menor a 0");
		log.cerrarLog();
		error = true;
		return !error;
	}
	return !error;
}

bool Window::iniciarSDL()
{
	Logger& log = * Logger::Instancia();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		std::string buf ("No se pudo inicializar SDL!");
		buf = buf + SDL_GetError();
		log.escribirLog(ERROR, buf);
		log.cerrarLog();
		error = true;
	}else{
		//Inicio la carga de imagenes
		int imgFlags = IMG_INIT_PNG;
		if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
			printf( "SDL_image no pudo iniciar! SDL_image Error: %s" , IMG_GetError() , "\n" );
			error = true;
		}
	}
	return !error;
}

SDL_Window* Window::crearVentana()
{
	Logger& log = * Logger::Instancia();
	SDL_Window* w = SDL_CreateWindow("Snow Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(!w) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return w;
		}
		std::string buf("No se pudo crear la ventana.");
		buf = buf + SDL_GetError();
		log.escribirLog(ERROR, buf);
		log.cerrarLog();
		error = true;
	}
	return w;
}

SDL_Renderer* Window::crearRenderer(SDL_Window* w)
{
	Logger& log = * Logger::Instancia();
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer( w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( !renderer )
	{
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return renderer;
		}
		log.escribirLog(ERROR, "No se pudo crear el renderer!");
		log.cerrarLog();
		SDL_DestroyWindow(window);
		return renderer;
	}
	else SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	return renderer;
}

void Window::insertarFigura(IDibujable* figura){
	figura->setRenderer(wRenderer);
}

Window::~Window(){

	if(wRenderer) {
		SDL_DestroyRenderer(wRenderer);
		wRenderer = NULL;
	}
	if(window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
	SDL_Quit();
}
