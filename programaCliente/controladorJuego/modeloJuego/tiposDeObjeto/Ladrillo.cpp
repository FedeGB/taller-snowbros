/*
 * Ladrillo.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "Ladrillo.h"

Ladrillo::Ladrillo() {
	// TODO Auto-generated constructor stub

}

Ladrillo::~Ladrillo() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * Ladrillo::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(LADRILLO);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * Ladrillo::obtenerSprite(){

	Vector2D origen; origen.x = 0; origen.y = 0;
	FiguraGeometrica * sprite = espacioOcupado->cambiarDeCoordenadas(origen);

	sprite->rotar(-rotacion);
	sprite->escalar(sprite->calcularBaricentro(), 0.15);

	return sprite;
}
