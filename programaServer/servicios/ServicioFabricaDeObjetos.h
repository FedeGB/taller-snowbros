/*
 * ServicioFabricaDeObjetos.h
 *
 *  Created on: Dec 9, 2014
 *      Author: rodrizapico
 */

#ifndef SERVICIOFABRICADEOBJETOS_H_
#define SERVICIOFABRICADEOBJETOS_H_

#include "../controladorJuego/ControladorJuego.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/Personaje.h"

class ServicioFabricaDeObjetos {
public:
	//ServicioFabricaDeObjetos();
	virtual ~ServicioFabricaDeObjetos(){};

	// Fabrica una bola de nieve y la agrega al modelo.
	virtual void fabricarBolaDeNieve(Personaje * creador) = 0;

	// Fabrica una bola de fuego y la agrega al modelo.
	virtual void fabricarBolaDeFuego(EnemigoFuego * creador) = 0;

	// Fabrica una pelota de nieve y la agrega al modelo.
	virtual void fabricarPelotaDeNieve(Enemigo * creador) = 0;

	// Fabrica una sorpresa y la agrega al modelo.
	virtual void fabricarSorpresa(PelotaDeNieve * creador) = 0;

};

#endif /* SERVICIOFABRICADEOBJETOS_H_ */
