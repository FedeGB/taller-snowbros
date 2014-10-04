/*
 * vistaPersonaje.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: matias
 */

#include "vistaPersonaje.h"

vistaPersonaje::vistaPersonaje(Personaje* personaje) {
	refPersonaje = personaje;
	imgParado = IMG_Load("../imagenes/parado.png");
	imgIzq = IMG_Load("../imagenes/izquierda.png");
	imgDer = IMG_Load("../imagenes/derecha.png");

}

vistaPersonaje::~vistaPersonaje() {
	// TODO Auto-generated destructor stub
}

