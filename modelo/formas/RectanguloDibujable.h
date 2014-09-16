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
#include "../ObjetoDibujable.h"
#include "../../control/interfaces/INotificable.h"

class RectanguloDibujable: public ObjetoDibujable {

private:
	Sint16 *vx, *vy;

public:

	RectanguloDibujable() {	vx = vy = NULL;}
	~RectanguloDibujable() {
		if(vx)
			delete[] vx;
		if(vy)
			delete[] vy;
	}

	SDL_Rect getRecuadroDeDibujo()
	{
		return getSDL_Rect();
	}

	virtual void render() {
		// Se redefine distinto, usa el renderer directo
		int status;
		status = boxRGBA(dRenderer, vx[0], vy[0], vx[1], vy[1], oColor.r, oColor.g, oColor.b, oColor.a);
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

	bool setVertices(Sint16* vx, Sint16* vy, int nvert) {
		if (vx != NULL) {
			this->vx = vx;
		} else {
			return false;
		}
		if (vy != NULL) {
			this->vy = vy;
		} else {
			return false;
		}
		return true;
	}
};

#endif /* RECTANGULO_H_ */
