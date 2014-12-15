/*
 * ControladorModificaciones.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "ControladorModificaciones.h"

// Crea un controlador de modificaciones.
// El mismo sirve como interfaz de comunicacion entre el thread que se comunica con
// el servidor y el de rendereo.
// NOTA: el objeto es, forzosamente, thread safe.
ControladorModificaciones::ControladorModificaciones(){
	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_condv, NULL);
}

// Destruye el controlador de modificaciones.
ControladorModificaciones::~ControladorModificaciones(){
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_condv);
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ControladorModificaciones::notificar(tipo_notificacion_t notificacion){

}

// Agrega una modificacion al modelo del juego.
void ControladorModificaciones::agregarModificacion(ObjetoJuego * mod){
    pthread_mutex_lock(&m_mutex);
	modificaciones.push_back(mod);
    pthread_cond_signal(&m_condv);
    pthread_mutex_unlock(&m_mutex);
}

// Obtiene la proxima modificacion a aplicar al modelo del juego.
ObjetoJuego * ControladorModificaciones::obtenerModificacion(){
    pthread_mutex_lock(&m_mutex);
    while (modificaciones.size() == 0) {
        pthread_cond_wait(&m_condv, &m_mutex);
    }
    ObjetoJuego * mod = modificaciones.front();
	modificaciones.pop_front();
    pthread_mutex_unlock(&m_mutex);
	return mod;
}

// Obtiene la proxima modificacion a aplicar al modelo del juego.
// NOTA: No bloquea.
ObjetoJuego * ControladorModificaciones::obtenerModificacionSinBloquear(){
    pthread_mutex_lock(&m_mutex);
    ObjetoJuego * mod = NULL;
    if(modificaciones.size() != 0){
    	mod = modificaciones.front();
    	modificaciones.pop_front();
    }
    pthread_mutex_unlock(&m_mutex);
    return mod;
}

// Determina si aun quedan modificaciones para resolver.
bool ControladorModificaciones::quedanModificaciones(){
    pthread_mutex_lock(&m_mutex);
    bool quedanModificaciones = modificaciones.empty();
    pthread_mutex_unlock(&m_mutex);
	return quedanModificaciones;
}
