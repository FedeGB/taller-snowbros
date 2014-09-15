#ifndef CIRCULODIBUJABLE_H_
#define CIRCULODIBUJABLE_H_

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "../../utiles/Logger.h"
#include <math.h>

class CirculoDibujable: public Objeto, public IDibujable {
private:
	Sint16 rad; // radio
	int arcoMarca() {
		Sint16 radioArco  = (Sint16)(rad*0.75);
		Uint8 newRed = 255 - oColor.r;
		Uint8 newGreen = 255 - oColor.g;
		Uint8 newBlue = 255 - oColor.b;
		int32 anguloInit = this->angulo();
		if(anguloInit > 360) {
			anguloInit -= 360;
		}
		int32 anguloEnd = anguloInit + 50;
		return arcRGBA(dRenderer, oPosicion.x, oPosicion.y, radioArco, anguloInit, anguloEnd, newRed, newGreen, newBlue, oColor.a);
	}

public:
	CirculoDibujable() {
		rad = 0;
	}
	~CirculoDibujable() {}

	virtual void render() {
		// Se redefine distinto, usa el renderer directo
		int status;
		status = filledCircleRGBA(dRenderer, oPosicion.x, oPosicion.y, rad, oColor.r, oColor.g, oColor.b, oColor.a);
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

	void setRadio(Sint16 radio) {
		rad = radio;
	}

};



#endif
