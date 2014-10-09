/*
 * RecvThread.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: matias
 */

#include "RecvThread.h"

RecvThread::RecvThread(ColaTrabajo<Message*>& queue, TCPStream* stream) : m_queue(queue), m_stream(stream) {
	closed = true;
}

void* RecvThread::run(){
	closed = false;
	char input[256]; //TODO Cambiar por buffer dinamico.
	int len;
	while ((len = m_stream->receive(input, sizeof(input)-1)) > 0 ){
		input[len] = NULL;
		Message* item = new Message(std::string(input), m_stream->getPeerIP());
		m_queue.add(item);
	}
	closed = true;
	return NULL;
}

bool RecvThread::readyToClose(){
	return closed;
}
