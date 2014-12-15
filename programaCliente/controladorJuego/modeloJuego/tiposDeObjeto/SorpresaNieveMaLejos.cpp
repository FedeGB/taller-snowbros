/*
 * SorpresaNieveMaLejos.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: rodrizapico
 */

#include "SorpresaNieveMaLejos.h"

SorpresaNieveMaLejos::SorpresaNieveMaLejos() {
	// TODO Auto-generated constructor stub

}

SorpresaNieveMaLejos::~SorpresaNieveMaLejos() {
	// TODO Auto-generated destructor stub
}

// Obtiene la textura que representa al objeto.
Textura * SorpresaNieveMaLejos::obtenerTextura(){

	ServicioControladorDeTexturas * controladorTex = LocalizadorDeServicios::obtenerControladorDeTexturas();
	Textura * tex = controladorTex->obtenerTextura(SORPRESALEJOS);

	return tex;
}

// Calcula el sprite a dibujar segun el estado actual del objeto.
FiguraGeometrica * SorpresaNieveMaLejos::obtenerSprite(){

	FiguraGeometrica * sprite = FiguraGeometrica::generarRectangulo(0,0,1,1,0);
	return sprite;
}
