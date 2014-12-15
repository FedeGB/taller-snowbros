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

class SerVivo: public ObjetoModelo {
public:
	virtual ~SerVivo();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
	//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
	virtual void aplicarSobre(ObjetoModelo * objeto);

	// Aplica la modificacion indicada sobre el personaje.
	virtual void aplicar(SerVivo * modificacion);

	// Describe las posibles acciones del personaje.
	enum estado_t{
		PARADO,
		CAMINANDO,
		SALTANDO,
		ATACANDO,
		ATRAPADO,
	};

	estado_t estado;
	int acumuladorCaminando;
	int acumuladorSaltando;
	int acumuladorAtacando;
	int acumuladorAtrapado;
};

#endif /* SERVIVO_H_ */
