/*
 * PosicionadorObjetos.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "PosicionadorObjetos.h"

// Crea un objeto encargado de posicionr los elementos en pantalla.
PosicionadorObjetos::PosicionadorObjetos(){

}

// Destruye el posicionador.
PosicionadorObjetos::~PosicionadorObjetos(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void PosicionadorObjetos::notificar(tipo_notificacion_t notificacion){

}

// Posiciona un objeto en la region de pantalla donde debe ser dibujado.
// La region es determinada por el parametro 'tipo'.
void PosicionadorObjetos::posicionar(Posicionable * objeto, tipo_objeto_t tipo){

	// Rectangulo que va a contener la informacion sobre el area de dibujo.
	SDL_Rect areaDeDibujo;

	// Determina cual es el objeto a posicionar.
	switch(tipo.tipo){
	case NOMBREJUGADOR:

		areaDeDibujo.x = 30 + 150 * (tipo.numero - 1);
		areaDeDibujo.y = 30;
		areaDeDibujo.w = 120;
		areaDeDibujo.h = 25;
		break;
	case PUNTAJEJUGADOR:

		areaDeDibujo.x = 30 + 150 * (tipo.numero - 1);
		areaDeDibujo.y = 60;
		areaDeDibujo.w = 120;
		areaDeDibujo.h = 25;
		break;
	case VIDASJUGADOR:

		areaDeDibujo.x = 30 + 150 * (tipo.numero - 1);
		areaDeDibujo.y = 90;
		areaDeDibujo.w = 120;
		areaDeDibujo.h = 25;
		break;
	case CORAZONJUGADOR:

		areaDeDibujo.x = 30 + 150 * (tipo.numero - 1);
		areaDeDibujo.y = 30;
		areaDeDibujo.w = 120;
		areaDeDibujo.h = 25;
		break;
	}

	// Asigna la posicion al objeto.
	objeto->asignarPosicion(areaDeDibujo.x, areaDeDibujo.y);
	objeto->asignarDimensiones(areaDeDibujo.w, areaDeDibujo.h);
	objeto->inicializar();
}
