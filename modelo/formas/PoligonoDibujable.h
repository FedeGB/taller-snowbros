#ifndef POLIGONODIBUJABLE_H
#define POLIGONODIBUJABLE_H

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "utiles/Logger.h"

class PoligonoDibujable: public Objeto, public IDibujable, public INotificable {

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
			Logger& log = Logger::Instancia();
			if(!log.abrirLog(DIBUJABLELOG)) {
				log.escribirLog("WAR", "No se renderizo el poligono " + SDL_GetError());
				log.cerrarLog();
				return;
			}
		}
	}

	bool setVertices(Sint16* vx, Sint16 vy, int nvert) {
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


	virtual void eventoArriba(){
		moverY(-10.0);
	}

	virtual void eventoAbajo(){
		moverY(10.0);
	}

	virtual void eventoDerecha(){
		moverX(10.0);
	}

	virtual void eventoIzquierda(){
		moverX(-10.0);
	}

	virtual void eventoRESTART(){
		posicion( 30.0, 30.0);
	}
};

#endif
