/*
 * Usuario.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: rodrizapico
 */

#include "Usuario.h"

Usuario::Usuario() {
	online = true;
	inicializado = false;
	PJ = NULL;
	sonidoPJ = NULL;
}

Usuario::~Usuario() {
	// TODO Auto-generated destructor stub
}

// Agrega una nueva notificacion por parte del handler de conexion para
// ser recuperada por el handler de la simulacion B2D.
// IDEvento: ID del evento que se esta notificando.
void Usuario::encolarNotificacion(teclas_t IDEvento){

	WorkItem * item = new WorkItem;
	item->type = KEYEVENT;
	item->key = IDEvento;

	colaNotificaciones.add(item);
}

// Recupera una notificacion dejada por el handler de conexion, para tratarla.
// Debe ser usada solo por el handler de simulacion B2D.
// return: el WorkItem a ser procesado, o NULL cuando no quedan mas notificaciones
// a procesar.
WorkItem * Usuario::desencolarNotificacion(){
	return colaNotificaciones.nonLockingRemove();
}

// Procesa todas las notificaciones en la cola de notificaciones. Es llamada
// por el handler de simulacion B2D.
void Usuario::procesarNotificaciones(){
	WorkItem * item;

	while ( ( item = desencolarNotificacion() ) != NULL ){

		switch(item->key){
		case SOLTOSPACE:
			PJ->eventoSoltoSpace();
			break;
		case SPACE:
			PJ->eventoSpace();
			break;
		case ARRIBA:
			PJ->eventoArriba();
			break;
		case IZQUIERDA:
			PJ->eventoIzquierda();
			break;
		case DERECHA:
			PJ->eventoDerecha();
			break;
		case SOLTOARRIBA:
			PJ->eventoSoltoArriba();
			break;
		case SOLTOIZQUIERDA:
			PJ->eventoSoltoIzquierda();
			break;
		case SOLTODERECHA:
			PJ->eventoSoltoDerecha();
			break;
		case ZOOMIN:
			PJ->camera->eventoZoomIn();
			break;
		case ZOOMOUT:
			PJ->camera->eventoZoomOut();
			break;
		}
		delete(item);
	}


}


// Devuelve una representacion serializada de lo que ve el usuario en su camara,
// para poder ser rendereada en el cliente.
std::string Usuario::obtenerPantallaSerializada(){

	std::string pantallaSerializada;
	pantallaSerializada.clear();

//	std::cout << "obteniendo pantalla serializada" << std::endl;

	// Bloquea la lista para evitar modificaciones mientras se serializa.
	listaVisibles.lock();

	// Envia los elementos que deben ser renderizados.
	for(ThreadSafeList<WorldItem*>::iterator it=listaVisibles.begin(); it != listaVisibles.end(); ++it){
		// TODO: sacar el % hardcodeado.
		pantallaSerializada += "%";
		pantallaSerializada += (*it)->serializar();
	}

	listaVisibles.unlock();

	if( sonidoPJ->sonido != VACIO ){
		//printf("sonido: %s\n", sonidoPJ->sonido.c_str());
		pantallaSerializada += "%";
		pantallaSerializada += sonidoPJ->serializar();
		//std::cout << "pantalla: " << sonidoPJ->serializar() << '\n';
		sonidoPJ->sonido = VACIO;
	}

	pantallaSerializada += "%USERNAME ";
	pantallaSerializada += username;
	return pantallaSerializada;
}

// Notifica a los threads que esten esperando por este usuario, para que
// continuen ejecutando.
void Usuario::enviarSenial(){
	c.signal();
}

// El thread llamante espera hasta que se notifique que puede continuar
// ejecutando, mediante una llamada a enviarSenial().
void Usuario::esperarSenial(){
	c.wait();
}

// Inicializa el PJ asociado a este usuario, con su correspondiente camara.
void Usuario::inicializarPJ(b2World * worldB2D, std::string configFile){
	Inicializador inicializador;
	PJ = inicializador.pjInit(&worldB2D, listaVisibles, configFile);
	if (!PJ){
		// TODO: Error handling.
		std::cout << "hubo un error al crear el PJ" << std::endl;
	}
	sonidoPJ = new Sonido();
	inicializado = true;
}

// Actualiza el estado del PJ y su camara asociada.
void Usuario::actualizarPJ(){
	PJ->update(sonidoPJ);
}

void Usuario::setOnline(bool estado){
	this->online= estado;
	this->PJ->online= estado;
}
