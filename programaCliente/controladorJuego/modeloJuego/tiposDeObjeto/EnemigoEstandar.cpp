/*
 * EnemigoEstandar.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "EnemigoEstandar.h"

EnemigoEstandar::EnemigoEstandar() {

	acumuladorCaminando = 0;
	acumuladorSaltando = 0;
	acumuladorAtrapado = 0;
}

EnemigoEstandar::~EnemigoEstandar() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * EnemigoEstandar::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(ENEMIGOESTANDAR);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * EnemigoEstandar::obtenerSprite(){

	FiguraGeometrica * sprite;
	int x, y = 1, w = 24, h = 26;

	switch (estado){
	case PARADO:
		x = 26;
		break;
	case CAMINANDO:
		acumuladorSaltando = 0;
		switch( (acumuladorCaminando / 15) % 2 ){
		case 0:
			x = 56;
			break;
		case 1:
			x = 85;
			break;
		}
		acumuladorCaminando++;
		break;
	case SALTANDO:
		acumuladorCaminando = 0;
		y = 29; h = 31;
		switch( (acumuladorSaltando / 30) ){
		case 0:
			x = 56;
			break;
		case 1:
			x = 28;
			break;
		default:
			x = 28;
			break;
		}
		acumuladorSaltando++;
		break;
	case ATRAPADO:
		acumuladorCaminando = 0;
		acumuladorSaltando = 0;
		y = 29; h = 31;
		switch( (acumuladorAtrapado / 15) % 2 ){
		case 0:
			x = 56;
			break;
		case 1:
			x = 149;
			break;
		default:
			x = 149;
			break;
		}
		acumuladorAtrapado++;
		break;
	}

	sprite = FiguraGeometrica::generarRectangulo(x / 228.0f, y / 114.0f, w / 228.0f, h / 114.0f, 0);

	return sprite;
}
