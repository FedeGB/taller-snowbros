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
#include "../../Window.h"

class RectanguloDibujable: public IDibujable {

protected:
	float32 halfHeight, halfWidth;

public:

	RectanguloDibujable() {	halfHeight = 0; halfWidth = 0;}
	~RectanguloDibujable() { }

	virtual void render() {

		// Se redefine distinto, usa el renderer directo
		int status;

		// Calcula las coordenadas en X e Y segun la posicion, el tamaño, y la rotacion del rectangulo.
		float modulo = sqrt( pow(halfWidth, 2) + pow(halfHeight, 2) );
		float thita = angulo + atan( halfHeight / halfWidth );
		float xaux = modulo * cos(thita);
		float yaux = modulo * sin(thita);
		float thita2 = - angulo + atan( halfHeight / halfWidth );
		float xaux2 = modulo * cos(thita2);
		float yaux2 = modulo * sin(thita2);

		Sint16 * vx = new Sint16[4];
		vx[0] = (posicion.x - xaux) * Window::wRatio;
		vx[1] = (posicion.x + xaux2) * Window::wRatio;
		vx[2] = (posicion.x + xaux) * Window::wRatio;
		vx[3] = (posicion.x - xaux2) * Window::wRatio;

		Sint16 * vy = new Sint16[4];
		vy[0] = (posicion.y - yaux) * Window::hRatio;
		vy[1] = (posicion.y - yaux2) * Window::hRatio;
		vy[2] = (posicion.y + yaux) * Window::hRatio;
		vy[3] = (posicion.y + yaux2) * Window::hRatio;

		status = filledPolygonRGBA(dRenderer, vx, vy, 4, color.r, color.g, color.b, color.a);
		delete[] vx ; delete[] vy ;

		if(status != 0) {
			Logger& log = * Logger::Instancia();
			if(!log.abrirLog(DIBUJABLELOG)) {
				std::string err(SDL_GetError());
				log.escribirLog("WAR", "No se renderizo el poligono "+err);
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

};

#endif /* RECTANGULO_H_ */
