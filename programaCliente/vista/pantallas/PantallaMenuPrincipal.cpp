/*
 * PantallaMenuPrincipal.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "PantallaMenuPrincipal.h"

PantallaMenuPrincipal::PantallaMenuPrincipal() {
	botonIniciarJuego = NULL;
	botonOpciones = NULL;
	botonAtras = NULL;
	salirDePantalla = false;
	eleccion = OPCIONES;
}

PantallaMenuPrincipal::~PantallaMenuPrincipal() {
}

// Crea la GUI que corresponde a la pantalla de menu principal.
void PantallaMenuPrincipal::inicializar(){

	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	botonIniciarJuego = new BotonGUI();
	botonIniciarJuego ->asignarPosicion(60,300);
	botonIniciarJuego ->asignarDimensiones(120,40);
	botonIniciarJuego ->asignarTexto("Jugar");
	botonIniciarJuego ->inicializar();

	botonOpciones = new BotonGUI();
	botonOpciones->asignarPosicion(60,380);
	botonOpciones->asignarDimensiones(120,40);
	botonOpciones->asignarTexto("Opciones");
	botonOpciones->inicializar();

	botonAtras = new BotonGUI();
	botonAtras->asignarPosicion(560,20);
	botonAtras->asignarDimensiones(120,40);
	botonAtras->asignarTexto("Atras");
	botonAtras->inicializar();
}

// Analiza los eventos acontecidos desde la ultima llamada a esta funcion, y actua
// en base a ellos.
void PantallaMenuPrincipal::procesarEventos(){

	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ) {

		// Le da el evento a los elementos del programa para que lo procesen.
		botonIniciarJuego->manejarEvento(evento);
		botonOpciones->manejarEvento(evento);
		botonAtras->manejarEvento(evento);

		// Maneja para ver si sale.
		switch(evento.type){
		case SDL_QUIT:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(CERRARPROGRAMA);
			break;
		case SDL_KEYDOWN:
			if (evento.key.keysym.sym == SDLK_ESCAPE)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(CERRARPROGRAMA);
			break;
		}
	}
}

// Dibuja la pantalla de menu principal.
// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
bool PantallaMenuPrincipal::dibujarPantalla(Window * ventana){

	ventana->limpiarVentana();
	botonIniciarJuego->dibujar();
	botonOpciones->dibujar();
	botonAtras->dibujar();
	ventana->actualizarVentana();
	return true;
}

// Destruye la GUI que utilizada durante la pantalla de menu principal.
void PantallaMenuPrincipal::limpiar(){
	delete botonIniciarJuego;
	delete botonOpciones;
	delete botonAtras;

	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);
}

// Muestra el menu principal del juego. En el mismo, se da la opcion de
// iniciar una partida, o configurar las opciones del juego.
// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
void PantallaMenuPrincipal::ejecutar(Window * ventana){

	inicializar();

	salirDePantalla = false;

	while (!salirDePantalla){
		procesarEventos();
		dibujarPantalla(ventana);
	}

	limpiar();
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void PantallaMenuPrincipal::notificar(tipo_notificacion_t notificacion){

	if (notificacion == BOTONCLICKEADO && botonIniciarJuego->estaClickeado()) {
		eleccion = INICIARJUEGO;
		salirDePantalla = true;
		botonIniciarJuego->declickear();
	}

	if (notificacion == BOTONCLICKEADO && botonOpciones->estaClickeado()) {
		eleccion = OPCIONES;
		salirDePantalla = true;
		botonOpciones->declickear();
	}

	if (notificacion == BOTONCLICKEADO && botonAtras->estaClickeado()) {
		eleccion = ATRAS;
		salirDePantalla = true;
		botonAtras->declickear();
	}

	if (notificacion == CERRARPROGRAMA) salirDePantalla = true;

}

// Devuelve la eleccion tomada por el usuario.
PantallaMenuPrincipal::eleccion_t PantallaMenuPrincipal::obtenerEleccion(){
	return eleccion;
}
