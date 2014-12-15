/*
 * Notificador.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef NOTIFICADOR_H_
#define NOTIFICADOR_H_

#include "ServicioNotificador.h"
#include <list>

class Notificador: public ServicioNotificador {
public:

	// Construye un objeto notificador.
	Notificador();

	// Destruye el notificador.
	virtual ~Notificador();

	// Agrega a 'objeto' a la lista de objetos a notificar.
	virtual void subscribirANotificaciones(Notificable * objeto);

	// Quita a 'objeto' de la lista de objetos a notificar.
	virtual void finalizarNotificaciones(Notificable * objeto);

	// Notifica a los modulos que correspondan que sucedio un evento del tipo 'notificacion'.
	virtual void enviarNotificaciones(tipo_notificacion_t notificacion);

	// Notifica a los modulos que correspondan que sucedio un evento del tipo 'notificacion'.
	void enviarNotificaciones(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto);

private:

	std::list<Notificable*> listaSubscriptos;
};

#endif /* NOTIFICADOR_H_ */
