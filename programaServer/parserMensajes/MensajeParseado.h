/*
 * MensajeParseado.h
 *
 *  Created on: Dec 7, 2014
 *      Author: rodrizapico
 */

#ifndef MENSAJEPARSEADO_H_
#define MENSAJEPARSEADO_H_

#include <string>
#include "protocoloServidorCliente.h"

class MensajeParseado {
public:
	MensajeParseado();
	virtual ~MensajeParseado();

	// Tipo de mensaje recibido.
	codigo_protocolo_t tipo;

	// Datos adicionales, si los hubiera.
	std::string datos;
};

#endif /* MENSAJEPARSEADO_H_ */
