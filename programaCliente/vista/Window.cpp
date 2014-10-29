#include "Window.h"
#include <iostream>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>
#include "ItemRenderer.h"

float Window::wRatio, Window::hRatio;


Window::Window() {
	window = NULL;
	//wEscenario = NULL;
	error = false;
	SCREEN_WIDTH = 480;
	SCREEN_HEIGHT = 640;
	wRatio = hRatio = 1;
}

bool Window::init(int width, int height, std::string BGpath){
	if( !validarAnchoYAlto( width, height ) ){
		return !error;
	}
	if (!iniciarSDL()){
		return !error;
	}
	else{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		 window = crearVentana();
		if( !window ){
			 return !error;
		}
		else{
			ctx = initGL(window);

			if( TTF_Init() < 0){
				printf("error al abrir ttf\n");
				return !error;
			}
		}
	}

	return !error;
}

bool Window::updateWindow(std::list<WorldItem*> & itemList, float escala){

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Dibuja uno por uno los elementos en la lista.
	while(!itemList.empty()){
		WorldItem * item = itemList.front();
		itemList.pop_front();
		ItemRenderer::render(item, escala);
		delete item;
		item = NULL;
	}

	SDL_GL_SwapWindow(window);

	return !error;
}


bool Window::validarAnchoYAlto(int width, int height)
{
	Logger& log = * Logger::Instancia();

	if (height > 0 && width > 0){
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	} else {
		log.log(WINDOWLOG,ERROR, "Altura y/o ancho menor a 0");
		error = true;
	}
	return !error;
}

bool Window::iniciarSDL() {
	Logger& log = * Logger::Instancia();

	// Inicio SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::string buff ("No se pudo inicializar SDL! ");
		buff = buff + SDL_GetError();
		log.log(WINDOWLOG,ERROR, buff);
		return false;
	}

	// Inicio la carga de imagenes.
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		std::string buff ("SDL_image no pudo iniciar! SDL_image Error: ");
		buff = buff + IMG_GetError();
		log.log(WINDOWLOG,ERROR, buff);
		return false;
	}

	return true;
}

SDL_Window* Window::crearVentana()
{
	Logger& log = * Logger::Instancia();
	SDL_Window* w = SDL_CreateWindow("Snow Bros", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!w) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log " << WINDOWLOG << std::endl;
			return w;
		}
		std::string buf("No se pudo crear la ventana. ");
		buf = buf + SDL_GetError();
		log.escribirLog(ERROR, buf);
		log.cerrarLog();
		error = true;
	}
	return w;
}


Window::~Window(){

	if (TTF_WasInit()) TTF_Quit();

	if (ctx) {
		SDL_GL_DeleteContext(ctx);
		ctx = NULL;
	}

	if(window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}

	SDL_Quit();
}

SDL_GLContext Window::initGL(SDL_Window* w) {

	SDL_GLContext c = SDL_GL_CreateContext(w);
	SDL_GL_MakeCurrent(w, c);

	SDL_GL_SetSwapInterval(1);

// Set the OpenGL state after creating the context with SDL_SetVideoMode
	glClearColor(0, 0, 0, 1);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
	glMatrixMode( GL_MODELVIEW);

	glLoadIdentity();

	return c;
}
