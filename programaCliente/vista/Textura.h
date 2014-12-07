/*
 * Textura.h
 *
 *  Created on: 5/10/2014
 *      Author: manuel
 */

#ifndef TEXTURA_H_
#define TEXTURA_H_

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../utiles/tipos.h"
#include "../utiles/Logger.h"

//#include "../vista/Camera.h"

class Textura {
private:
	GLuint id_tex;

public:

	Textura();
	virtual ~Textura();

	void eliminar();

	bool generar(std::string path);

	bool generarTexto(std::string path, int tamanio, std::string txt, SDL_Color color);

	void dibujar(GLfloat* vx, GLfloat* vy, float* s, float* t, int n);
	void dibujar(GLfloat* vx, GLfloat* vy, float* s, float* t, int n, float z);
	void dibujarOscuro(GLfloat* vx, GLfloat* vy, float* s, float* t, int n);

};

#endif /* TEXTURA_H_ */
