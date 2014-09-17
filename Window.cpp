#include "Window.h"
#include <iostream>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>

//#include "utiles/Configurador.h"

float Window::wRatio, Window::hRatio = 1;


Window::Window() {
	window = NULL;
	wEscenario = NULL;
	error = false;
	wRenderer = NULL;
	SCREEN_WIDTH = 480;
	SCREEN_HEIGHT = 640;
	wRatio = hRatio = 1;
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

			wEscenario = crearEscenario(BGpath);
		}
	}

	this->wRatio = wRatio;
	this->hRatio = hRatio;

	return !error;
}

void Window::handleEvent(SDL_Event& evento)
{
	 switch( evento.type )
	 {
	 	 case SDL_KEYDOWN: wHandlerEventos.manejarTeclaPresionada(evento.key.keysym.sym); break;
	 }
}

bool Window::updateWindow() {
	 wEscenario->dibujarEscena(wRenderer);

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

		log.escribirLog("ERROR", "Altura y/o ancho menor a 0");
		log.cerrarLog();
		error = true;
		return !error;
	}
	return !error;
}

bool Window::iniciarSDL()
{
	Logger& log = * Logger::Instancia();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		std::string buf ("No se pudo inicializar SDL!");
		buf = buf + SDL_GetError();
		log.escribirLog("ERROR", buf);
		log.cerrarLog();
		error = true;
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
		log.escribirLog("ERROR", buf);
		log.cerrarLog();
		error = true;
	}
	return w;
}

SDL_Renderer* Window::crearRenderer(SDL_Window* w)
{
	Logger& log = * Logger::Instancia();
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer( w, -1, SDL_RENDERER_ACCELERATED );
	if( !renderer )
	{
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return renderer;
		}
		log.escribirLog("ERROR", "No se pudo crear el renderer!");
		log.cerrarLog();
		SDL_DestroyWindow(window);
		return renderer;
	}
	else
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return renderer;
}

Escenario* Window::crearEscenario(std::string BGpath) {
	 Logger& log = * Logger::Instancia();
	 Escenario* escena = new Escenario();
	 if(!escena) {
		 if (!log.abrirLog(WINDOWLOG)) {
		 	std::cout << "Error al abrir archivo de log" << std::endl;
		 	return NULL;
		 }
		  log.escribirLog("ERROR", "No se pudo asignar memoria para el escenario");
		  log.cerrarLog();
		  return NULL;
	 }

	 Fondo* fondo = new Fondo(SCREEN_WIDTH, SCREEN_HEIGHT);
	 if(!fondo) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog("ERROR", "No se pudo asignar memoria para el fondo");
		log.cerrarLog();
		return NULL;
	 }
	 fondo->setRenderer(wRenderer);
	 fondo->cargarImagen(BGpath);
	 escena->agregarDibujable(fondo);
	 Observador<Escenario>* observadorEscenario = new Observador<Escenario>( escena );
	 if(!observadorEscenario) {
	 	if (!log.abrirLog(WINDOWLOG)) {
	 		std::cout << "Error al abrir archivo de log" << std::endl;
	 		return NULL;
	 	}
	 	log.escribirLog("ERROR", "No se pudo asignar memoria para el observador del Escenario");
	 	log.cerrarLog();
	 	return NULL;
	 }
	 wHandlerEventos.agregarObservador(observadorEscenario);
	 return escena;
}

bool Window::insertarPersonaje(float32 posX, float32 posY, uint32 height, uint32 width) {
	Logger& log = * Logger::Instancia();
	Personaje* personaje = new Personaje();
	if(!personaje) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("ERROR", "No se pudo asignar memoria para al personaje");
		log.cerrarLog();
		return false;
	}
	personaje->setRenderer(wRenderer);
	personaje->cargarImagen("imagenes/parado.png");
	personaje->setPosicion(posX, posY);
	personaje->tamano(height, width);
	wEscenario->agregarDibujable(personaje);
	Observador<Personaje>* observadorPersonaje = new Observador<Personaje>( personaje );
	if(!observadorPersonaje) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("ERROR", "No se pudo asignar memoria para el observador de personaje");
		log.cerrarLog();
		return false;
	}
	wHandlerEventos.agregarObservador(observadorPersonaje);
	return true;
}

void Window::insertarFigura(IDibujable* figura){
	figura->setRenderer(wRenderer);
	wEscenario->agregarDibujable(figura);
}

Window::~Window(){
	if(wEscenario) {
		delete(wEscenario);
		wEscenario = NULL;
	}
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

// Resize an input surface to a target height and width.
// Does not check if the resize distorts the surface size
// Returns the new Surface and frees the old one
/*SDL_Surface* Window::resizeSurface(SDL_Surface* surface, int t_height, int t_width) {
	Logger& log = * Logger::Instancia();
	if(!surface) {
		if (!log.abrirLog(WINDOWLOG)) {
			log.escribirLog("ERROR", "Parametro de superficie invalido.");
			log.cerrarLog();
			return NULL;
		}
	}
	if(t_height <= 0 || t_width <= 0) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog("ERROR", "Los tamaños para resize son <= 0");
		return NULL;
	}
	SDL_Surface* newSurface = NULL;
	int src_height = surface->h;
	int src_width = surface->w;
	double zoomx, zoomy;
	zoomx = (double)t_width / src_width;
	zoomy = (double)t_height / src_height;

	newSurface = rotozoomSurfaceXY(surface, 0, zoomx, zoomy, SMOOTHING_ON);
	if(!newSurface) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		std::string buf ("No se pudo resizear la superficie. ");
		buf = buf + SDL_GetError();
		log.escribirLog("WAR", buf);
		log.cerrarLog();
		return NULL;
	}
	SDL_FreeSurface(surface);
	return newSurface;
}


// Loads a Background image.
// If the image is not of the same size as the window it will be resized
// to fit the window size, being proportional and avoiding blank spaces (image could be cropped).
bool Window::loadBackground(const char* pathToBG) {
	Logger& log = * Logger::Instancia();
	SDL_Surface* imagenCargada = IMG_Load(pathToBG);
	if (!imagenCargada) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		std::string buf("No se pudo cargar el fondo!");
		buf = buf + SDL_GetError();
		log.escribirLog("WAR", buf);
		log.cerrarLog();
		error = true;
		return error;
	}
	int bg_height, bg_width;
	bg_height = imagenCargada->h;
	bg_width = imagenCargada->w;
	// Adjusting BG to window size if necessary
	if(bg_height != SCREEN_HEIGHT || bg_width != SCREEN_WIDTH) {
		double ratio;
		int aux;
		if(bg_height < bg_width) {
			ratio = (double)SCREEN_HEIGHT/bg_height;
			aux = (int)(ratio*bg_width);
			imagenCargada = resizeSurface(imagenCargada, SCREEN_HEIGHT, aux);
		}
		else {
			ratio = (double)SCREEN_WIDTH/bg_width;
			aux = (int)(ratio*bg_height);
			imagenCargada = resizeSurface(imagenCargada, aux, SCREEN_WIDTH);
		}
		if(!imagenCargada) {
			if (!log.abrirLog("Window.log")) {
				std::cout << "Error al abrir archivo de log" << std::endl;
				return false;
			}
			std::string buf("No se pudo resizear la imagen correctamente.");
			buf = buf + SDL_GetError();
			log.escribirLog("WAR", buf);
			log.cerrarLog();
			return false;
		}
	}

	//SDL_BlitSurface(BGimage, NULL, wSurface, NULL);
	BGimage = SDL_CreateTextureFromSurface( wRenderer, imagenCargada );
	SDL_FreeSurface(imagenCargada);

	return !error;
}*/
