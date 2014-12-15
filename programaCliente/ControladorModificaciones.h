/*
 * ControladorModificaciones.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef CONTROLADORMODIFICACIONES_H_
#define CONTROLADORMODIFICACIONES_H_

#include <list>
#include <pthread.h>
#include "interfaces/Notificable.h"
#include "controladorJuego/ObjetoJuego.h"

class ControladorModificaciones: public Notificable {
public:

	// Crea un controlador de modificaciones.
	// El mismo sirve como interfaz de comunicacion entre el thread que se comunica con
	// el servidor y el de rendereo.
	// NOTA: el objeto es, forzosamente, thread safe.
	ControladorModificaciones();

	// Destruye el controlador de modificaciones.
	virtual ~ControladorModificaciones();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Agrega una modificacion a aplicar al juego.
	void agregarModificacion(ObjetoJuego * mod);

	// Obtiene la proxima modificacion a aplicar al juego.
	ObjetoJuego * obtenerModificacion();

	// Obtiene la proxima modificacion a aplicar al juego
	// NOTA: No bloquea.
	ObjetoJuego * obtenerModificacionSinBloquear();

	// Determina si aun quedan modificaciones para resolver.
	bool quedanModificaciones();

private:

	std::list<ObjetoJuego*> modificaciones;

	//	Variables encargadas de hacer thread safe al controlador.
	pthread_mutex_t m_mutex;
    pthread_cond_t m_condv;

};

#endif /* CONTROLADORMODIFICACIONES_H_ */
