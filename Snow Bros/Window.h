#ifndef WINDOW_H
#define WINDOW_H
//#include <SDL.h>

#include <SDL2/SDL.h>

class Window2 {

private:
	SDL_Window* window;
	SDL_Surface* wSurface;
	SDL_Surface* BGimage;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool error;

public:
	// Constructor de la clase
	Window2();
	// Cargar ventana
	bool init(int width, int height);
	// Cargar el fondo
	bool loadBackground(const char* pathToBG);
	// Update ventana
	bool updateWindow();
	// Destructor de la clase
	virtual ~Window2();
};

#endif
