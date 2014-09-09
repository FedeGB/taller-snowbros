#ifndef WINDOW_H
#define WINDOW_H
//#include <SDL.h>

#include <SDL2/SDL.h>

#include "control/HandlerDeEventos.h"
#include "vista/Escenario.h"
#include "control/Observador.h"
#include "modelo/Personaje.h"
#include "modelo/formas/RectanguloDibujable.h"
#include "vista/Fondo.h"
#include "utiles/Logger.h"

class Window {

private:
	SDL_Window* window;
	SDL_Surface* wSurface;
	//SDL_Surface* BGimage;
	SDL_Texture* BGimage;
	SDL_Renderer* wRenderer;

	Escenario* wEscenario;
	HandlerDeEventos wHandlerEventos;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool error;

	SDL_Surface* resizeSurface(SDL_Surface* surface, int t_height, int t_width);

	bool validarAnchoYAlto(int ancho, int alto);
	bool iniciarSDL();
	SDL_Window* crearVentana();
	SDL_Renderer* crearRenderer(SDL_Window*);

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
