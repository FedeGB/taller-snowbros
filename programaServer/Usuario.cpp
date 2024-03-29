/*
 * Usuario.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: rodrizapico
 */

#include "Usuario.h"
#include "Inicializador.h"

Usuario::Usuario() {
	online = true;
	inicializado = false;
	PJ = NULL;
	sonidoPJ = NULL;
	numeroUsuario = 0;
	vida= 2;
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
		case a:
			eventoa();
			break;
		}
		delete(item);
	}


}


// Devuelve una representacion serializada de lo que ve el usuario en su camara,
// para poder ser rendereada en el cliente.
std::string Usuario::obtenerPantallaSerializada(){
	//this->vida=this->PJ->vida;
	std::string pantallaSerializada;
	pantallaSerializada.clear();

//	std::cout << "obteniendo pantalla serializada" << std::endl;

	// Bloquea la lista para evitar modificaciones mientras se serializa.
	listaVisibles.lock();

	// Envia los elementos que deben ser renderizados.
	while (!listaVisibles.empty()){
		//std::cout << "INIT: " << this->inicializado << std::endl;
		WorldItem * item = listaVisibles.front();
		listaVisibles.pop_front();
//		if(!item) continue;
		// LINEA MAGICA
		if( PJ->vida == 0 && (item->tipo==8 || !item->tipo) ) continue;
		//cout << "tipo:" << item->tipo << std::endl;
		if(!item) continue;
		pantallaSerializada += "%";
		pantallaSerializada += item->serializar();
		//std::cout << "SERIALIZO" << std::endl;
		if (item->tipo == METADATAFONDO) delete item;
		else if (item->tipo == METADATAHUD) delete item;
	}
	std::cout << "TERMINO SERIAL" << std::endl;

/*	for(ThreadSafeList<WorldItem*>::iterator it=listaVisibles.begin(); it != listaVisibles.end(); ++it){
		// TODO: sacar el % hardcodeado.
		pantallaSerializada += "%";
		pantallaSerializada += (*it)->serializar();
	}
*/
	listaVisibles.unlock();

	if( sonidoPJ->sonido != VACIO ){
		//printf("sonido: %s\n", sonidoPJ->sonido.c_str());
		pantallaSerializada += "%";
		pantallaSerializada += sonidoPJ->serializar();
		//std::cout << "pantalla: " << sonidoPJ->serializar() << '\n';
		sonidoPJ->sonido = VACIO;
	}

	//pantallaSerializada += "%USERNAME ";
	//pantallaSerializada += username;
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
	PJ = inicializador.pjInit(&worldB2D, listaVisibles, numeroUsuario, configFile);
	if (!PJ){
		std::cout << "hubo un error al crear el PJ" << std::endl;
	}
	sonidoPJ = new Sonido();
	inicializado = true;
	PJ->vida=this->vida;
}

// Actualiza el estado del PJ y su camara asociada.
void Usuario::actualizarPJ(){
	if(PJ!=NULL)
		PJ->update(sonidoPJ);
}

void Usuario::setOnline(bool estado){
	this->online= estado;
	if(PJ!=NULL)
		this->PJ->online= estado;
}

b2Vec2 Usuario::getPosition() {
	if(PJ!=NULL)
		return this->PJ->posicion;
	return b2Vec2(0,0);
}

bool Usuario::isPJAlive() {
	if(PJ!=NULL)
		return this->PJ->isAlive();
	else return false;
}

void Usuario::eventoa(){
	b2World * mundo = PJ->getMundo();

	Sorpresa* sorpresa;

	int tipo_sorpresa = rand() % 4;
	switch( tipo_sorpresa ){

	case 0: sorpresa= new SorpresaVida(); break;
	case 1: sorpresa= new SorpresaCorrer(); break;
	case 2: sorpresa= new SorpresaNieveMasLejos(); break;
	case 3: sorpresa= new SorpresaNieveMasPotente(); break;
	}

	sorpresa->agregarAMundo(10, 10, mundo);
}

float Usuario::getLives(){
	if(PJ!=NULL)
		return this->PJ->vida;
	return 2;
}

// Informa el resultado de la partida actual. Ademas, inicia el protocolo para mantenerlos
// conectados a una nueva partida, o desconectarlos en caso que no quieran jugar nuevamente.
void Usuario::notificarFinDePartida(resultado_t resultado){

}

void Usuario::DeletePj(){
	if(PJ!=NULL)
		this->PJ->setDelete();
	this->PJ=NULL;
}

long int Usuario::getPuntaje() {
	if(PJ!=NULL)
		return PJ->getPuntaje();
	return 0;
}
