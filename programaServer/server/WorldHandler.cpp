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
#include "../modelo/Fireball.h"


WorldHandler::WorldHandler(ControladorUsuarios & c, ControladorEnemigos & en, std::string config):
	controlador(c), worldB2D(NULL), army(en), configFile(config){}

// El programa espera a que haya una cantidad suficiente de jugadores.
void WorldHandler::esperarConexiones(){
	// Espera a que se llene el escenario.
	while (!controlador.escenarioLleno()) {
		std::cout << "esperando mas conexiones para iniciar la partida." << std::endl;
		usleep(200000);
	}

	std::cout << "se lleno el mapa, iniciando partida." << std::endl;
}

void WorldHandler::limpiarNivel(){
	// Destruye el nivel.
	std::cout << "MUERE MUNDO" << std::endl;
	delete worldB2D;
	worldB2D = NULL;
	std::cout << "MUERE MUNDO2" << std::endl;
	// Resettea los PJs.
	for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){
		(*it).second->inicializado = false;
	}
}

// Cuando se llena el mapa, comienza la partida.
resultado_t WorldHandler::simularPartida(){

	std::string nextLevel;

	resultado_t resultado = GANARON;

	// Itera sobre todos los niveles.
	while (nextLevel != "LASTLEVEL" && resultado == GANARON){

		std::cout << "cargando siguiente nivel: " << nextLevel << "..." << std::endl;

		// Simula el nivel.
		if (inicializador.init(configFile, &worldB2D, &contactListener, army, nextLevel)){

			// Juega el nivel.
			resultado = loopPrincipal();
			for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){
				if ((*it).second && (*it).second->online && (*it).second->inicializado) {
					(*it).second->vida = (*it).second->getLives();
				}
			}


			// Limpia el world y aquello que sea necesario.
			limpiarNivel();

			// Asigna el archivo de configuracion necesario para cargar el proximo nivel.
			configFile = nextLevel;

		} else {
			limpiarNivel();
			return ERROR_RESULTADO;
		}

	}

	return resultado;
}

void* WorldHandler::run(){

	// Loop infinito de partidas. Cada partida comienza cuando hay suficientes jugadores para comenzar,
	// segun se indique en el archivo de partida cargado al levantar el servidor.
	while (true){

		// El programa espera a que haya una cantidad suficiente de jugadores.
		esperarConexiones();

		// Cuando se llena el mapa, comienza la partida.
		resultado_t resultado = simularPartida();

		controlador.notificarFinDePartida(resultado);

	}

	return NULL;
}

resultado_t WorldHandler::loopPrincipal() {

	//Loop infinito en busca de mensajes para procesar
	bool quit = false;
	resultado_t resultado;

	while(!quit){

		//std::cout << "simulando... " << std::endl;

		int count = 0;
		float freq = 600.0f;

		// Cuenta cuantos usuarios estan online.
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){
			if ((*it).second && (*it).second->online && (*it).second->inicializado) {
				count++;
			}
		}

		//std::cout << "simulando... eligiendo estrategia enemigos." << std::endl;

		if(count > 0) {
			army.strategy(worldB2D, controlador);
		} else {
			army.strategy(NULL, controlador);
		}

		//std::cout << "simulando... setteando frecuencia." << std::endl;

		if(count == 1)
			freq = 20000.0f;
		if(count == 2)
			freq = 12000.0f;
		if(count == 3)
				freq = 9000.0f;
		if(count == 4)
				freq = 6000.0f;
		//std::cout << "freq: " << freq << '\n';		// Simula.

		//std::cout << "simulando... calculando steps" << std::endl;

		for(int i=0;i<10;i++) {
			worldB2D->Step(1.0f/freq, 8, 5);
		};

		// Clean powers (bodies) from world
		//this->cleanPowers();

		// Updatea enemigos

		//std::cout << "simulando... updateando enemigos." << std::endl;

		if(count > 0) {
			army.update(true, controlador);
		} else {
			army.update(false, controlador);
		}

		//std::cout << "simulando... updateando PJs." << std::endl;

		bool quedaPJvivo = false;

		if (army.isMapCleared()) {
			quit = true;
			resultado = GANARON;
			std::cout << "NO HAY MS BICHOS" << std::endl;
			return resultado;
		}

		// Procesa uno por uno todos los usuarios, inicializandolos, moviendo sus
		// PJs o camaras, o ignorandolos si estan desconectados.
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){

			// Saltea al usuario si este no esta conectado.
			if (!(*it).second->online) continue;

			// Inicializa al PJ del usuario si este todavia no lo fue.
			if (!(*it).second->inicializado) {
				std::cout << "inicializando PJ" << std::endl;
				(*it).second->inicializarPJ(worldB2D, configFile);
			}
			if( (*it).second->isPJAlive()) {
				quedaPJvivo = true;
				//std::cout<<"pjvivo"<<std::endl;
				(*it).second->procesarNotificaciones();
				(*it).second->actualizarPJ();
			}

			//(*it).second->esperarSenial();
			//usleep(20000);
		}

		if (!quedaPJvivo){
			quit = true;
			resultado = PERDIERON;
			std::cout << "NO HAY MAS JUGADORES" << std::endl;
		}

	}

	return resultado;
}

