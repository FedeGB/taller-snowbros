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
	ID = 0;
}

// Destruye la representacion del modelo de juego.
ModeloJuego::~ModeloJuego(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ModeloJuego::notificar(tipo_notificacion_t notificacion){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ModeloJuego::notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto){

}

// Inicializa el modelo del juego.
void ModeloJuego::inicializar(){

	// El modelo desea ser notificado cuando se cree o destruya un personaje.
	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);
}

// Calcula que PJ sera atacado por el enemigo actual.
// Actualmente solo tiene en cuenta la distancia para determinar el objetivo.
Personaje * ModeloJuego::obtenerPJAAtacar(Enemigo * enemigo){

	Personaje * PJ = NULL;
	float32 menorModuloCuadrado = INFINITY;

	Vector2D posicionEnemigo = enemigo->espacioOcupado->calcularBaricentro();

	for(std::map<std::string,Personaje*>::iterator it = personajes.begin(); it != personajes.end(); it++){

		// Analiza si debe saltear al PJ.
		Personaje * PJActual = (*it).second;
		if( PJActual == NULL) continue;
		if( PJActual->salud <= 0) continue;

		// Calcula el modulo de la distancia entre el PJ y el enemigo.
		Vector2D posicionPJ = PJActual->espacioOcupado->calcularBaricentro();
		Vector2D vectorDistancia = posicionEnemigo - posicionPJ;
		float moduloCuadrado = vectorDistancia.moduloCuadrado();

		// Analiza si es el mas cercano hasta ahora.
		// TODO: area de vision hardcodeada.
		float RADIOVISIONALCUADRADO = 1600; // vision de 40 unidades.
		if (moduloCuadrado < menorModuloCuadrado && moduloCuadrado < RADIOVISIONALCUADRADO){
			menorModuloCuadrado = moduloCuadrado;
			PJ = PJActual;
		}
	}

	return PJ;
}

// Actualiza el modelo del juego.
void ModeloJuego::actualizar(int cantidadOnline){

	// Actualiza objetos.
	for(std::map<std::string,ObjetoModelo*>::iterator it = objetos.begin(); it != objetos.end(); it++){
		if((*it).second == NULL) continue;
		(*it).second->actualizar();

		if( (*it).second->paraDestruir && (*it).second->reconocerDestruccion >= 10 * cantidadOnline ){
			(*it).second->limpiar();
			delete (*it).second;
			(*it).second = NULL;
		}
	}

	// Actualiza personajes.
	for(std::map<std::string,Personaje*>::iterator it = personajes.begin(); it != personajes.end(); it++){
		if((*it).second == NULL) continue;
		(*it).second->actualizar();

		// Si el personaje perdio todas las vidas, lo debo destruir.
		if((*it).second->salud < 1) (*it).second->paraDestruir = true;
		if( (*it).second->paraDestruir && (*it).second->reconocerDestruccion >= 10 * cantidadOnline ){
			(*it).second->limpiar();
			delete (*it).second;
			(*it).second = NULL;
		}
	}

	// Actualiza enemigos.
	for(std::map<std::string,Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); it++){
		if((*it).second == NULL) continue;


		Personaje * PJ = obtenerPJAAtacar((*it).second);
		(*it).second->actualizar(PJ);

		if( (*it).second->paraDestruir && (*it).second->reconocerDestruccion >= 10 * cantidadOnline ){
			(*it).second->limpiar();
			delete (*it).second;
			(*it).second = NULL;
		}
	}

}

// Destruye el modelo del juego para asegurar un correcto finalizado
// de los modulos involucrados.
void ModeloJuego::limpiar(){

	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);

	for(std::map<std::string,ObjetoModelo*>::iterator it = objetos.begin(); it != objetos.end(); it++){
		if((*it).second == NULL) continue;
		(*it).second->limpiar();
		delete (*it).second;
		(*it).second = NULL;
	}

	for(std::map<std::string,Personaje*>::iterator it = personajes.begin(); it != personajes.end(); it++){
		if((*it).second == NULL) continue;
		(*it).second->limpiar();
		delete (*it).second;
		(*it).second = NULL;
	}

	for(std::map<std::string,Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); it++){
		if((*it).second == NULL) continue;
		(*it).second->limpiar();
		delete (*it).second;
		(*it).second = NULL;
	}
}

// Verifique que queden enemigos vivos en el modelo.
bool ModeloJuego::quedanEnemigos(){

	for(std::map<std::string,Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); it++){
		if((*it).second != NULL) return true;
	}

	return false;
}

// Verifica la existencia de un objeto en el modelo.
bool ModeloJuego::existeObjeto(std::string ID){
	return ( objetos.count(ID) == 1 ? true : false );
}

// Agrega un objeto al modelo.
void ModeloJuego::agregarObjeto (ObjetoModelo * objeto){
	ID++;
	objeto->ID = SSTR(ID);
	objetos[SSTR(ID)] = objeto;
}

// Agrega un personaje al modelo.
void ModeloJuego::agregarPersonaje (Personaje * personaje){
	ID++;
	personaje->ID = SSTR(ID);
	personajes[SSTR(ID)] = personaje;
}

// Agrega un enemigo al modelo.
void ModeloJuego::agregarEnemigo (Enemigo * enemigo){
	ID++;
	enemigo->ID = SSTR(ID);
	enemigos[SSTR(ID)] = enemigo;
}

// Elimina un objeto del modelo.
void ModeloJuego::eliminarObjeto (std::string ID){
	objetos[ID]->limpiar();
	delete objetos[ID];
	objetos.erase(ID);
}

// Elimina un personaje del modelo.
void ModeloJuego::eliminarPersonaje (std::string ID){
	personajes[ID]->limpiar();
	delete personajes[ID];
	personajes.erase(ID);
}

// Elimina un enemigo del modelo.
void ModeloJuego::eliminarEnemigo (std::string ID){
	enemigos[ID]->limpiar();
	delete enemigos[ID];
	enemigos.erase(ID);
}
