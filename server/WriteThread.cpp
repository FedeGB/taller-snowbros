/*
 * WriteThread.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: matias
 */

#include "WriteThread.h"

WriteThread::WriteThread(ColaTrabajo<Message*> queue, TCPStream* stream) : m_queue(queue), m_stream(stream) {
	closed = false;
}

void* WriteThread::run(){
	//Recorro de forma infinita en busca de paquetes a enviar.

	while(1){
		Message* item = m_queue.remove();
		//TODO enviar y garantizar la transferencia.
		delete item;
	}

	return NULL;
}

bool WriteThread::readyToClose(){
	return closed;
}
