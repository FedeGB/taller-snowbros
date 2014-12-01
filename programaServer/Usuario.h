/*
 * Usuario.h
 *
 *  Created on: Oct 26, 2014
 *      Author: rodrizapico
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include "threads/ConditionVariable.h"
#include "threads/ThreadSafeList.h"
#include "threads/ColaTrabajo.h"
#include "server/WorkItem.h"
#include "modelo/WorldItem.h"
#include "modelo/Personaje.h"
#include "utiles/tipos.h"
#include <Box2D/Box2D.h>

#include "modelo/Sonido.h"
#include "modelo/SorpresaVida.h"
#include "modelo/SorpresaCorrer.h"
#include "modelo/SorpresaNieveMasLejos.h"
#include "modelo/SorpresaNieveMasPotente.h"

class Usuario {
public:
	Usuario();
	virtual ~Usuario();

	bool online;
	bool inicializado;
	std::string username;


	// Agrega una nueva notificacion por parte del handler de conexion para
	// ser recuperada por el handler de la simulacion B2D.
	// Debe ser usada solo por el handler de conexion.
	// IDEvento: ID del evento que se esta notificando.
	void encolarNotificacion(teclas_t IDEvento);

	// Recupera una notificacion dejada por el handler de conexion, para tratarla.
	// Debe ser usada solo por el handler de simulacion B2D.
	// return: el WorkItem a ser procesado, o NULL cuando no quedan mas notificaciones
	// a procesar.
	WorkItem * desencolarNotificacion();

	// Procesa todas las notificaciones en la cola de notificaciones. Es llamada
	// por el handler de simulacion B2D.
	void procesarNotificaciones();

	// Devuelve una representacion serializada de lo que ve el usuario en su camara,
	// para poder ser rendereada en el cliente.
	std::string obtenerPantallaSerializada();

	// Notifica a los threads que esten esperando por este usuario, para que
	// continuen ejecutando.
	void enviarSenial();

	// El thread llamante espera hasta que se notifique que puede continuar
	// ejecutando, mediante una llamada a enviarSenial().
	void esperarSenial();

	// Inicializa el PJ asociado a este usuario, con su correspondiente camara.
	void inicializarPJ(b2World * worldB2D, std::string);

	// Actualiza el estado del PJ y su camara asociada.
	void actualizarPJ();

	void setOnline(bool estado);

	b2Vec2 getPosition();

	bool isPJAlive();

	void eventoa();

	float getLives();

private:
	ColaTrabajo<WorkItem*>  colaNotificaciones;
	ConditionVariable c;
	Personaje * PJ;
	ThreadSafeList<WorldItem*> listaVisibles;

	Sonido* sonidoPJ;
};

#endif /* USUARIO_H_ */
