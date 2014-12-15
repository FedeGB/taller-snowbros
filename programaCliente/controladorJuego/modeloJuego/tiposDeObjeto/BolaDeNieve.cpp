/*
 * BolaDeNieve.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "BolaDeNieve.h"

BolaDeNieve::BolaDeNieve() {
	// TODO Auto-generated constructor stub

}

BolaDeNieve::~BolaDeNieve() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * BolaDeNieve::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(BOLADENIEVE);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * BolaDeNieve::obtenerSprite(){

	FiguraGeometrica * sprite = FiguraGeometrica::generarRectangulo(0, 0, 1, 1, 0);
	return sprite;
}
