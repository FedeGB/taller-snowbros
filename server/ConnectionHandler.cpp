/*
 * ConnectionHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "ConnectionHandler.h"
#include <stdio.h>

ConnectionHandler::ConnectionHandler(ColaTrabajo<Message*>& queue, TCPStream* stream){
	m_stream = stream;
	m_receiver = new RecvThread(queue, m_stream);
	m_writer = new WriteThread(m_toSend, m_stream);
}

void ConnectionHandler::start() {
	// Remove 1 item at a time and process it. Blocks if no items are
	// available to process.
	printf("Conexion con: %s:%d establecida.\n", m_stream->getPeerIP().c_str() , m_stream->getPeerPort());

	m_receiver->start();
	m_writer->start();
}

std::string ConnectionHandler::getPeerIP(){
	return m_stream->getPeerIP();
}

void ConnectionHandler::queueMessage(Message* newItem){
	m_toSend.add(newItem);
}

