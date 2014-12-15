/*
 * Notificador.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "Notificador.h"

// Construye un objeto notificador.
Notificador::Notificador(){

}

// Destruye el notificador.
Notificador::~Notificador(){

}

// Agrega a 'objeto' a la lista de objetos a notificar.
void Notificador::subscribirANotificaciones(Notificable * objeto){
	listaSubscriptos.push_back(objeto);
}

// Quita a 'objeto' de la lista de objetos a notificar.
void Notificador::finalizarNotificaciones(Notificable * objeto){
	listaSubscriptos.remove(objeto);

}

// Notifica a los modulos que correspondan que sucedio un evento del tipo 'notificacion'.
void Notificador::enviarNotificaciones(tipo_notificacion_t notificacion){

	// Itera sobre todos los subscriptos, notificandolos.
	for(std::list<Notificable*>::iterator it = listaSubscriptos.begin(); it != listaSubscriptos.end(); it++)
		(*it)->notificar(notificacion);
}

// Notifica a los modulos que correspondan que sucedio un evento del tipo 'notificacion'.
void Notificador::enviarNotificaciones(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto){

	// Itera sobre todos los subscriptos, notificandolos.
	for(std::list<Notificable*>::iterator it = listaSubscriptos.begin(); it != listaSubscriptos.end(); it++)
		(*it)->notificar(notificacion, objeto);
}
