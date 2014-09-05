/*
 * Personaje.cpp
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#include "Personaje.h"

Personaje::Personaje() : pEstado(ESTADO_PARADO){}

Personaje::~Personaje() {}

void Personaje::eventoArriba()
{
	printf("EVENTO ARRIBA: SALTO\n");
}

void Personaje::eventoDerecha()
{
	printf("EVENTO DERECHA: MOVER DERECHA\n");
}

void Personaje::eventoIzquierda()
{
	printf("EVENTO IZQUIERDA: MOVER IZQUIERDA\n");
}

void Personaje::eventoAbajo()
{
	printf("EVENTO ABAJO: MOVER ABAJO\n");
}

void Personaje::eventoRESTART()
{
	printf("EVENTO RESTART: RESTART PERSONAJE\n");
}

bool Personaje::saltar()
{
	bool pudoSaltar = true;

	if( pEstado == ESTADO_SALTANDO )
		return !pudoSaltar;

	//TODO aplicar el salto con box2d
	pEstado = ESTADO_SALTANDO;
	printf("SALTAR!\n");

	return pudoSaltar;
}
