/*
 * Servidor.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#include "Servidor.h"
#include "servicios/Fabrica.h"

// Instancia principal del programa.
Servidor::Servidor(){
	fabrica = NULL;
	notificador = NULL;
	informacion = NULL;
	inicializador = NULL;
	aceptorConexiones = NULL;
	controlador = NULL;
	salir = false;
}

Servidor::~Servidor(){

}


// Ejecuta el programa.
void Servidor::ejecutar(int argc, char** argv){

	// Inicializa aquello que sea necesario para la ejecucion del servidor.
	if (inicializar(argc, argv) == false) salir = true;

	// Creo el thread encargado de la simulacion.
	WorldHandler * simulacion = new WorldHandler(controlador);
	if (!simulacion) {
		printf("Could not create WorldHandler.\n");
	}else simulacion->start();

	// Loop eterno aceptando conexiones.
	while (!salir){

		TCPStream* connection = aceptorConexiones->accept();
		if (!connection) {
			printf("Could not accept a connection\n");
			continue;
		}

		ConnectionHandler * handler = new ConnectionHandler(connection, controlador);
		if (!handler) {
			printf("Could not create ConnectionHandler.\n");
		}else handler->start();
	}

	limpiar();
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void Servidor::notificar(tipo_notificacion_t notificacion){
	if (notificacion == CERRARPROGRAMA) salir = true;
}

// Carga los parametros necesarios para la ejecucion del servidor, e inicializa los
// modulos que necesiten inicializacion.
bool Servidor::inicializar(int argc, char** argv){

	// Inicializo el notificador y lo establezco como proveedor de notificaciones.
	notificador = new Notificador();
	LocalizadorDeServicios::proveer(notificador);
	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	// Inicializo el servicio de informacion y lo establezco como proveedor de informacion.
	informacion = new ServicioInformacion();
	LocalizadorDeServicios::proveer(informacion);

	// Valida los parametros de entrada.
	inicializador = new Inicializador();
	if (!inicializador->validarParametros(argc, argv)) return false;

	// Recupera la IP y el puerto.
    std::string ip = LocalizadorDeServicios::obtenerInformacionPublica()->IP;
    int puerto = LocalizadorDeServicios::obtenerInformacionPublica()->puerto;

    // Crea un aceptor de conexiones.
    if (ip.length() > 0) {
    	aceptorConexiones = new TCPAcceptor(puerto, (char*)ip.c_str());
    }
    else {
    	aceptorConexiones = new TCPAcceptor(puerto);
    }

    if (!aceptorConexiones || aceptorConexiones->start() != 0) {
        printf("Could not create an connection acceptor\n");
        return false;
    }

    controlador = new ControladorJuego;
    controlador->inicializar();

	// Inicializo el servicio de fabrica.
	fabrica = new Fabrica(controlador);
	LocalizadorDeServicios::proveer(fabrica);

	return true;
}

// Libera memoria y realiza las acciones necesarias para cerrar en un estado valido.
void Servidor::limpiar(){

	delete notificador;
	delete informacion;
	delete inicializador;
	delete aceptorConexiones;
	controlador->limpiar();
	delete controlador;
}

