/*
 * serverMain.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: matias
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string>
#include "../Threads/Thread.h"
#include "ColaTrabajo.h"
#include "TCPAcceptor.h"
#include "ConnectionHandler.h"
#include "Message.h"
#include "WorldHandler.h"
#include <list>
#include "DispatchThread.h"
#include "ctype.h"

int isNumber(char* string);
bool file_exist(const string f);
bool ipValid(string ip);

int main(int argc, char** argv)
{
    // Process command line arguments
    int opt, cflag, pflag, iflag, port;
    opt = cflag = pflag = iflag = port = 0;
    std::string path (" "); // path al config
    std::string ip (""); // IP en el que escucha.

    while( (opt = getopt(argc, argv, "c:p:i:")) != -1 ) {
       	switch(opt) {
       	case 'c':
       		if ( argc < 5 || argc > 7 ) {
       			printf("Uso: %s -c <JSON Mapa> -p <Puerto> -i [<IP Opcional>]\n", argv[0]);
       			exit(-1);
       		}

       		cflag = 1;
       		path = std::string(optarg);
       		break;
       	case 'p':
       		if ( argc < 3 || argc > 7 ) {
       	        printf("Uso: %s -c <JSON Mapa> -p <Puerto> -i [<IP Opcional>]\n", argv[0]);
       	        exit(-1);
       	    }
       		if(!isNumber(optarg)) {
       			printf("El puerto %s especificado debe ser un numero\n", optarg);
       			exit(-1);
       		}
       		pflag = 1;
       		port = atoi(optarg); // Puerto en el que escucha a las conexiones.
       		break;
       	case 'i':
       		if ( argc < 5 || argc > 7 ) {
       	        printf("Uso: %s -c <JSON Mapa> -p <Puerto> -i [<IP Opcional>]\n", argv[0]);
       	        exit(-1);
       	    }
       		iflag = 1;
       		ip = std::string(optarg);
       		break;
       	case '?':
       		if(optopt == 'c') {
       			printf("Al parametro -c le falta el path\n");
       		}
       		else if(optopt == 'p') {
       			printf("Al parametro -p le falta especificar el puerto\n");
       		}
       		else if(optopt == 'i') {
       			printf("Al parametro -i le faltaria especificar una ip, si no quiere especificar una, no utilice el argumento -i\n");
       		}
       		else {
       			printf("Parametro -%c no reconocido\n", optopt);
       		}
       		exit(-1);
       	default:
       		printf("Error no esperado en el procesamiento de comandos\n");
       		exit(-1);
       	}
    }

    if (!cflag) {
     	printf("No se especifico archivo de configuracion\n");
       	// Seteando archivo default
       	path = "default.conf";
    }
    if (!file_exist(path)){
        printf("no existe el archivo: ",path," de configuracion, el programa terminara\n");
        return -1;
    }

    if (!pflag) {
       printf("No se especifico puerto con el comando -p\n");
       return -1;
    }

    if (iflag) {
    	if(!ipValid(ip)){
    		printf("la ip ingresada es invalida\n");
    		ip="";
    	}
    }

    //TODO: Cargar el json y el world.

    // Creo la cola de mensajes recibidos para procesar.
    ColaTrabajo<Message*>  queue;
    //Creo la cola de mensajes a enviar y la lista de conexiones
    ColaTrabajo<Message*> dispatchQueue;
    list<ConnectionHandler*> connectionList;

    //Creo el thread que despacha mensajes
    DispatchThread* dispatcher = new DispatchThread(dispatchQueue, connectionList);
    if(!dispatcher){
    	printf("Error creando el dispatch thread. \n");
    	exit(1);
    }
    dispatcher->start();

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
        }else{
        	connectionList.push_back(handler);
        	handler->start();
        }

    }

    // Should never get here
    exit(0);
}

int isNumber(char* string) {
	std::string var;
	if(!string) {
		return 0;
	} else {
		var  = string;
	}
	for(unsigned int i = 0; i < var.length(); i++) {
		if(!isdigit(var[i])) {
			return 0;
		}
	}
	return 1;
}

bool file_exists(const string  f){
    ifstream file;
    file.open(f.c_str());
    if(file.fail())
        return false;
    file.close();
    return true;
}

bool ipValid(string ip){
	if(ip.length()<8 || ip.length()>16)
		return false;
	string token ,temp=ip;
	while(token != ip){
		token = temp.substr(0,temp.find_first_of("."));
		temp = temp.substr(temp.find_first_of(".") + 1);
		int num;
		num = atoi( temp.c_str() );
		if (temp == 0 ){
			return false;
		}
	}
	return true;
}
