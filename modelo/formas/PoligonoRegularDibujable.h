#ifndef POLIGONODIBUJABLE_H
#define POLIGONODIBUJABLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../../utiles/Logger.h"
#include "../interfaces/IDibujable.h"
#include "../../Window.h"

class PoligonoRegularDibujable: public IDibujable {

private:
	int nVertices;
	float32 escala;

public:
	PoligonoRegularDibujable() {
		nVertices = 5;
		escala = 1;
	}
	~PoligonoRegularDibujable() { }

	virtual void render() {

		// Calculo la posicion de los vertices.

		Sint16 vx[nVertices]; Sint16 vy[nVertices];

		for (int i = 0; i < nVertices; i++) {
			float thita = (2 * i * PI / nVertices) - (angulo);
			vx[i] = ( posicion.x + escala * cos(thita) ) * Window::wRatio;
			vy[i] = ( posicion.y - escala * sin(thita) ) * Window::hRatio;
		}


		int status;
		status = filledPolygonRGBA(dRenderer, vx, vy, nVertices, color.r, color.g, color.b, color.a);
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

	void setNumVertices(int nvert) {
		nVertices = nvert;
	}

	void setEscala(float32 e){
		escala = e;
	}

};

#endif
