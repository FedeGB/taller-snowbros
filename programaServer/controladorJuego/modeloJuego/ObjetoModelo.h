/*
 * ObjetoModelo.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef OBJETOMODELO_H_
#define OBJETOMODELO_H_

#include <Box2D/Box2D.h>
#include <string>
#include <iostream>
#include "../ObjetoJuego.h"
#include "../../parser/parser.h"
#include "../../matematica/FiguraGeometrica.h"
#include "../../parserMensajes/protocoloServidorCliente.h"

class SerVivo;
class Personaje;
class EnemigoEstandar;
class EnemigoFuego;
class BolaDeNieve;
class BolaDeFuego;
class Camara;

class ObjetoModelo: public ObjetoJuego {
public:
	virtual ~ObjetoModelo(){};

	// Crea un elemento nuevo del modelo en base a los datos serializados.
	static ObjetoModelo * deserializar(std::string serializado);

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar() = 0;

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion){};

	// Inicializa al objeto.
	virtual void inicializar();

	// Elimina lo que sea necesario.
	virtual void limpiar();

	// Actualiza la informacion del objeto para poder dibujarlo.
	virtual void actualizar();

	// Describe las posibles orientaciones del objeto.
	enum orientacion_t{
		IZQUIERDA,
		DERECHA,
	};

	std::string ID;
	bool paraDestruir;
	int reconocerDestruccion;
	bool modificado;
	b2Body * cuerpoB2D;
	FiguraGeometrica * espacioOcupado;
	float rotacion;
	orientacion_t orientacion;
	bool cayoPorAgujero;
	int acumuladorCaida;
};

#endif /* OBJETOMODELO_H_ */
