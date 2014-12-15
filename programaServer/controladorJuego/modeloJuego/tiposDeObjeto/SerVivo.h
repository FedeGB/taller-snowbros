/*
 * SerVivo.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef SERVIVO_H_
#define SERVIVO_H_

#include <SDL2/SDL.h>
#include "../ObjetoModelo.h"
#include "../../../servicios/LocalizadorDeServicios.h"
#include "../../../matematica/FiguraGeometrica.h"
#include "../../../utiles/tipos.h"

class SerVivo: public ObjetoModelo {
public:
	SerVivo();
	// Levanta el ser vivo desde el archivo de configuracion Json.
	SerVivo(std::string sConfig, int numeroObjeto);
	virtual ~SerVivo();

	// Modifica los contactos de los pies para determinar si esta en el aire.
	void modificarContactosPie(int num);

	// Aplica el danio indicado.
	virtual void aplicarDanio(float danio);

	// Actualiza la informacion del objeto para poder dibujarlo.
	virtual void actualizar();

	// Describe las posibles acciones del personaje.
	enum estado_t{
		PARADO,
		CAMINANDO,
		SALTANDO,
		ATACANDO,
		ATRAPADO,
	};

	estado_t estado;
	float salud;
	bool sumergido;
	Vector2D posicionInicial;
	bool sorpresaCorrerActiva;

protected:

	bool moviendoIzquierda, moviendoDerecha;
	bool saltando;
	bool atacando, comenzoAtaque;
	int numContactosPie;
	int acumuladorAtaque;
	float factorEscalaVelocidad;

};

#endif /* SERVIVO_H_ */
