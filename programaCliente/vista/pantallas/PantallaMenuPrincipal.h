/*
 * PantallaMenuPrincipal.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef PantallaMenuPrincipal_H_
#define PantallaMenuPrincipal_H_

#include <SDL2/SDL.h>
#include "../elementosMenues/BotonGUI.h"
#include "../elementosMenues/CajaDeTextoGUI.h"
#include "../Window.h"
#include "../../interfaces/Notificable.h"
#include "../../servicios/LocalizadorDeServicios.h"

class PantallaMenuPrincipal: public Notificable {
public:

	// Crea una pantalla de menu principal.
	PantallaMenuPrincipal();

	// Destruye la pantalla.
	virtual ~PantallaMenuPrincipal();

	// Muestra el menu principal del juego. En el mismo, se da la opcion de
	// iniciar una partida, o configurar las opciones del juego.
	// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
	void ejecutar(Window * ventana);

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);


	// Enumera las posibles elecciones tomadas al salir del menu principal.
	enum eleccion_t{
		INICIARJUEGO,
		OPCIONES,
		ATRAS,
	};

	// Devuelve la eleccion tomada por el usuario.
	eleccion_t obtenerEleccion();

private:

	// Crea la GUI que corresponde a la pantalla de menu principal.
	void inicializar();

	// Analiza los eventos acontecidos desde la ultima llamada a esta funcion, y actua
	// en base a ellos.
	void procesarEventos();

	// Dibuja la pantalla de menu principal.
	// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
	bool dibujarPantalla(Window * ventana);

	// Destruye la GUI que utilizada durante la pantalla de menu principal.
	void limpiar();

	BotonGUI * botonIniciarJuego;
	BotonGUI * botonOpciones;
	BotonGUI * botonAtras;
	bool salirDePantalla;
	eleccion_t eleccion;

};

#endif /* PantallaMenuPrincipal_H_ */
