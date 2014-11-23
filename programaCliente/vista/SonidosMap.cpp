/*
 * SonidosMap.cpp
 *
 *  Created on: 7/11/2014
 *      Author: manuel
 */

#include "SonidosMap.h"

SonidosMap::SonidosMap() {
	inicializado = false;
}

SonidosMap::~SonidosMap() {
	for (SonidosMap::iterator it = this->begin(); it != this->end(); it++){
		if ((*it).second) {
			delete (*it).second;
			(*it).second = NULL;
		}
	}
}

bool SonidosMap::init() {

	if(inicializado) return false;

	if( !loadSonidoSalto() ) return false;
	if( !loadSonidoExplosion() ) return false;
	if( !loadSonidoDisparo() ) return false;
	if( !loadSonidoDisparoSorpresa() ) return false;

	inicializado=true;
	return true;
}

bool SonidosMap::yaInicializado(){
	return inicializado;
}

void SonidosMap::actualizarEstados(){
	for (SonidosMap::iterator it = this->begin(); it != this->end(); it++)
		(*it).second->actualizarEstado();
}

bool SonidosMap::loadSonidoSalto() {

	Sonido* sonido = NULL;
	sonido =  new Sonido();

	if(!sonido ){
		printf("No se pudo cargar el sonido %s\n", SONIDO_SALTO);
		return false;
	}

	if( !sonido->generar(SONIDO_SALTO) ){
		printf("NO SE PUDO GENERAR EL BUFFER PARA SONIDO %s\n", SONIDO_SALTO);
		return false;
	}

	(*this)[SALTO] = sonido;
	return true;
}

bool SonidosMap::loadSonidoExplosion() {

	return true;
}

bool SonidosMap::loadSonidoDisparo() {

	Sonido* sonido = NULL;
	sonido =  new Sonido();

	if(!sonido ){
		printf("No se pudo cargar el sonido %s\n", SONIDO_DISPARO);
		return false;
	}

	if( !sonido->generar(SONIDO_DISPARO) ){
		printf("NO SE PUDO GENERAR EL BUFFER PARA SONIDO %s\n", SONIDO_DISPARO);
		return false;
	}

	(*this)[DISPARO] = sonido;
	return true;
}

bool SonidosMap::loadSonidoDisparoSorpresa() {

	Sonido* sonido = NULL;
	sonido =  new Sonido();

	if(!sonido ){
		printf("No se pudo cargar el sonido %s\n", SONIDO_DISPARO_SORPRESA);
		return false;
	}

	if( !sonido->generar(SONIDO_DISPARO_SORPRESA) ){
		printf("NO SE PUDO GENERAR EL BUFFER PARA SONIDO %s\n", SONIDO_DISPARO_SORPRESA);
		return false;
	}

	(*this)[DISPARO_SORPRESA] = sonido;
	return true;
}
