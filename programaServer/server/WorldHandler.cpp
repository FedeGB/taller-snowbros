/*
 * WorldHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "WorldHandler.h"
#include <stdio.h>
#include <unistd.h>
#include "../utiles/Timer.h"




WorldHandler::WorldHandler(ControladorUsuarios & c):
	controlador(c), worldB2D(NULL) {}

void* WorldHandler::run(){

	std::string configFile = "defaultConfig.json";

	if (inicializador.init(configFile, &worldB2D, &contactListener)) loopPrincipal();

	return NULL;
}

bool WorldHandler::loopPrincipal() {

	//Loop infinito en busca de mensajes para procesar
	bool quit = false;
	while(!quit){
		// Simula.
		for(int i=0;i<10;i++) worldB2D->Step(1.0f/300.0f, 8, 5);

		// Procesa uno por uno todos los usuarios, inicializandolos, moviendo sus
		// PJs o camaras, o ignorandolos si estan desconectados.
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){

			// Saltea al usuario si este no esta conectado.
			if (!(*it).second->online) continue;

			// Inicializa al PJ del usuario si este todavia no lo fue.
			if (!(*it).second->inicializado) (*it).second->inicializarPJ(worldB2D);

			(*it).second->procesarNotificaciones();
			(*it).second->actualizarPJ();
			(*it).second->esperarSenial();
		}

	}

	return true;
}
