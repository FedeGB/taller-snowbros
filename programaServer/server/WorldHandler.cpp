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


WorldHandler::WorldHandler(ControladorUsuarios & c, ControladorEnemigos & en, std::string config):
	controlador(c), worldB2D(NULL), army(en), configFile(config){}

void* WorldHandler::run(){

	if (inicializador.init(configFile, &worldB2D, &contactListener, army)) loopPrincipal();

	return NULL;
}

bool WorldHandler::loopPrincipal() {

	//Loop infinito en busca de mensajes para procesar
	bool quit = false;
	while(!quit){
		int count = 0;
		float freq =600.0f;
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){
			if ((*it).second && (*it).second->online) {
				count++;
			}
		}
		if(count > 0) {
			army.strategy(true);
		} else {
			army.strategy(false);
		}
		if(count == 1)
			freq = 20000.0f;
		if(count == 2)
			freq = 12000.0f;
		if(count == 3)
				freq = 9000.0f;
		if(count == 4)
				freq = 6000.0f;
		// Simula.
		for(int i=0;i<10;i++) worldB2D->Step(1.0f/freq, 8, 5);

		// Updatea enemigos
		if(count > 0) {
			army.update(true);
		} else {
			army.update(false);
		}


		// Procesa uno por uno todos los usuarios, inicializandolos, moviendo sus
		// PJs o camaras, o ignorandolos si estan desconectados.
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){

			// Saltea al usuario si este no esta conectado.
			if (!(*it).second->online) continue;

			// Inicializa al PJ del usuario si este todavia no lo fue.
			if (!(*it).second->inicializado) (*it).second->inicializarPJ(worldB2D, configFile);

			(*it).second->procesarNotificaciones();
			(*it).second->actualizarPJ();
			//(*it).second->esperarSenial();
			//usleep(20000);
		}

	}

	return true;
}
