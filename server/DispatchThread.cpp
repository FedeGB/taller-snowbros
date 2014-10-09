/*
 * DispatchThread.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: matias
 */

#include "DispatchThread.h"

DispatchThread::DispatchThread(ColaTrabajo<Message*>& queue, list<ConnectionHandler*> connections) :
		m_connections(connections), m_queue(queue) {}

void* DispatchThread::run(){

	//Loop infinito en busca de mensajes para procesar
	while(1){
		Message* item = m_queue.remove();
		for (list<ConnectionHandler*>::iterator it = m_connections.begin(); it != m_connections.end(); it++){
			if ( (*it)->getPeerIP() == item->m_from ) {
				(*it)->queueMessage(item);
				break;
			}
		}
	}

	return NULL;
}

