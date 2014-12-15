/*
 * ObjetoModelo.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef OBJETOMODELO_H_
#define OBJETOMODELO_H_

#include <string>
#include <iostream>
#include "../ObjetoJuego.h"
#include "../../matematica/FiguraGeometrica.h"
#include "../../vista/Textura.h"
#include "../../parserMensajes/protocoloServidorCliente.h"

class SerVivo;
class Personaje;
class Enemigo;
class EnemigoEstandar;
class EnemigoFuego;
class BolaDeNieve;
class BolaDeFuego;
class PelotaDeNieve;
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

	// Dibuja el objeto en pantalla.
	virtual void dibujar(Camara * camara);

	// Aplica una modificacion.
	virtual void aplicarModificacion(ControladorJuego * juego);

	// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
	//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
	virtual void aplicarSobre(ObjetoModelo * objeto) = 0;
	virtual void aplicar(ObjetoModelo * modificacion);
	virtual void aplicar(SerVivo * modificacion){};
	virtual void aplicar(Enemigo * modificacion){};
	virtual void aplicar(Personaje * modificacion){};
	virtual void aplicar(EnemigoEstandar * modificacion){};
	virtual void aplicar(EnemigoFuego * modificacion){};
	virtual void aplicar(BolaDeNieve * modificacion){};
	virtual void aplicar(BolaDeFuego * modificacion){};

	// Describe las posibles orientaciones del objeto.
	enum orientacion_t{
		IZQUIERDA,
		DERECHA,
	};

	std::string ID;
	bool paraDestruir;
	FiguraGeometrica * espacioOcupado;
	float rotacion;
	orientacion_t orientacion;

protected:

	// Obtiene la textura que representa al objeto. Debe ser implementada
	// por las clases instanciadas pues es utilizada en el metodo dibujar para
	// determinar que dibujar.
	virtual Textura * obtenerTextura() = 0;

	// Calcula el sprite a dibujar segun el estado actual del objeto. Debe ser
	// implementada por las clases instanciadas pues es utilizada en el metodo
	// dibujar para determinar que dibujar.
	virtual FiguraGeometrica * obtenerSprite() = 0;

};

#endif /* OBJETOMODELO_H_ */
