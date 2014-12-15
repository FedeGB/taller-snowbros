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
#include "Camara.h"
#include "ObjetoModelo.h"
#include "tiposDeObjeto/Fondo.h"

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
	void actualizar();

	// Destruye el modelo del juego para asegurar un correcto finalizado
	// de los modulos involucrados.
	void limpiar();

	// Dibuja la seccion del modelo de juego visible en la pantalla.
	void dibujar();

	// Verifica la existencia de un objeto en el modelo.
	bool existeObjeto(std::string ID);

	// Modifica un objeto en base a los cambios indicados en 'modificacion'.
	void modificarObjeto(ObjetoModelo * modificacion);

	// Agrega un nuevo objeto al modelo.
	void agregarObjeto(ObjetoModelo * modificacion);

	// Quita un objeto del modelo.
	void destruirObjeto(ObjetoModelo * modificacion);

	friend class ControladorJuego;

private:

	std::map<std::string, ObjetoModelo *> objetos;
	Camara * camara;
	Fondo * fondo;
};

#endif /* ModeloJuego_H_ */
