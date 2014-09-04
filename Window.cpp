#include "Window.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL2_rotozoom.h"

Window::Window() {
	window = NULL;
	wSurface = NULL;
	error = false;
	renderer = NULL;
	SCREEN_WIDTH = 0;
	SCREEN_HEIGHT = 0;
	BGimage = NULL;
	log = * Logger::Instancia();
}

bool Window::init(int width, int height) {
	if (height > 0 && width > 0){
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	}
	else {
		if (!log.abrirLog("Window.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}

		log.escribirLog("ERROR", "Altura y/o ancho menor a 0");
		log.cerrarLog();
		error = true;
		return !error;
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		if (!log.abrirLog("Window.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("ERROR", "No se pudo inicializar SDL!");
		log.cerrarLog();
		error = true;
		return !error;
	}
	else {
		 window = SDL_CreateWindow("Snow Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(!window) {
			if (!log.abrirLog("Window.log")) {
				std::cout << "Error al abrir archivo de log" << std::endl;
				return false;
			}
			log.escribirLog("ERROR", "No se pudo crear la ventana.");
			log.cerrarLog();
			error = true;
			return !error;
		}
		else {
			wSurface = SDL_GetWindowSurface(window);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (!renderer) {
				if (!log.abrirLog("Window.log")) {
					std::cout << "Error al abrir archivo de log" << std::endl;
					return false;
				}
				log.escribirLog("ERROR", "No se pudo crear el renderer!");
				log.cerrarLog();
				SDL_DestroyWindow(window);
				error = true;
				return !error;
			}
			/* inicializamos la escena
			CREAMOS EL OBJETO Y LO AGREGAMOS A LA LISTA DE OBJETOS.
			 lista de objetos = escena.
			RectanguloDibujable* rectangulo = new RectanguloDibujable();
			rectangulo->posicion( 30.0, 30.0 );
			rectangulo->tamano(100, 50);
			SDL_Color c = { 255, 165, 0, 0 };
			rectangulo->color( c );

			wEscenario.agregarDibujable(rectangulo);*/
		}
	}
	return !error;

}

bool Window::updateWindow() {
	 if (SDL_UpdateWindowSurface(window) != 0 ) {
		if (!log.abrirLog("Window.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("WAR", "Window update fail!");
		log.cerrarLog();
		error = true;
		return !error;
	 }
	 // El dibujar supongo que deberia ir antes del update surface
	 // Igualmente por ahi es mejor usar un renderer para los objetos dinamicos
	 // Y el surface para los estaticos, asi solo hace un update surface al cargar
	 // o cambiar de escenario (es una idea).
	 // Por deberia haber 2 update uno para renderer y otro para surface.
	 /*SDL_RenderClear(renderer);
	 wEscenario.dibujarEscena(wSurface);
	 SDL_RenderPresent(renderer);*/

	 return !error;
}

// Loads a Background image.
// If the image is not of the same size as the window it will be resized
// to fit the window size, being proportional and avoiding blank spaces (image could be cropped).
bool Window::loadBackground(const char* pathToBG) {
	BGimage = IMG_Load(pathToBG);
	if (!BGimage) {
		if (!log.abrirLog("Window.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("WAR", "No se pudo cargar el fondo!");
		log.cerrarLog();
		error = true;
		return error;
	}
	int bg_height, bg_width;
	bg_height = BGimage->h;
	bg_width = BGimage->w;
	// Adjusting BG to window size if necessary
	if(bg_height != SCREEN_HEIGHT && bg_width != SCREEN_WIDTH) {
		double ratio;
		int aux;
		if(bg_height < bg_width) {
			ratio = (double)SCREEN_HEIGHT/bg_height;
			aux = (int)(ratio*bg_width);
			BGimage = resizeSurface(BGimage, SCREEN_HEIGHT, aux);
		}
		else {
			ratio = (double)SCREEN_WIDTH/bg_width;
			aux = (int)(ratio*bg_height);
			BGimage = resizeSurface(BGimage, aux, SCREEN_WIDTH);
		}
		if(!BGimage) {
			if (!log.abrirLog("Window.log")) {
				std::cout << "Error al abrir archivo de log" << std::endl;
				return false;
			}
			log.escribirLog("WAR", "No se pudo resizear la imagen correctamente.");
			log.cerrarLog();
			return false;
		}
	}

	SDL_BlitSurface(BGimage, NULL, wSurface, NULL);
	return !error;
}

// Resize an input surface to a target height and width.
// Does not check if the resize distorts the surface size
// Returns the new Surface and frees the old one
SDL_Surface* Window::resizeSurface(SDL_Surface* surface, int t_height, int t_width) {
	if(!surface) {
		if (!log.abrirLog("Window.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("ERROR", "Parametro de superficie invalido.");
		log.cerrarLog();
		return NULL;
	}
	if(t_height <= 0 || t_width <= 0) {
		if (!log.abrirLog("Window.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
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
		if (!log.abrirLog("Window.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("WAR", "No se pudo resizear la superficie.");
		log.cerrarLog();
		return NULL;
	}
	SDL_FreeSurface(surface);
	return newSurface;
}

Window::~Window(){
	if(BGimage) {
		SDL_FreeSurface(BGimage);
		BGimage = NULL;
	}
	if(renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if(window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
	SDL_Quit();
}
