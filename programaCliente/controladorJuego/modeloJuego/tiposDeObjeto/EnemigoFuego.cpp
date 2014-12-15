/*
 * EnemigoFuego.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "EnemigoFuego.h"

EnemigoFuego::EnemigoFuego() {
	acumuladorCaminando = 0;
	acumuladorSaltando = 0;
	acumuladorAtacando = 0;
}

EnemigoFuego::~EnemigoFuego() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * EnemigoFuego::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(ENEMIGOFUEGO);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * EnemigoFuego::obtenerSprite(){

	SonidosMap * sonidos = LocalizadorDeServicios::obtenerSonidos();
	FiguraGeometrica * sprite;
	int x, y, w = 24, h = 32;

	switch (estado){
	case PARADO:
		x = 86; y = 1;
		break;
	case CAMINANDO:
		acumuladorSaltando = 0;
		acumuladorAtacando = 0;
		y = 1;
		switch( (acumuladorCaminando / 15) % 2 ){
		case 0:
			x = 142;
			break;
		case 1:
			x = 114;
			break;
		}
		acumuladorCaminando++;
		break;
	case SALTANDO:
		acumuladorCaminando = 0;
		acumuladorAtacando = 0;
		y = 34;
		switch( (acumuladorSaltando / 15) ){
		case 0:
			x = 142;
			break;
		case 1:
			x = 114;
			break;
		default:
			x = 86;
			break;
		}
		acumuladorSaltando++;
		break;

	case ATACANDO:
		acumuladorCaminando = 0;
		acumuladorSaltando = 0;
		if (acumuladorAtacando % 45 == 44) (*sonidos)[DISPARO_SORPRESA]->reproducir();
		switch( (acumuladorAtacando / 15) % 3 ){
		case 0:
			x = 57; y = 34;
			break;
		case 1:
			x = 57; y = 34;
			break;
		case 2:
			x = 114; y = 34;
			break;
		}
		acumuladorAtacando++;
		break;

	}

	sprite = FiguraGeometrica::generarRectangulo(x / 340.0f, y / 66.0f, w / 340.0f, h / 66.0f, 0);

	return sprite;
}
