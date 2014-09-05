#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>

//#include <SDL2/SDL.h>

#include "control/HandlerDeEventos.h"
#include "vista/Escenario.h"
#include "control/Observador.h"
#include "modelo/Personaje.h"
#include "modelo/formas/RectanguloDibujable.h"
#include "utiles/Logger.h"

class Window {

private:
	SDL_Window* window;
	SDL_Surface* wSurface;
	SDL_Surface* BGimage;
	SDL_Renderer* renderer;

	Escenario* wEscenario;
	HandlerDeEventos wHandlerEventos;

	Logger& log;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool error;

	SDL_Surface* resizeSurface(SDL_Surface* surface, int t_height, int t_width);

public:
	// Constructor de la clase
	Window();
	// Cargar ventana
	bool init(int width, int height);
	// Cargar el fondo
	bool loadBackground(const char* pathToBG);
	// manejar evento
	void handleEvent(SDL_Event&);
	// Update ventana
	bool updateWindow();
	// Destructor de la clase
	virtual ~Window();
};

#endif
