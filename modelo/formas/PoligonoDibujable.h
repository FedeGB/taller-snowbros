#ifndef POLIGONODIBUJABLE_H
#define POLIGONODIBUJABLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../../utiles/Logger.h"
#include "../ObjetoDibujable.h"

class PoligonoDibujable: public ObjetoDibujable {

private:
	Sint16 *vx, *vy;
	int ver; // Cantidad de vertices
public:
	PoligonoDibujable() {
		ver = 0;
		vx = vy = NULL;
	}
	~PoligonoDibujable() {
		if(vx)
			delete[] vx;
		if(vy)
			delete[] vy;
	}

	virtual void render() {
		// Se redefine distinto, usa el renderer directo
		int status;
		status = filledPolygonRGBA(dRenderer, vx, vy, ver, oColor.r, oColor.g, oColor.b, oColor.a);
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
		if (nvert >= 3) {
			this->ver = nvert;
		} else {
			return false;
		}
		return true;
	}
};

#endif
