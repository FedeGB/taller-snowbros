/*
 * ParserMensajes.h
 *
 *  Created on: Dec 7, 2014
 *      Author: rodrizapico
 */

#ifndef PARSERMENSAJES_H_
#define PARSERMENSAJES_H_

#include "MensajeParseado.h"
#include "../utiles/tipos.h"

class ParserMensajes {
public:
	ParserMensajes();
	virtual ~ParserMensajes();

	// Interpreta el mensaje y lo descompone en sus partes.
	MensajeParseado parsearTexto(std::string mensaje);
};

#endif /* PARSERMENSAJES_H_ */
