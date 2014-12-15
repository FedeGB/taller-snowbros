/*
 * Personaje.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <SDL2/SDL.h>
#include "../../../interfaces/EnviadorNotificaciones.h"
#include "SerVivo.h"

class Personaje: public SerVivo, public EnviadorNotificaciones{
public:

	// Representacion de un personaje controlado por el usuario.
	Personaje();
	virtual ~Personaje();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	// Inicializa al objeto.
	virtual void inicializar();

	// Elimina lo que sea necesario.
	virtual void limpiar();

	// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
	//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
	virtual void aplicarSobre(ObjetoModelo * objeto);

	// Aplica la modificacion indicada sobre el personaje.
	virtual void aplicar(Personaje * modificacion);

	// Dibuja el objeto en pantalla.
	virtual void dibujar(Camara * camara);

	std::string nombre;
	bool inmune;
	bool murio;
	int acumuladorMuerte;
	int acumuladorInmunidad;
	bool inicializado;

protected:

	// Dibuja la animacion de inmunidad del PJ.
	void dibujarInmunidad(Camara * camara);

	// Obtiene la textura que representa al objeto.
	virtual Textura * obtenerTextura();

	// Calcula el sprite a dibujar segun el estado actual del objeto.
	virtual FiguraGeometrica * obtenerSprite();
};

#endif /* PERSONAJE_H_ */
