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
			this->cleanPowers();
		};

		// Clean powers (bodies) from world
		//this->cleanPowers();

//		int j = 0;
//		for(b2Body* cuerpo = worldB2D->GetBodyList(); cuerpo; cuerpo = cuerpo->GetNext() ){
//			WorldItem* item = (WorldItem*) cuerpo->GetUserData();
//			worlditem_t tipo = *(worlditem_t*) &item->tipo;
//			//int tipo = (int) t;
//			if( item->eliminado )
//				printf("j: %i eliminado tipo: %i\n", j, tipo);
//			else
//				printf("j: %i noooo eliminado tipo: %i tipoPJ: %i\n", j, tipo, PJ);
//			j++;
//		}


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
		void* fixData = body->GetFixtureList()->GetUserData();
		if( *((int*)(&fixData)) == PODERHIELO) {
			if( ( (snowball*) body->GetUserData() )->forDelete() ){
				delete ((snowball*) body->GetUserData());
			}
		}

		if( *((int*)(&fixData)) == sensorSORPRESA) {
			if( ( (Sorpresa*) body->GetUserData() )->forDelete() ){
				delete ((Sorpresa*) body->GetUserData());
			}
		}
		if( *((int*)(&fixData)) == BOLASNOW) {
			if( ( (BolaEnemigo*) body->GetUserData() )->forDelete() ){
				delete ((BolaEnemigo*) body->GetUserData());
			}
			else
				((BolaEnemigo*) body->GetUserData())->aumentarTiempo();
		}
		body = body->GetNext();
	}
}
