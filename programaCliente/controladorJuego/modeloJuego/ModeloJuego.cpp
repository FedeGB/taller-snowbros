/*
 * ModeloJuego.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "ModeloJuego.h"

#include "tiposDeObjeto/Personaje.h"

// Representacion del modelo del juego actual: mapa, posicion de los personajes,
// enemigos, obstaculos, poderes, etc.
ModeloJuego::ModeloJuego(){
	camara = NULL;
	fondo = NULL;
}

// Destruye la representacion del modelo de juego.
ModeloJuego::~ModeloJuego(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ModeloJuego::notificar(tipo_notificacion_t notificacion){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ModeloJuego::notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto){

	if (notificacion == PERSONAJECREADO){
		if ( ((Personaje*)objeto)->nombre == LocalizadorDeServicios::obtenerInformacionPublica()->nombreUsuario){
			camara->enfocar((Personaje*)objeto);
		}

	}

	// TODO: posiblemente hacer que enfoque en otro lado?
	// onda killcam. O que la puedas controlar con las flechas.
	// TODO: probar que la implementacion del todo anterior funcione.
	if (notificacion == PERSONAJEDESTRUIDO)	{
		if ( ((Personaje*)objeto)->nombre == LocalizadorDeServicios::obtenerInformacionPublica()->nombreUsuario){
			std::cout << "detecte la destruccion del personaje correspondiente al jugador" << std::endl;
			camara->desenfocar();
			camara->modoLibre();
		}
	}

}

// Inicializa el modelo del juego.
void ModeloJuego::inicializar(){

	// El modelo desea ser notificado cuando se cree o destruya un personaje.
	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	camara = new Camara();

	// TODO: sacar hardcodeo.
	camara->asignarDimensiones(28.125f, 25.0f);
	camara->asignarPosicion(0,0);
	camara->inicializar();
	camara->modoLibre();

	fondo = new Fondo(camara);
	fondo->inicializar();
}

// Actualiza el modelo del juego.
void ModeloJuego::actualizar(){
	camara->actualizar();
}

// Destruye el modelo del juego para asegurar un correcto finalizado
// de los modulos involucrados.
void ModeloJuego::limpiar(){

	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);

	camara->limpiar();
	delete camara;
	//fondo->limpiar();
	//delete fondo;

	for(std::map<std::string,ObjetoModelo*>::iterator it = objetos.begin(); it != objetos.end(); it++){
		if ((*it).second == NULL) continue;
		(*it).second->limpiar();
		delete (*it).second;
		(*it).second = NULL;
	}

	objetos.clear();
}

// Dibuja la seccion del modelo de juego visible en la pantalla.
void ModeloJuego::dibujar(){

	fondo->dibujar(camara);

	for(std::map<std::string,ObjetoModelo*>::iterator it = objetos.begin(); it != objetos.end(); it++){
		if ((*it).second == NULL) continue;
		(*it).second->dibujar(camara);
	}
}

// Verifica la existencia de un objeto en el modelo.
bool ModeloJuego::existeObjeto(std::string ID){
	return ( objetos.count(ID) == 1 ? true : false );
}

// Modifica un objeto en base a los cambios indicados en 'modificacion'.
void ModeloJuego::modificarObjeto(ObjetoModelo * modificacion){

	ObjetoModelo * objeto = objetos[modificacion->ID];
	modificacion->aplicarSobre(objeto);

	modificacion->limpiar();
	delete modificacion;
}

// Agrega un nuevo objeto al modelo.
void ModeloJuego::agregarObjeto(ObjetoModelo * modificacion){

	modificacion->inicializar();
	objetos[modificacion->ID] = modificacion;
}

// Quita un objeto del modelo.
void ModeloJuego::destruirObjeto(ObjetoModelo * modificacion){

	std::cout << "recibi para destruir un objeto: " << modificacion->ID << std::endl;

	ObjetoModelo * obj = objetos[modificacion->ID];
	obj->limpiar();
	objetos.erase(modificacion->ID);
	delete obj;

	modificacion->limpiar();
	delete modificacion;
}
