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

class WorkItem
{
    TCPStream* m_stream;

  public:
    WorkItem(TCPStream* stream) : m_stream(stream) {}
    ~WorkItem() { delete m_stream; }

    TCPStream* getStream() { return m_stream; }
};

class ConnectionHandler : public Thread
{
    ColaTrabajo<WorkItem*>& m_queue;

  public:
    ConnectionHandler(ColaTrabajo<WorkItem*>& queue) : m_queue(queue) {}

    void* run() {
        // Remove 1 item at a time and process it. Blocks if no items are
        // available to process.
        for (int i = 0;; i++) {
            printf("thread %lu, loop %d - waiting for item...\n",
                   (long unsigned int)self(), i);
            WorkItem* item = m_queue.remove();
            printf("thread %lu, loop %d - got one item\n",
                   (long unsigned int)self(), i);
            TCPStream* stream = item->getStream();

            // Echo messages back the client until the connection is
            // closed
            char input[256];
            int len;
            while ((len = stream->receive(input, sizeof(input)-1)) > 0 ){
                input[len] = NULL;
                stream->send(input, len);
                printf("thread %lu, echoed '%s' back to the client\n",
                       (long unsigned int)self(), input);
            }
            delete item;
        }

        // Should never get here
        return NULL;
    }
};

int main(int argc, char** argv)
{
    // Process command line arguments
    if ( argc < 3 || argc > 4 ) {
        printf("Uso: %s <JSON Mapa> <Puerto> [<IP Opcional>]\n", argv[0]);
        exit(-1);
    }
    int workers = 2; //Threads que levantan mensajes de la cola.
    int port = atoi(argv[2]); //Puerto en el que escucha alas conexiones.
    string ip; //IP en el que escucha.
    if (argc == 4) {
        ip = argv[3];
    }

    // Create the queue and consumer (worker) threads
    ColaTrabajo<WorkItem*>  queue;
    for (int i = 0; i < workers; i++) {
        ConnectionHandler* handler = new ConnectionHandler(queue);
        if (!handler) {
            printf("Could not create ConnectionHandler %d\n", i);
            exit(1);
        }
        handler->start();
    }

    // Create an acceptor then start listening for connections
    WorkItem* item;
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

    // Add a work item to the queue for each connection
    while (1) {
        TCPStream* connection = connectionAcceptor->accept();
        if (!connection) {
            printf("Could not accept a connection\n");
            continue;
        }
        item = new WorkItem(connection);
        if (!item) {
            printf("Could not create work item a connection\n");
            continue;
        }
        queue.add(item);
    }

    // Should never get here
    exit(0);
}

