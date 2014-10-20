/*
 * Textura.h
 *
 *  Created on: 5/10/2014
 *      Author: manuel
 */

#ifndef TEXTURA_H_
#define TEXTURA_H_

#include <SDL2/SDL_opengl.h>
#include "../utiles/tipos.h"

#include "interfaces/IDibujable.h"
#include "../vista/Camera.h"

class Textura {
private:
	GLuint _tex;

public:

	Textura() : _tex(0) {}
	virtual ~Textura() {
		glDeleteTextures(1, &_tex);
	}

	bool generar(std::string path) {

		bool exito = true;
		SDL_Surface *surface = NULL; // this surface will tell us the details of the image
		surface = IMG_Load(path.c_str());

		if (surface == NULL){
			Logger& log = * Logger::Instancia();
			if(log.abrirLog(TEXTURALOG)) {
				std::string err(SDL_GetError());
				log.escribirLog(WARNING, "No se pudo crear la textura '"+ path+"' : "+err+". Se rellena la figura con color.");
				log.cerrarLog();
			}else
				std::cout << "NO SE PUDO ABRIR EL LOG " << TEXTURALOG << "." << std::endl;
			return !exito;
		}

		GLenum texture_format;
		GLint nofcolors = surface->format->BytesPerPixel;
		// seteo los parametros para la funcion glTexImage2D
		if (nofcolors == 4) {
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else if (nofcolors == 3) //no alpha channel
				{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		} else {
			Logger& log = * Logger::Instancia();
			if(log.abrirLog(TEXTURALOG)) {
				std::string err(SDL_GetError());
				log.escribirLog(WARNING, "La imagen '"+ path+"' no es RGB. No se puede generar la textura. Se rellena la figura con color.");
				log.cerrarLog();
			}else
				std::cout << "NO SE PUDO ABRIR EL LOG " << TEXTURALOG << "." << std::endl;
			return !exito;
		}

		// Have OpenGL generate a texture object handle for us
		glGenTextures(1, &_tex);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, _tex);

		glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->w);

		// Set the texture's stretching properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		glTexImage2D(GL_TEXTURE_2D, 0, nofcolors, surface->w, surface->h, 0,
				texture_format, GL_UNSIGNED_BYTE, surface->pixels);

		glBindTexture( GL_TEXTURE_2D, 0);

		// Free the SDL_Surface only if it was successfully created
		if (surface) {
			SDL_FreeSurface(surface);
		}

		return exito;
	}

	void dibujar(GLfloat* vx, GLfloat* vy, float* s, float* t, int n) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_BLEND );

		// Bind the texture to which subsequent calls refer to
		glBindTexture( GL_TEXTURE_2D, _tex);

		glBegin( GL_POLYGON);

		for( int i = 0; i < n; i++ ){
			glTexCoord2f(s[i], t[i]);
			glVertex3f(vx[i], vy[i], 0);
		}

		glEnd();
		glFlush();

		glDisable( GL_BLEND );
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}

	void mapearCoordenadas(IDibujable* figura, float escalaX, float escalaY){

		GLint nVertices = figura->getCantidadDeVertices();
		GLfloat vx[nVertices]; GLfloat vy[nVertices];

		float* s = new float[nVertices];
		float* t = new float[nVertices];

		GLint i;
		// genero unos vertices cualquiera para calcular las coordenadas
		figura->calcularVertices(vx, vy, nVertices, escalaX, escalaY, 0.0f, 1.0f);

		GLfloat menorX = vx[0]; GLfloat menorY = vy[0]; GLfloat mayorX = vx[0]; GLfloat mayorY = vy[0];

		// calculo los menores y mayores de X e Y para calcular el ancho y largo de la textura
		for( i = 1; i<nVertices ; i++){
			if( vx[i] < menorX ) menorX = vx[i];
			if( vy[i] < menorY ) menorY = vy[i];
			if( vx[i] > mayorX ) mayorX = vx[i];
			if( vy[i] > mayorY ) mayorY = vy[i];
		}

		GLfloat ancho = mayorX - menorX;
		GLfloat largo = mayorY - menorY;

		// calculo las coordenadas
		for( i = 0; i < nVertices; i++ ){
			s[i] =  (vx[i] - menorX)* escalaX / ancho;
			t[i] =  (vy[i] - menorY)* escalaY / largo;
		}
		figura->setCoord_s(s);
		figura->setCoord_t(t);

	}
};

#endif /* TEXTURA_H_ */
