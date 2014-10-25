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




WorldHandler::WorldHandler(ColaTrabajo<WorkItem*> & queue,
		ThreadSafeList<WorldItem*> (&rList)[4],
		ConditionVariable (& c)[4]) :
	m_queue(queue), renderList(rList), worldB2D(NULL), cond(c) {
	numJugadores = 0;
}

void* WorldHandler::run(){

	std::string configFile = "defaultConfig.json";

	if (inicializador.init(configFile, &worldB2D, &contactListener)) loopPrincipal();

	return NULL;
}

bool WorldHandler::loopPrincipal() {

	// Asigna la cantidad maxima de pjs que puede haber en el mundo.
	vectorPJ.resize(4, NULL);

	//Loop infinito en busca de mensajes para procesar
	bool quit = false;
	while(!quit){

		WorkItem* item;
		std::string configFile = "defaultConfig.json";

		while ( ( item = m_queue.nonLockingRemove() ) != NULL ){
			switch (item->type){
			case NEWPJ:
				printf("Procesando: %d\n", item->PJnum);

				vectorPJ[item->PJnum-1] = inicializador.pjInit(&worldB2D, renderList[item->PJnum-1],
						configFile, item->PJnum);
				if (!vectorPJ[item->PJnum-1]) {
					//TODO: Error handling
					std::cout << "hubo un error al crear el PJ" << std::endl;
				}
				numJugadores++;
				break;
			case DISCONNECTED:
				vectorPJ[item->PJnum-1]->online = false;
				break;
			case KEYEVENT:
				switch(item->key){
				case ARRIBA:
					vectorPJ[item->PJnum-1]->eventoArriba();
					break;

				case IZQUIERDA:
					vectorPJ[item->PJnum-1]->eventoIzquierda();
					break;

				case DERECHA:
					vectorPJ[item->PJnum-1]->eventoDerecha();
					break;

				case SOLTOARRIBA:
					vectorPJ[item->PJnum-1]->eventoSoltoArriba();
					break;

				case SOLTOIZQUIERDA:
					vectorPJ[item->PJnum-1]->eventoSoltoIzquierda();
					break;
				case SOLTODERECHA:
					vectorPJ[item->PJnum-1]->eventoSoltoDerecha();
					break;
				case ZOOMIN:
					vectorPJ[item->PJnum-1]->camera->eventoZoomIn();
					break;
				case ZOOMOUT:
					vectorPJ[item->PJnum-1]->camera->eventoZoomOut();
					break;
				case SOLTOZOOMIN:
					break;
				case SOLTOZOOMOUT:
					break;
				}
				break;
			}

			delete(item);
		}


		for(int i=0;i<10;i++) worldB2D->Step(1.0f/600.0f, 8, 5);

		// TODO: testear esto con 2 maquinas.
		for(int i = 0; i < numJugadores; i++)
			if (vectorPJ[i]->online){
				vectorPJ[i]->update();
				cond[i].wait();
			}


		usleep(23000);

	}

	return true;
}
