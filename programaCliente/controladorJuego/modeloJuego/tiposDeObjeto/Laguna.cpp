/*
 * Laguna.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: rodrizapico
 */

#include "Laguna.h"

Laguna::Laguna() {
	// TODO Auto-generated constructor stub

}

Laguna::~Laguna() {
	// TODO Auto-generated destructor stub
}


// Obtiene la textura que representa al objeto.
Textura * Laguna::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(LAGUNA);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * Laguna::obtenerSprite(){

	Vector2D origen; origen.x = 0; origen.y = 0;
	FiguraGeometrica * sprite = espacioOcupado->cambiarDeCoordenadas(origen);

	sprite->rotar(-rotacion);
	sprite->escalar(sprite->calcularBaricentro(), 0.15);

	return sprite;
}
