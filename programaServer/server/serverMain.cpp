/*
 * serverMain.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: matias
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../threads/Thread.h"
#include "../threads/ThreadSafeList.h"
#include "../threads/ConditionVariable.h"
#include "../threads/ColaTrabajo.h"
#include "TCPAcceptor.h"
#include "ConnectionHandler.h"
#include "WorkItem.h"
#include "WorldHandler.h"
#include "../modelo/WorldItem.h"
#include "../ControladorUsuarios.h"
//#include "ControladorEnemigos.h"

int isNumber(const char* string);
bool file_exist( string f);
bool ipValid(string ip);
bool isValidIPNumber(string token);
bool isValidPort(int puerto);

int main(int argc, char** argv){


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
       	path = "defaultConfig.json";
    }
    if (!file_exist(path)){
      //  printf("no existe el archivo: ",path," de configuracion, el programa terminara\n");
        return -1;
    }

    if (!pflag) {
       printf("No se especifico puerto con el comando -p\n");
       return -1;
    } else {
    	if(!isValidPort(port)) {
    		printf("El puerto %d no es valido, ingrese un puerto entre 1024 y 49151\n", port);
    		return -1;
    	}
    }

    if (iflag) {
    	if(!ipValid(ip)){
    		printf("la ip ingresada es invalida\n");
    		return -1;
    	}
    }

    // Creo el controlador de usuarios. Este contiene toda la informacion
    // necesaria para la comunicacion entre el handler de simulacion y el de
    // conexion.
    fstream fConfig;
	fConfig.open(path.c_str(), ios_base::in);
	std::string newStr((std::istreambuf_iterator<char>(fConfig)),
				std::istreambuf_iterator<char>());
	fConfig.close();

    int maxplayer=get_node("maxplayer","escenario", newStr,4);
    ControladorUsuarios controlador;
    ControladorEnemigos enemigos;
    controlador.setConnectionLimit(maxplayer);
    //Creo el handler de simulacion.
    WorldHandler* world = new WorldHandler(controlador, enemigos, path);
    if (!world){
    	printf("No se pudo crear el connection handler.\n");
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

    //ConnectionHandler * connections[4];

    //Loop infinito esperando conexiones.
    while (true) {
        TCPStream* connection = connectionAcceptor->accept();
        if (!connection) {
            printf("Could not accept a connection\n");
            continue;
        }

        ConnectionHandler* handler = new ConnectionHandler(controlador, connection);
        if (!handler) {
            printf("Could not create ConnectionHandler.\n");
            //exit(1);
        }else handler->start();
    }

    // Espera que finalicen todas las conexiones antes de finalizar.
    //for (std::list<Thread*>::iterator it = threadList.begin(); it != threadList.end(); it++)
    //	(*it)->join();

    exit(0);
}


int isNumber(const char* string) {
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

bool file_exist(const string  f){
    ifstream file;
    file.open(f.c_str());
    if(file.fail())
        return false;
    file.close();
    return true;
}

bool ipValid(string ip){
	if(ip == "localhost") return true;
	if(ip.length()<8 || ip.length()>16)
		return false;
	string token ,temp=ip;
	while (token != temp){
		token = temp.substr(0,temp.find_first_of("."));
		temp = temp.substr(temp.find_first_of(".") + 1);
		if(!isValidIPNumber(token)) {
			return false;
		}
	}
	return true;
}

bool isValidIPNumber(string token) {
	if(isNumber(token.c_str())) {
		int number = atoi(token.c_str());
		if (number < 0 || number > 255) {
			return false;
		}
	} else {
		return false;
	}
	return true;
}

bool isValidPort(int puerto) {
	if(puerto < 1024 || puerto > 49151) {
		return false;
	}
	return true;
}
