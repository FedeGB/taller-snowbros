/*
 * WorldHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "WorldHandler.h"
#include <stdio.h>

WorldHandler::WorldHandler(ColaTrabajo<WorkItem*>& queue) : m_queue(queue) {}

void* WorldHandler::run(){

	//Loop infinito en busca de mensajes para procesar
	while(1){
		WorkItem* item = m_queue.remove();
		printf("Procesando: %s\n", item->m_message.c_str());
		delete(item);
	}

	return NULL;
}

