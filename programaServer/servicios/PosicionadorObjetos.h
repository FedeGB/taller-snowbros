/*
 * PosicionadorObjetos.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef POSICIONADOROBJETOS_H_
#define POSICIONADOROBJETOS_H_

#include "ServicioPosicionador.h"
#include "SDL2/SDL.h"

class PosicionadorObjetos: public ServicioPosicionador {
public:

	// Crea un objeto encargado de posicionr los elementos en pantalla.
	PosicionadorObjetos();

	// Destruye el posicionador.
	virtual ~PosicionadorObjetos();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Posiciona un objeto en la region de pantalla donde debe ser dibujado.
	// La region es determinada por el parametro 'tipo'.
	virtual void posicionar(Posicionable * objeto, tipo_objeto_t tipo);
};

#endif /* POSICIONADOROBJETOS_H_ */
