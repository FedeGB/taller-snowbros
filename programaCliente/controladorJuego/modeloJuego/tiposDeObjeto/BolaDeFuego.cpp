/*
 * BolaDeFuego.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "BolaDeFuego.h"

BolaDeFuego::BolaDeFuego() {
	// TODO Auto-generated constructor stub

}

BolaDeFuego::~BolaDeFuego() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * BolaDeFuego::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(BOLADEFUEGO);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * BolaDeFuego::obtenerSprite(){

	FiguraGeometrica * sprite = FiguraGeometrica::generarRectangulo(0, 0, 1, 1, 0);
	return sprite;
}
