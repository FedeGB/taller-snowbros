/*
 * Rectangulo.h
 *
 *  Created on: 2/9/2014
 *      Author: manuel
 */

#ifndef RECTANGULO_H_
#define RECTANGULO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../interfaces/IDibujable.h"
//#include "../../control/interfaces/INotificable.h"
#include "../../vista/Camera.h"

#include "../Textura.h"

class RectanguloDibujable: public IDibujable {

protected:
	float32 halfHeight, halfWidth;

	Textura* _tex;

public:

	RectanguloDibujable() : _tex(NULL){	halfHeight = 0; halfWidth = 0;}
	~RectanguloDibujable() { }

	virtual void render() {

		// Se redefine distinto, usa el renderer directo
		int status;

		GLfloat vx[4]; GLfloat vy[4];
		// Calcula las coordenadas en X e Y segun la posicion, el tamaño, y la rotacion del rectangulo.
		calcularVertices(vx, vy, 4, 1.0f, 1.0f, angulo, Camera::WORLDTOWINDOWSCALE);

		if( _tex != NULL)
			_tex->dibujar(vx, vy, 4);
		else{
			Sint16 i_vx[4]; Sint16 i_vy[4];
			// convierto los vertices de float a short para que la funcion "filledPolygonRGBA" los tome
			for( int i = 0; i < 4; i++ ) {
				i_vx[i] = (short) vx[i]; i_vy[i] = (short) vy[i];
			}
			status = filledPolygonRGBA(dRenderer, i_vx, i_vy, 4, color.r, color.g, color.b, color.a);
		}

		if(status != 0) {
			Logger& log = * Logger::Instancia();
			if(!log.abrirLog(DIBUJABLELOG)) {
				std::string err(SDL_GetError());
				log.escribirLog(WARNING, "No se renderizo el poligono "+err);
				log.cerrarLog();
				return;
			}
		}
	}

	bool setDimensiones(float32 height, float32 width){
		halfHeight = height / 2;
		halfWidth = width / 2;
		return true;
	}

	float32 getHeight(){
		return halfHeight * 2;
	}

	float32 getWidth(){
		return halfWidth * 2;
	}

	void calcularVertices(float* vx, float* vy, int nVertices, float escX, float escY, float ang, float worldtowindowscale) {
		float modulo = sqrt( pow(halfWidth, 2) + pow(halfHeight, 2) );
		float thita = ang + atan( halfHeight / halfWidth );
		float xaux = modulo * cos(thita);
		float yaux = modulo * sin(thita);
		float thita2 = - ang + atan( halfHeight / halfWidth );
		float xaux2 = modulo * cos(thita2);
		float yaux2 = modulo * sin(thita2);

//		Sint16 * vx = new Sint16[4];
		vx[0] = (posicion.x - xaux) * worldtowindowscale;
		vx[1] = (posicion.x + xaux2) * worldtowindowscale;
		vx[2] = (posicion.x + xaux) * worldtowindowscale;
		vx[3] = (posicion.x - xaux2) * worldtowindowscale;

//		Sint16 * vy = new Sint16[4];
		vy[0] = (posicion.y - yaux) * worldtowindowscale;
		vy[1] = (posicion.y - yaux2) * worldtowindowscale;
		vy[2] = (posicion.y + yaux) * worldtowindowscale;
		vy[3] = (posicion.y + yaux2) * worldtowindowscale;
	}

	GLuint getCantidadDeVertices() { return 4; }

	void setTex(Textura* t){
		_tex = t;
		_tex->mapearCoordenadas(this);
	}
};

#endif /* RECTANGULO_H_ */
