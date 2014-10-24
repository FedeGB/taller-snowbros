/*
 * ConnectionHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "ConnectionHandler.h"
#include "../utiles/tipos.h"
#include <iostream>

ConnectionHandler::ConnectionHandler(ColaTrabajo<WorkItem*>& queue,
		ThreadSafeList<WorldItem*> & rList,
		TCPStream* stream,
		ConditionVariable & c,
		int num) :
	m_queue(queue), renderList(rList), m_stream(stream), clientNumber(num), cond(c){}

void* ConnectionHandler::run() {
	// Remove 1 item at a time and process it. Blocks if no items are
	// available to process.
	printf("Conexion con: %s:%d establecida.\n", m_stream->getPeerIP().c_str() , m_stream->getPeerPort());


	// Inicia la comunicacion enviando el numero de cliente.
	std::string message = SSTR(clientNumber);
	m_stream->send(message);

	std::cout << "el mensaje enviado es: " << message << std::endl;

	WorkItem * newPJ = new WorkItem;
	newPJ->type = NEWPJ;
	newPJ->PJnum = clientNumber;
	m_queue.add(newPJ);

	std::cout << "creado WorkItem NEWPJ" << std::endl;

	int len;
	bool quit = false;
	std::string inMessage, outMessage;

	while (!quit){

		inMessage = "NOTDONE";

		// Recibe todos los eventos sucedidos en el cliente.
		while (inMessage != "DONE"){
			len = m_stream->receive(inMessage);
			if (len <= 0) {
				quit = true;
				break;
				std::cout << "quiteando" << std::endl;
			}
			if (inMessage != "DONE") {
				std::cout << inMessage << std::endl;
				WorkItem * item = new WorkItem;
				item->type = KEYEVENT;
				item->PJnum = clientNumber;
				if (inMessage == "UPPRESSED") item->key = ARRIBA;
				else if (inMessage == "LEFTPRESSED") item->key = IZQUIERDA;
				else if (inMessage == "RIGHTPRESSED") item->key = DERECHA;
				else if (inMessage == "UPRELEASED") item->key = SOLTOARRIBA;
				else if (inMessage == "LEFTRELEASED") item->key = SOLTOIZQUIERDA;
				else if (inMessage == "RIGHTRELEASED") item->key = SOLTODERECHA;

				m_queue.add(item);
			}
		}

		// Envia la escala mundo->ventana.
		// TODO: HARDCODEADO!!
		outMessage = SSTR(1/0.05f);
		m_stream->send(outMessage);

		// Bloquea la lista para evitar modificaciones mientras se envia.
		renderList.lock();

		// Envia los elementos que deben ser renderizados.
		for(ThreadSafeList<WorldItem*>::iterator it=renderList.begin(); it != renderList.end(); ++it){
			outMessage = (*it)->serializar();
			m_stream->send(outMessage);
		}

		renderList.unlock();

		// Envia un ultimo mensaje informando que se termino.
		outMessage = "DONE";
		m_stream->send(outMessage);

		cond.signal();
	}

	delete m_stream;

	printf("Conexion terminada.\n");
	return NULL;
}

