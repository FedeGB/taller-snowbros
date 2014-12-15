/*
 * SorpresaNieveMasPotente.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#include "SorpresaNieveMasPotente.h"

SorpresaNieveMasPotente::SorpresaNieveMasPotente() {
	// TODO Auto-generated constructor stub

}

SorpresaNieveMasPotente::~SorpresaNieveMasPotente() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * SorpresaNieveMasPotente::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(SORPRESAPOTENTE);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * SorpresaNieveMasPotente::obtenerSprite(){

	FiguraGeometrica * sprite = FiguraGeometrica::generarRectangulo(0,0,1,1,0);
	return sprite;
}
