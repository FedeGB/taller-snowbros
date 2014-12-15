/*
 * Fondo.h
 *
 *  Created on: Dec 14, 2014
 *      Author: rodrizapico
 */

#ifndef FONDO_H_
#define FONDO_H_

#include "../ObjetoModelo.h"
#include "../Camara.h"

class Fondo: public ObjetoModelo {
public:
	Fondo(Camara * cam);
	virtual ~Fondo();

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();

	// Dibuja el objeto en pantalla.
	virtual void dibujar(Camara * camara);

	virtual void aplicarSobre(ObjetoModelo * objeto);

	Camara * cam;
};

#endif /* FONDO_H_ */
