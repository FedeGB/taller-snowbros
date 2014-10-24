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

	//The frames per second timer
	Timer fpsTimer;
	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();

	// Asigna la cantidad maxima de pjs que puede haber en el mundo.
	vectorPJ.resize(4, NULL);

	//Loop infinito en busca de mensajes para procesar
	bool quit = false;
	while(!quit){

		WorkItem* item;
		std::string configFile = "defaultConfig.json";

		while ( ( item = m_queue.nonLockingRemove() ) != NULL ){
			//printf("Procesando: %s\n", item->m_message.c_str());
			//item->parse();
			switch (item->type){
			case NEWPJ:
				vectorPJ[item->PJnum-1] = inicializador.pjInit(&worldB2D, renderList[item->PJnum-1],
						configFile, item->PJnum);
				if (!vectorPJ[item->PJnum-1]) {
					//TODO: Error handling
					std::cout << "hubo un error al crear el PJ" << std::endl;
				}
				numJugadores++;
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
				}
				break;
			}

			delete(item);
		}


		for (std::vector<Personaje*>::iterator it = vectorPJ.begin() ; it != vectorPJ.end(); ++it)
			if ((*it) != NULL) (*it)->update();

		for(int i=0;i<10;i++) worldB2D->Step(1.0f/600.0f, 8, 5);

		// TODO: testear esto con 2 maquinas.
		//for(int i = 0; i < numJugadores; i++) cond[i].wait();

		float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
		if (avgFPS > 2000) {
			fpsTimer.stop();
			fpsTimer.start();
			countedFrames = 0;
		}
		std::cout << avgFPS << " FPS avg" << std::endl;
		++countedFrames;

		usleep(23000);

	}

	return true;
}
