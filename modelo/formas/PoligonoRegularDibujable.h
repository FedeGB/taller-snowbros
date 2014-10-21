#ifndef POLIGONODIBUJABLE_H
#define POLIGONODIBUJABLE_H

#include <SDL2/SDL.h>
#include "../../utiles/Logger.h"
#include "../interfaces/ITexturizable.h"
#include "../../vista/Camera.h"

class PoligonoRegularDibujable: public ITexturizable{

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

		GLfloat vx[nVertices]; GLfloat vy[nVertices];

		// Calculo la posicion de los vertices.
		calcularVertices(vx, vy, nVertices, escala, escala, angulo, Camera::WORLDTOWINDOWSCALE);

		int status = 0;
		if( _tex != NULL )
			_tex->dibujar(vx, vy, s, t, nVertices);
		else
			dibujarV(vx, vy, nVertices, color.r, color.g, color.b, color.a);

		if(status != 0) {
			Logger& log = * Logger::Instancia();
			if(log.abrirLog(DIBUJABLELOG)) {
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

	void calcularVertices(GLfloat* vx, GLfloat* vy, int nVertices, float escX, float escY, float ang, float worldtowindowscale){
		for (int i = 0; i < nVertices; i++) {
			float thita = (2 * i * PI / nVertices) - (ang);
			vx[i] = ( posicion.x + escX * cos(thita) ) * worldtowindowscale;
			vy[i] = ( posicion.y - escY * sin(thita) ) * worldtowindowscale;
		}
	}

	GLuint getCantidadDeVertices() { return nVertices; }

};

#endif
