#ifndef POLIGONOIRREGULARDIBUJABLE_H
#define POLIGONOIRREGULARDIBUJABLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../../utiles/Logger.h"
#include "../interfaces/IDibujable.h"
#include "../../Window.h"

class PoligonoIrregularDibujable: public IDibujable {

private:
	float32 base;
	float32 tapa;
	float32 altura;
	float32 desplazamiento;

public:
	PoligonoIrregularDibujable() {
		base = 1;
		tapa = 1;
		altura = 1;
		desplazamiento = 0;
	}
	~PoligonoIrregularDibujable() { }

	virtual void render() {

		// Calculo la posicion de los vertices.
		Sint16 vx[4]; Sint16 vy[4];

		float32 centroX = ( ( 2 * tapa * desplazamiento + base * desplazamiento + base * tapa + pow(base,2) + pow(tapa,2) ) / (3 * (base + tapa) ) );
		float32 centroY = ( ( altura * (base + 2 * tapa ) ) / ( 3 * ( base + tapa ) ) );

		float32 modulo0 = sqrt( pow(- centroX, 2) + pow(centroY, 2) );
		float32 modulo1 = sqrt( pow(- centroX + base, 2) + pow(centroY, 2) );
		float32 modulo2 = sqrt( pow(- centroX + desplazamiento + tapa, 2) + pow(centroY - altura, 2) );
		float32 modulo3 = sqrt( pow(- centroX + desplazamiento, 2) + pow(centroY - altura, 2) );

		float32 thita0 = PI + atan( centroY / (centroX) ) - angulo;
		float32 thita1 =  2 * PI - atan( centroY / (-centroX + base) ) - angulo;
		float32 thita2 =  atan( (-centroY + altura) / (-centroX + desplazamiento + tapa) ) - angulo;
		float32 thita3 =  PI - atan( (-centroY + altura) / (centroX - desplazamiento) ) - angulo;

		vx[0] = (posicion.x + modulo0 * cos(thita0) ) * Window::wRatio;
		vy[0] = (posicion.y - modulo0 * sin(thita0)) * Window::hRatio;
		vx[1] = (posicion.x + modulo1 * cos(thita1)) * Window::wRatio;
		vy[1] = (posicion.y - modulo1 * sin(thita1)) * Window::hRatio;
		vx[2] = (posicion.x + modulo2 * cos(thita2)) * Window::wRatio;
		vy[2] = (posicion.y - modulo2 * sin(thita2)) * Window::hRatio;
		vx[3] = (posicion.x + modulo3 * cos(thita3)) * Window::wRatio;
		vy[3] = (posicion.y - modulo3 * sin(thita3)) * Window::hRatio;

		int status;

		status = filledPolygonRGBA(dRenderer, vx, vy, 4, color.r, color.g, color.b, color.a);
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

	void setBase(float32 b) {base = b;}
	void setTapa(float32 t) {tapa = t;}
	void setAltura(float32 h) {altura = h;}
	void setDesplazamiento(float32 d) {desplazamiento = d;}


};

#endif
