/*
 * PelotaDeNieve.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#include "PelotaDeNieve.h"

PelotaDeNieve::PelotaDeNieve() {
	// TODO Auto-generated constructor stub

}

PelotaDeNieve::~PelotaDeNieve() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * PelotaDeNieve::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(PELOTADENIEVE);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * PelotaDeNieve::obtenerSprite(){

	FiguraGeometrica * sprite = FiguraGeometrica::generarRectangulo(0, 0, 1, 1, 0);
	return sprite;
}
