/*
 * PelotaDeNieve.h
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#ifndef PELOTADENIEVE_H_
#define PELOTADENIEVE_H_

#include "ObjetoInanimado.h"
#include <list>

class Personaje;

class PelotaDeNieve: public ObjetoInanimado {
public:
	PelotaDeNieve();
	// Levanta el personaje desde el archivo de configuracion Json.
	PelotaDeNieve(std::string sConfig, int numeroObjeto);
	virtual ~PelotaDeNieve();

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	// Agrega un personaje a la lista de personajes atrapados.
	void atraparPersonaje(Personaje * pj);

	// Actualiza la informacion del objeto para poder dibujarlo.
	void actualizar();

private:

	int acumuladorParaDestruccion;
	list<Personaje*> atrapados;
	bool tiroSorpresa;
};

#endif /* PELOTADENIEVE_H_ */
