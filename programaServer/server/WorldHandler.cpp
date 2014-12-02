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

void* WorldHandler::run(){

	if (inicializador.init(configFile, &worldB2D, &contactListener, army)) loopPrincipal();

	return NULL;
}

bool WorldHandler::loopPrincipal() {

	// Espera a que se llene el escenario.
	while (!controlador.escenarioLleno()) {
		std::cout << "esperando mas conexiones para simular." << std::endl;
		usleep(200000);
	}

	std::cout << "se lleno el mapa, iniciando simulacion." << std::endl;

	//Loop infinito en busca de mensajes para procesar
	bool quit = false;
	while(!quit){

		int count = 0;
		float freq =600.0f;

		// Cuenta cuantos usuarios estan online.
		for (ControladorUsuarios::iterator it=controlador.begin(); it!=controlador.end(); ++it){
			if ((*it).second && (*it).second->online && (*it).second->inicializado) {
				count++;
			}
		}

		if(count > 0) {
			army.strategy(worldB2D, controlador);
		} else {
			army.strategy(NULL, controlador);
		}

		if(count == 1)
			freq = 20000.0f;
		if(count == 2)
			freq = 12000.0f;
		if(count == 3)
				freq = 9000.0f;
		if(count == 4)
				freq = 6000.0f;
		//std::cout << "freq: " << freq << '\n';		// Simula.

		for(int i=0;i<10;i++) {
			worldB2D->Step(1.0f/freq, 8, 5);
			//this->cleanPowers();
		};

		// Clean powers (bodies) from world
		this->cleanPowers();

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
			if (!(*it).second->inicializado) {
				std::cout << "inicializando PJ" << std::endl;
				(*it).second->inicializarPJ(worldB2D, configFile);
			}
			if( (*it).second->isPJAlive()) {
				(*it).second->procesarNotificaciones();
				(*it).second->actualizarPJ();
			}

			//(*it).second->esperarSenial();
			//usleep(20000);
		}

	}

	return true;
}

void WorldHandler::cleanPowers() {
	b2Body* body = worldB2D->GetBodyList();
	while (body) {
		b2Fixture* fix = body->GetFixtureList();
		if(fix) {
			void* fixData = fix->GetUserData();
			if( *((int*)(&fixData)) == PODERHIELO) {
				if( ( (snowball*) body->GetUserData() )->cayoPorAgujero() )
					((snowball*) body->GetUserData())->moverArriba();

				if( ( (snowball*) body->GetUserData() )->forDelete() ){
					delete ((snowball*) body->GetUserData());
				}
			}

			if( *((int*)(&fixData)) == PODERFUEGO) {
				if( ( (Fireball*) body->GetUserData() )->cayoPorAgujero() )
					((Fireball*) body->GetUserData())->moverArriba();


				if( ( (Fireball*) body->GetUserData() )->forDelete() ){
					delete ((Fireball*) body->GetUserData());
				}
			}


			if( *((int*)(&fixData)) == sensorSORPRESA) {
				if( ( (Sorpresa*) body->GetUserData() )->forDelete() ){
					delete ((Sorpresa*) body->GetUserData());
				}
			}
			if( *((int*)(&fixData)) == BOLASNOW) {
				if( ( (BolaEnemigo*) body->GetUserData() )->cayoPorAgujero() )
					((BolaEnemigo*) body->GetUserData())->moverArriba();


				if( ( (BolaEnemigo*) body->GetUserData() )->forDelete() ){
					delete ((BolaEnemigo*) body->GetUserData());
				}
				else
					((BolaEnemigo*) body->GetUserData())->aumentarTiempo();
			}
			if( *((int*)(&fixData)) == PERSONAJE|| *((int*)(&fixData)) == PIESPJ||(*((int*)(&fixData)) == EMPUJE)) {
						if( ( (Personaje*) body->GetUserData() )->isRespawnable ==true)
							((Personaje*) body->GetUserData())->respawn();
						if( ( (Personaje*) body->GetUserData() )->cayoPorAgujero())
							((Personaje*) body->GetUserData())->moverArriba();
						if( ( (Personaje*) body->GetUserData() )->forDelete()) {
							delete ( (Personaje*) body->GetUserData() );
						}
			}

			if( *((int*)(&fixData)) == ENEMIGO|| *((int*)(&fixData)) == ENEMIGOCONGELADO || *((int*)(&fixData)) == PIESEN || *((int*)(&fixData)) == PIESENCONGELADO  || *((int*)(&fixData)) == ENEMIGOBOLA ) {
						if( ( (EnemigoEstandar*) body->GetUserData() )->cayoPorAgujero()){
							((EnemigoEstandar*) body->GetUserData())->moverArriba();
						}
			}
		}
		body = body->GetNext();
	}
}
