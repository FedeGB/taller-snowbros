/*
 * Notificable.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef NOTIFICABLE_H_
#define NOTIFICABLE_H_

#include "EnviadorNotificaciones.h"

enum tipo_notificacion_t{
	BOTONCLICKEADO,
	CAJADETEXTOLLENA,
	CERRARPROGRAMA,
	PERSONAJECREADO,
	PERSONAJEDESTRUIDO,
	ACERCARCAMARA,
	ALEJARCAMARA,
	MOVERPERSONAJESALTO,
	MOVERPERSONAJEABAJO,
	MOVERPERSONAJEIZQUIERDA,
	MOVERPERSONAJEDERECHA,
	DETENERMOVIMIENTOPERSONAJE,
	DETENERMOVIMIENTOPERSONAJESALTO,
	DETENERMOVIMIENTOPERSONAJEATAQUE,
	MOVERPERSONAJEATAQUE,
	COMIENZODEJUEGO,
	FINDEJUEGO,
};

class Notificable {
public:

	virtual ~Notificable(){};

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion) = 0;

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto){};

};

#endif /* NOTIFICABLE_H_ */
