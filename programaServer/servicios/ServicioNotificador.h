/*
 * ServicioNotificador.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef SERVICIONOTIFICADOR_H_
#define SERVICIONOTIFICADOR_H_

#include "../interfaces/Notificable.h"

class ServicioNotificador {
public:

	virtual ~ServicioNotificador(){};

	// Agrega a 'objeto' a la lista de objetos a notificar.
	virtual void subscribirANotificaciones(Notificable * objeto) = 0;

	// Quita a 'objeto' de la lista de objetos a notificar.
	virtual void finalizarNotificaciones(Notificable * objeto) = 0;

	// Notifica a los modulos que correspondan que sucedio un evento del tipo 'notificacion'.
	virtual void enviarNotificaciones(tipo_notificacion_t notificacion) = 0;

	// Notifica a los modulos que correspondan que sucedio un evento del tipo 'notificacion'.
	virtual void enviarNotificaciones(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto) = 0;

};

#endif /* SERVICIONOTIFICADOR_H_ */
