/*
 * PantallaInicioSesion.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef PANTALLAINICIOSESION_H_
#define PANTALLAINICIOSESION_H_

#include <SDL2/SDL.h>
#include "../elementosMenues/BotonGUI.h"
#include "../elementosMenues/CajaDeTextoGUI.h"
#include "../Window.h"
#include "../../interfaces/Notificable.h"
#include "../../servicios/LocalizadorDeServicios.h"

class PantallaInicioSesion: public Notificable {
public:

	// Crea una pantalla de inicio de sesion.
	PantallaInicioSesion();

	// Destruye la pantalla.
	virtual ~PantallaInicioSesion();

	// Muestra una pantalla de login. En la misma, se pide al jugador que ingrese un
	// nombre de usuario, con el cual se lo reconocera durante la partida.
	// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
	void ejecutar(Window * ventana);

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Devuelve el nombre de usuario obtenido durante la ejecucion de la pantalla
	// de inicio de sesion.
	std::string obtenerNombreDeUsuario();

private:

	// Crea la GUI que corresponde a la pantalla de inicio de sesion.
	void inicializar();

	// Analiza los eventos acontecidos desde la ultima llamada a esta funcion, y actua
	// en base a ellos.
	void procesarEventos();

	// Dibuja la pantalla de inicio de sesion.
	// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
	bool dibujarPantalla(Window * ventana);

	// Destruye la GUI que utilizada durante la pantalla de inicio de sesion.
	void limpiar();

	BotonGUI * boton;
	CajaDeTextoGUI * cajaDeTexto;
	bool salirDePantalla;
	std::string nombreDeUsuario;

};

#endif /* PANTALLAINICIOSESION_H_ */
