#ifndef CIRCULODIBUJABLE_H_
#define CIRCULODIBUJABLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../../utiles/Logger.h"
#include <math.h>
#include "../interfaces/IDibujable.h"
#include "../../Window.h"

class CirculoDibujable: public IDibujable {
private:

	float32 radio;

	int arcoMarca() {

		float32 ratio = ( Window::wRatio < Window::hRatio ? Window::wRatio : Window::hRatio );

		Sint16 radioArco  = (Sint16)(radio*0.4 * ratio);
		Uint8 newRed = 255 - color.r;
		Uint8 newGreen = 255 - color.g;
		Uint8 newBlue = 255 - color.b;
		int32 anguloInit = RADTODEG * this->angulo;
		if(anguloInit > 360) {
			anguloInit -= 360;
		}
		int32 anguloEnd = anguloInit + 70;

		Sint16 posX = posicion.x * Window::wRatio;
		Sint16 posY = posicion.y * Window::hRatio;

		return arcRGBA(dRenderer, posX, posY, radioArco, anguloInit, anguloEnd, newRed, newGreen, newBlue, color.a);
	}

public:
	CirculoDibujable() {
		radio = 1.0;
	}
	virtual ~CirculoDibujable() {}

	virtual void render() {
		// Se redefine distinto, usa el renderer directo
		int status;

		Sint16 posX = posicion.x * Window::wRatio;
		Sint16 posY = posicion.y * Window::hRatio;
		Sint16 radX = radio * Window::wRatio;
		Sint16 radY = radio * Window::hRatio;

		status = filledEllipseRGBA(dRenderer, posX, posY, radX, radY, color.r, color.g, color.b, color.a);
		if(status != 0) {
			Logger& log = * Logger::Instancia();
			if(!log.abrirLog(DIBUJABLELOG)) {
				std::string err(SDL_GetError());
				log.escribirLog("WAR", "No se renderizo el circulo "+err);
				log.cerrarLog();
				return;
			}
		}
		status = arcoMarca();
		if(status != 0) {
			Logger& log = * Logger::Instancia();
			if(!log.abrirLog(DIBUJABLELOG)) {
				std::string err(SDL_GetError());
				log.escribirLog("WAR", "No se renderizar la marca del circulo "+err);
				log.cerrarLog();
				return;
			}
		}

	}

	void setRadio(float32 r) {
		radio = r;
	}

};



#endif
