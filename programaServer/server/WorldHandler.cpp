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
		int count = 0;
		float freq =600.0f;
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){
			if ((*it).second && (*it).second->online) {
				std::cout << "HOLLAA";
				count++;
			}
		}
		if(count == 1)
			freq = 18000.0f;
		if(count == 2)
			freq = 12000.0f;
		if(count == 3)
				freq = 9000.0f;
		if(count == 4)
				freq = 6000.0f;
		std::cout << "freq: " << freq << '\n';
		// Simula.
		for(int i=0;i<10;i++) worldB2D->Step(1.0f/freq, 8, 5);

		// Procesa uno por uno todos los usuarios, inicializandolos, moviendo sus
		// PJs o camaras, o ignorandolos si estan desconectados.
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){

			// Saltea al usuario si este no esta conectado.
			if (!(*it).second->online) continue;

			// Inicializa al PJ del usuario si este todavia no lo fue.
			if (!(*it).second->inicializado) (*it).second->inicializarPJ(worldB2D);

			(*it).second->procesarNotificaciones();
			(*it).second->actualizarPJ();
			//(*it).second->esperarSenial();
			//usleep(20000);
		}

	}

	return true;
}
