/*
 * serverMain.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: matias
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../Threads/Thread.h"
#include "ColaTrabajo.h"
#include "TCPAcceptor.h"
#include "ConnectionHandler.h"
#include "WorkItem.h"
#include "WorldHandler.h"


int main(int argc, char** argv)
{
    // Process command line arguments
    if ( argc < 3 || argc > 4 ) {
        printf("Uso: %s <JSON Mapa> <Puerto> [<IP Opcional>]\n", argv[0]);
        exit(-1);
    }

    int port = atoi(argv[2]); //Puerto en el que escucha alas conexiones.
    string ip; //IP en el que escucha.
    if (argc == 4) {
        ip = argv[3];
    }

    //TODO: Cargar el json y el world.

    // Creo la cola de mensajes para procesar.
    ColaTrabajo<WorkItem*>  queue;

    //Creo el procesador de mensajes
    WorldHandler* world = new WorldHandler(queue);
    if (!world){
    	printf("Nose pudo crear el connection handler.\n");
    	exit(1);
    }
    world->start();

    // Create an acceptor then start listening for connections
    TCPAcceptor* connectionAcceptor;
    if (ip.length() > 0) {
        connectionAcceptor = new TCPAcceptor(port, (char*)ip.c_str());
    }
    else {
        connectionAcceptor = new TCPAcceptor(port);
    }
    if (!connectionAcceptor || connectionAcceptor->start() != 0) {
        printf("Could not create an connection acceptor\n");
        exit(1);
    }

    //Loop infinito esperando conexiones.
    while (1) {
        TCPStream* connection = connectionAcceptor->accept();
        if (!connection) {
            printf("Could not accept a connection\n");
            continue;
        }

        ConnectionHandler* handler = new ConnectionHandler(queue, connection);
        if (!handler) {
            printf("Could not create ConnectionHandler.\n");
            exit(1);
        }else handler->start();

    }

    // Should never get here
    exit(0);
}

