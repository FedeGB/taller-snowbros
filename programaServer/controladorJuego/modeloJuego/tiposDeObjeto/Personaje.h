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
#include "Enemigo.h"

class PelotaDeNieve;

class Personaje: public SerVivo, public EnviadorNotificaciones{
public:

	// Representacion de un personaje controlado por el usuario.
	Personaje();

	// Levanta el personaje desde el archivo de configuracion Json.
	Personaje(std::string sConfig, int numeroObjeto);
	virtual ~Personaje();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * origen);

	// Serializa la informacion de un elemento del modelo para su almacenamiento.
	virtual std::string serializar();

	// Inicializa al objeto.
	virtual void inicializar();

	// Elimina lo que sea necesario.
	virtual void limpiar();

	// Aplica el danio indicado.
	virtual void aplicarDanio(float danio);

	// Atrapa al personaje en una pelota.
	void atraparEnPelota(PelotaDeNieve * pelota);

	// Libera al personaje de una pelota.
	void liberarDePelota();

	// Actualiza la informacion del objeto para poder dibujarlo.
	virtual void actualizar();

	std::string nombre;
	bool inicializado;
	bool puedePatear;
	bool murio, inmune;
	int acumuladorInmunidad;
	bool acabaDePatear, atrapado;
	int acumuladorInmunidadPatada;
	PelotaDeNieve * pelota;
	Enemigo * enemigoParaEmpujar;
	int puntaje;
	int acumuladorMuerte;
	bool sorpresaNievePotenteActiva, sorpresaNieveLejosActiva;
	int acumuladorPotente, acumuladorLejos, acumuladorCorrer;

};

#endif /* PERSONAJE_H_ */
