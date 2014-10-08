/*
 * ConnectionHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "ConnectionHandler.h"
#include <stdio.h>

ConnectionHandler::ConnectionHandler(ColaTrabajo<WorkItem*>& queue, TCPStream* stream) : m_queue(queue), m_stream(stream) {}

void* ConnectionHandler::run() {
	// Remove 1 item at a time and process it. Blocks if no items are
	// available to process.
	printf("Conexion con: %s:%d establecida.\n", m_stream->getPeerIP().c_str() , m_stream->getPeerPort());

	// Echo messages back the client until the connection is
	// closed
	char input[256];
	int len;
	while ((len = m_stream->receive(input, sizeof(input)-1)) > 0 ){
		input[len] = NULL;
		WorkItem* item = new WorkItem(std::string(input));
		m_queue.add(item); //Error aca nose porque
		m_stream->send(input, len);
		printf("thread %lu, echoed '%s' back to the client\n",
			   (long unsigned int)self(), input);
	}
	delete m_stream;

	printf("Conexion terminada.\n");
	return NULL;
}

