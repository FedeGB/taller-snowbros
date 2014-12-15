/*
 * ParserMensajes.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: rodrizapico
 */

#include "ParserMensajes.h"

ParserMensajes::ParserMensajes() {
	// TODO Auto-generated constructor stub

}

ParserMensajes::~ParserMensajes() {
	// TODO Auto-generated destructor stub
}

// Interpreta el mensaje y lo descompone en sus partes.
MensajeParseado ParserMensajes::parsearTexto(std::string mensaje){

	MensajeParseado parseado;

	// Separa el codigo de mensaje del resto.
	std::vector<std::string> buff;
	split(buff, mensaje, SEPARADORCAMPOS, no_empties);

	// Determina el tipo.
	parseado.tipo = (codigo_protocolo_t) atoi(buff[0].c_str());

	// Determina los datos adicionales, si los hubiera.
	if (buff.size() > 1) parseado.datos = buff[1];

	return parseado;
}
