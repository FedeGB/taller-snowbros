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
	if( pEstado != ESTADO_SALTANDO )
	{
		pEstado = ESTADO_SALTANDO;
		printf("EVENTO ARRIBA: SALTO\n");
	}
	moverY(-5.0);
}

void Personaje::eventoDerecha()
{
	if( pEstado != ESTADO_DERECHA )
	{
		pEstado = ESTADO_DERECHA;
		cargarImagen("imagenes/derecha.png");
	}

	moverX(5.0);
}

void Personaje::eventoIzquierda()
{
	if( pEstado != ESTADO_IZQUIERDA )
	{
		pEstado = ESTADO_IZQUIERDA;
		cargarImagen("imagenes/izquierda.png");
	}
	moverX(-5.0);
}

void Personaje::eventoAbajo()
{
	if( pEstado != ESTADO_ABAJO )
	{
		pEstado = ESTADO_ABAJO;
		printf("EVENTO ABAJO: MOVER ABAJO\n");
	}
	moverY(5.0);
}

void Personaje::eventoRESTART()
{
	if( pEstado !=  ESTADO_PARADO)
	{
		pEstado = ESTADO_PARADO;
		cargarImagen("imagenes/parado.png");
	}
	posicion(100.0 ,100.0);
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
