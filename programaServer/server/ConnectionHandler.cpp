/*
 * ConnectionHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "ConnectionHandler.h"
#include "../utiles/tipos.h"
#include "../utiles/Timer.h"
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


	//The frames per second timer
	Timer fpsTimer;
	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();


	// Inicia la comunicacion enviando el numero de cliente.
	std::string message = SSTR(clientNumber);
	m_stream->send(message);

	std::cout << "el mensaje enviado es: " << message << std::endl;

	WorkItem * newPJ = new WorkItem;
	newPJ->type = NEWPJ;
	newPJ->PJnum = clientNumber;
	m_queue.add(newPJ);

	std::cout << "creado WorkItem NEWPJ" << std::endl;

	ssize_t len;
	bool quit = false;
	std::string inMessage, outMessage;

	while (!quit){

		inMessage = "NOTDONE";

		// Recibe todos los eventos sucedidos en el cliente.
		while (inMessage != "DONE"){
			len = m_stream->receive(inMessage);
			if (len <= 0) {
				quit = true;
				std::cout << "quiteando" << std::endl;
				break;
			}
			if (inMessage != "DONE") {
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

		if (quit) break;

		// Envia la escala mundo->ventana.
		// TODO: HARDCODEADO!!
		outMessage = SSTR(1/0.05f);
		len = m_stream->send(outMessage);
		if (len <= 0) {
			quit = true;
			std::cout << "quiteando" << std::endl;
		}

		// Bloquea la lista para evitar modificaciones mientras se envia.
		renderList.lock();

		// Envia los elementos que deben ser renderizados.
		for(ThreadSafeList<WorldItem*>::iterator it=renderList.begin(); it != renderList.end(); ++it){
			outMessage = (*it)->serializar();
			len = m_stream->send(outMessage);
			if (len <= 0) {
				quit = true;
				std::cout << "quiteando" << std::endl;
				break;
			}
		}

		renderList.unlock();

		// Envia un ultimo mensaje informando que se termino.
		outMessage = "DONE";
		len = m_stream->send(outMessage);
		if (len <= 0) {
			quit = true;
			std::cout << "quiteando" << std::endl;
		}

		float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
		if (avgFPS > 2000) {
			fpsTimer.stop();
			fpsTimer.start();
			countedFrames = 0;
		}

		std::cout << avgFPS << " FPS avg" << std::endl;
		++countedFrames;

		cond.signal();
	}

	WorkItem * item = new WorkItem;
	item->type = DISCONNECTED;
	item->PJnum = clientNumber;
	m_queue.add(item);

	cond.signal();

	delete m_stream;

	printf("Conexion terminada.\n");
	return NULL;
}

