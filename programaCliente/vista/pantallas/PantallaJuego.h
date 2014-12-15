/*
 * PantallaJuego.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef PantallaJuego_H_
#define PantallaJuego_H_

#include <SDL2/SDL.h>
#include "../elementosMenues/BotonGUI.h"
#include "../elementosMenues/CajaDeTextoGUI.h"
#include "../Window.h"
#include "../../interfaces/Notificable.h"
#include "../../servicios/LocalizadorDeServicios.h"
#include "../../threads/ControladorDeConexion.h"
#include "../../ControladorModificaciones.h"
#include "../../controladorJuego/ControladorJuego.h"

class PantallaJuego: public Notificable {
public:

	// Crea una pantalla de juego.
	PantallaJuego();

	// Destruye la pantalla.
	virtual ~PantallaJuego();

	// Muestra una pantalla de juego, donde se el jugador podra efectivamente jugar.
	void ejecutar(Window * ventana);

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto);

private:

	// Crea la GUI que corresponde a la pantalla de juego.
	void inicializar();

	// Analiza los eventos acontecidos desde la ultima llamada a esta funcion, y actua
	// en base a ellos.
	void procesarEventos();

	// Actualiza el estado de todos los objetos del mundo en base a lo indicado por el thread
	// controlador.
	void actualizarObjetos();

	// Dibuja la pantalla de juego.
	// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
	bool dibujarPantalla(Window * ventana);

	// Destruye la GUI que utilizada durante la pantalla de juego.
	void limpiar();

	enum respuesta_t{
		ESPERANDO,
		VOLVERAJUGAR,
		SALIR,
	};

	bool salirDePantalla;
	bool esperar;
	bool conexionRechazada;
	bool finDeNivel;
	bool finDeJuego;
	respuesta_t respuesta;

	ControladorModificaciones * modificaciones;
	ControladorJuego * juego;

	BotonGUI * mensajeFinDeNivel, * mensajeFinDeJuego;
	BotonGUI * botonVolverAJugar, * botonSalir, * botonSiguienteNivel;
	BotonGUI * mensajeJugadorPerdio, * botonSeguirMirando;
	BotonGUI * mensajeEsperar;
	BotonGUI * mensajeRechazo;
	bool jugadorPerdio, seguirMirando;

};

#endif /* PantallaJuego_H_ */
