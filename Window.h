#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

#include "control/Observador.h"
#include "utiles/Logger.h"
#include "vista/Fondo.h"
#include "vista/Camera.h"

class Window {

private:
	SDL_Window * window;
	SDL_Renderer * wRenderer;
	Fondo * background;
	Camera * camera;

	//Escenario* wEscenario;
	//HandlerDeEventos wHandlerEventos;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool error;

	SDL_Surface* resizeSurface(SDL_Surface* surface, int t_height, int t_width);

	bool validarAnchoYAlto(int ancho, int alto);
	bool iniciarSDL();
	SDL_Window* crearVentana();
	SDL_Renderer* crearRenderer(SDL_Window*);
	//rEscenario* crearEscenario(std::string BGpath);

public:

	static float wRatio, hRatio;

	// Constructor de la clase
	Window();
	// Cargar ventana
	bool init(int width, int height, float wRatio, float hRatio, std::string BGpath);
	// Cargar el fondo
	bool loadBackground(const char* pathToBG);
	// Inserta un personaje
	//Personaje * insertarPersonaje(float32 height, float32 width);
	// Inserta una figura
	void insertarFigura(IDibujable* figura);
	// manejar evento
	//void handleEvent(SDL_Event&);
	// Update ventana
	bool updateWindow(b2World * worldB2D);
	void setCamera (Camera * c);
	// Destructor de la clase
	virtual ~Window();
};

#endif
