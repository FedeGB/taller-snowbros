/*
 * SorpresaCorrer.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#include "SorpresaCorrer.h"

SorpresaCorrer::SorpresaCorrer() {
	// TODO Auto-generated constructor stub

}

SorpresaCorrer::~SorpresaCorrer() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * SorpresaCorrer::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(SORPRESACORRER);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * SorpresaCorrer::obtenerSprite(){

	FiguraGeometrica * sprite = FiguraGeometrica::generarRectangulo(0,0,1,1,0);
	return sprite;
}
