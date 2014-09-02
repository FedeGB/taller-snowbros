#include "Window.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL2_rotozoom.h"

Window::Window() {
	window = NULL;
	wSurface = NULL;
	error = false;
	SCREEN_WIDTH = 0;
	SCREEN_HEIGHT = 0;
	BGimage = NULL;
}

bool Window::init(int width, int height) {
	if (height > 0 && width > 0){
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	}
	else {
		// TODO: Error hangling, log
		error = true;
		return error;
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "No se pudo inicializar SDL!" << std::endl;
		// TODO: Catch Error and handle log.
		error = true;
	}
	else {
		 window = SDL_CreateWindow("Snow Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(!window) {
			// TODO: Catch Error and handle log.
			std::cout << "No se pudo crear la ventana." << std::endl;
			error = true;
		}
		else {
			wSurface = SDL_GetWindowSurface(window);
		}
	}
	return !error;

}

bool Window::updateWindow() {
	 if (SDL_UpdateWindowSurface(window) != 0 ) {
		 // TODO: Catch Error and handle log.
		 error = true;
	 }

	 // EJEMPLO DE DIBUJADO DE UN RECTANGULO
	 RectanguloDibujable rectangulo;
	 rectangulo.posicion( 30.0, 30.0 );
	 rectangulo.tamano(100, 50);
	 SDL_Color c = { 255, 165, 0, 0 }; // naranjita
	 rectangulo.color( c );

	 wEscenario.dibujar(rectangulo, wSurface);
	 // FIN EJEMPLO

	 return !error;
}

// Loads a Background image.
// If the image is not of the same size as the window it will be resized
// to fit the window size, being proportional and avoiding blank spaces (image could be cropped).
bool Window::loadBackground(const char* pathToBG) {
	BGimage = IMG_Load(pathToBG);
	if (!BGimage) {
		// TODO: Catch Error and handle log.
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
			//TODO: Error Handling
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
		// TODO: Error handling
		return NULL;
	}
	if(t_height <= 0 || t_width <= 0) {
		// TODO: Error handling
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
		std::cout << "No se pudo resizear" << std::endl;
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
	if(window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
	SDL_Quit();
}
