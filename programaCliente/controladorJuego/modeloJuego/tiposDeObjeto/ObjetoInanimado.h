/*
 * ObjetoInanimado.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef OBJETOINANIMADO_H_
#define OBJETOINANIMADO_H_

#include "../ObjetoModelo.h"
#include "../../../servicios/LocalizadorDeServicios.h"

class ObjetoInanimado: public ObjetoModelo {
public:
	virtual ~ObjetoInanimado();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
	//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
	virtual void aplicarSobre(ObjetoModelo * objeto);

	// Aplica la modificacion indicada sobre el personaje.
	virtual void aplicar(ObjetoInanimado * modificacion);
};

#endif /* OBJETOINANIMADO_H_ */
