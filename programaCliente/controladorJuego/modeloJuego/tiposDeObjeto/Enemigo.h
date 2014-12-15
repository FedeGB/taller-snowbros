/*
 * Enemigo.h
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include "SerVivo.h"
#include "../Camara.h"

class Enemigo: public SerVivo {
public:
	Enemigo();
	virtual ~Enemigo();

	// Dibuja el objeto en pantalla.
	void dibujar(Camara * camara);

	// Aplica la modificacion indicada sobre el objeto. Las clases que heredan
	//solo deben implementar el aplicar a la modificacion que corresponda a si misma.
	virtual void aplicarSobre(ObjetoModelo * objeto);

	// Aplica la modificacion indicada sobre el personaje.
	virtual void aplicar(Enemigo * modificacion);

	float salud;

private:

	// Dibuja la bola de nieve que cubre al enemigo, si este esta atrapado.
	void dibujarBolaDeNieve(Camara * camara);
};

#endif /* ENEMIGO_H_ */
