/*
 * ServicioPosicionador.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef SERVICIOPOSICIONADOR_H_
#define SERVICIOPOSICIONADOR_H_

#include "../interfaces/Notificable.h"
#include "../interfaces/Posicionable.h"

class ServicioPosicionador: public Notificable {
public:
	virtual ~ServicioPosicionador(){}

	enum tipo_t{
		NOMBREJUGADOR,
		PUNTAJEJUGADOR,
		VIDASJUGADOR,
		CORAZONJUGADOR,
	};

	struct tipo_objeto_t{
		tipo_t tipo;
		int numero;
	};

	// Posiciona un objeto en la region de pantalla donde debe ser dibujado.
	// La region es determinada por el parametro 'tipo'.
	virtual void posicionar(Posicionable * objeto, tipo_objeto_t tipo) = 0;
};

#endif /* SERVICIOPOSICIONADOR_H_ */
