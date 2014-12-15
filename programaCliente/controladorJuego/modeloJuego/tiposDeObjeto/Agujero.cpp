/*
 * Agujero.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: rodrizapico
 */

#include "Agujero.h"

Agujero::Agujero() {
	// TODO Auto-generated constructor stub

}

Agujero::~Agujero() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * Agujero::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(AGUJERO);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * Agujero::obtenerSprite(){

	Vector2D origen; origen.x = 0; origen.y = 0;
	FiguraGeometrica * sprite = espacioOcupado->cambiarDeCoordenadas(origen);

	sprite->rotar(-rotacion);
	sprite->escalar(sprite->calcularBaricentro(), 0.15);

	return sprite;
}
