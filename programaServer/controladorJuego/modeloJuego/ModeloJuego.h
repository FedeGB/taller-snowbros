/*
 * ModeloJuego.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef ModeloJuego_H_
#define ModeloJuego_H_

#include <map>
#include "../../interfaces/Notificable.h"
#include "../../servicios/LocalizadorDeServicios.h"
#include "ObjetoModelo.h"
#include "tiposDeObjeto/Personaje.h"
#include "tiposDeObjeto/Enemigo.h"

class ModeloJuego: public Notificable {
public:

	// Representacion del modelo del juego actual: mapa, posicion de los personajes,
	// enemigos, obstaculos, poderes, etc.
	ModeloJuego();

	// Destruye la representacion del modelo de juego.
	virtual ~ModeloJuego();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	void notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto);

	// Inicializa el modelo del juego.
	void inicializar();

	// Actualiza el modelo del juego.
	void actualizar(int cantidadOnline);

	// Destruye el modelo del juego para asegurar un correcto finalizado
	// de los modulos involucrados.
	void limpiar();

	// Verifique que queden enemigos vivos en el modelo.
	bool quedanEnemigos();

	// Verifica la existencia de un objeto en el modelo.
	bool existeObjeto(std::string ID);

	// Agrega un objeto al modelo.
	void agregarObjeto (ObjetoModelo * objeto);

	// Agrega un personaje al modelo.
	void agregarPersonaje (Personaje * personaje);

	// Agrega un enemigo al modelo.
	void agregarEnemigo (Enemigo * enemigo);

	// Elimina un objeto del modelo.
	void eliminarObjeto (std::string ID);

	// Elimina un personaje del modelo.
	void eliminarPersonaje (std::string ID);

	// Elimina un enemigo del modelo.
	void eliminarEnemigo (std::string ID);

	friend class ControladorJuego;

	std::map<std::string, ObjetoModelo *> objetos;
	std::map<std::string, Personaje *> personajes;
	std::map<std::string, Enemigo *> enemigos;

private:

	// Calcula que PJ sera atacado por el enemigo actual.
	// Actualmente solo tiene en cuenta la distancia para determinar el objetivo.
	Personaje * obtenerPJAAtacar(Enemigo * enemigo);

	int ID;

};

#endif /* ModeloJuego_H_ */
