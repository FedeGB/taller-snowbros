#ifndef CIRCULODIBUJABLE_H_
#define CIRCULODIBUJABLE_H_

#include <SDL2/SDL.h>
//#include <SDL2/SDL2_gfxPrimitives.h>
#include "../../utiles/Logger.h"
#include <math.h>
#include "../interfaces/IDibujable.h"
#include "../../vista/Camera.h"

#include "../Textura.h"

class CirculoDibujable: public IDibujable {
private:

	float32 radio;

	Textura* _tex;
	GLuint nVertices; // nivel de detalle del circulo

	int arcoMarca() {

//		float32 ratio = ( Camera::WORLDTOWINDOWSCALE < Camera::WORLDTOWINDOWSCALE ? Camera::WORLDTOWINDOWSCALE : Camera::WORLDTOWINDOWSCALE );
//
//		Sint16 radioArco  = (Sint16)(radio*0.4 * ratio);
//		Uint8 newRed = 255 - color.r;
//		Uint8 newGreen = 255 - color.g;
//		Uint8 newBlue = 255 - color.b;
//		int32 anguloInit = RADTODEG * this->angulo;
//		if(anguloInit > 360) {
//			anguloInit -= 360;
//		}
//		int32 anguloEnd = anguloInit + 70;
//
//		Sint16 posX = posicion.x * Camera::WORLDTOWINDOWSCALE;
//		Sint16 posY = posicion.y * Camera::WORLDTOWINDOWSCALE;
//
//		return arcRGBA(dRenderer, posX, posY, radioArco, anguloInit, anguloEnd, newRed, newGreen, newBlue, color.a);
	}

public:
	CirculoDibujable() : _tex(NULL), nVertices(20) {
		radio = 1.0;
	}
	virtual ~CirculoDibujable() {}

	virtual void render() {
		// Se redefine distinto, usa el renderer directo
		GLfloat vx[nVertices]; GLfloat vy[nVertices];

		calcularVertices(vx, vy, nVertices, radio, radio, angulo, Camera::WORLDTOWINDOWSCALE);

		if( _tex != NULL ){
			_tex->dibujar(vx, vy, s, t, nVertices);
		}
		else {
			dibujarV(vx, vy, nVertices, color.r, color.g, color.b, color.a);

			GLfloat vx_linea[2]; GLfloat vy_linea[2];

			vx_linea[0] = vx[0]; vy_linea[0] = vy[0];
			vx_linea[1] = vx[nVertices/2]; vy_linea[1] = vy[nVertices/2];

			dibujarLineas(vx_linea, vy_linea, 2, color.g, color.b, color.r, color.a);
		}
	}

	void setRadio(float32 r) {
		radio = r;
	}

	GLuint getCantidadDeVertices() { return nVertices; }

	void setTex(Textura* t, float escalaX, float escalaY){
		_tex = t;
		_tex->mapearCoordenadas(this, escalaX, escalaY);
	}

	void calcularVertices(float* vx, float* vy, int nVertices, float escX, float escY, float ang, float worldtowindowscale) {
		for (int i = 0; i < nVertices; i++) {
			float thita = (2 * i * PI / nVertices) - (ang);
			vx[i] = ( posicion.x + escX * cos(thita) ) * worldtowindowscale;
			vy[i] = ( posicion.y - escY * sin(thita) ) * worldtowindowscale;
		}
	}
};



#endif
