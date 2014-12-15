/*
 * PantallaInicioSesion.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "PantallaInicioSesion.h"

PantallaInicioSesion::PantallaInicioSesion() {
	boton = NULL;
	cajaDeTexto = NULL;
	salirDePantalla = false;
}

PantallaInicioSesion::~PantallaInicioSesion() {
}

// Crea la GUI que corresponde a la pantalla de inicio de sesion.
void PantallaInicioSesion::inicializar(){

	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	boton = new BotonGUI();
	boton->asignarPosicion(570,400);
	boton->asignarDimensiones(120,40);
	boton->asignarTexto("Iniciar");
	boton->inicializar();

	mensaje = new BotonGUI();
	mensaje->asignarPosicion(180,340);
	mensaje->asignarDimensiones(360,40);
	mensaje->asignarTexto("  Ingrese nombre de usuario:  ");
	mensaje->inicializar();


	cajaDeTexto = new CajaDeTextoGUI();
	cajaDeTexto->asignarPosicion(180,400);
	cajaDeTexto->asignarDimensiones(360,40);
	cajaDeTexto->inicializar();
}

// Analiza los eventos acontecidos desde la ultima llamada a esta funcion, y actua
// en base a ellos.
void PantallaInicioSesion::procesarEventos(){

	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ) {

		// Le da el evento a los elementos del programa para que lo procesen.
		boton->manejarEvento(evento);
		cajaDeTexto->manejarEvento(evento);

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

// Dibuja la pantalla de inicio de sesion.
// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
bool PantallaInicioSesion::dibujarPantalla(Window * ventana){

	ventana->limpiarVentana();
	boton->dibujar();
	mensaje->dibujar();
	cajaDeTexto->dibujar();
	ventana->actualizarVentana();
	return true;
}

// Destruye la GUI que utilizada durante la pantalla de inicio de sesion.
void PantallaInicioSesion::limpiar(){
	delete boton;
	delete mensaje;
	delete cajaDeTexto;

	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);
}

// Muestra una pantalla de login. En la misma, se pide al jugador que ingrese un
// nombre de usuario, con el cual se lo reconocera durante la partida.
// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
void PantallaInicioSesion::ejecutar(Window * ventana){

	inicializar();

	salirDePantalla = false;

	while (!salirDePantalla){
		procesarEventos();
		dibujarPantalla(ventana);
	}

	limpiar();
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void PantallaInicioSesion::notificar(tipo_notificacion_t notificacion){
	if (notificacion == BOTONCLICKEADO && boton->estaClickeado()) {
		salirDePantalla = true;
		nombreDeUsuario = cajaDeTexto->obtenerContenido();
		boton->declickear();
	}

	if (notificacion == CAJADETEXTOLLENA && cajaDeTexto->estaLlena()) {
		salirDePantalla = true;
		nombreDeUsuario = cajaDeTexto->obtenerContenido();
		cajaDeTexto->vaciar();
	}

	if (notificacion == CERRARPROGRAMA) salirDePantalla = true;

}

// Devuelve el nombre de usuario obtenido durante la ejecucion de la pantalla
// de inicio de sesion.
std::string PantallaInicioSesion::obtenerNombreDeUsuario(){
	return nombreDeUsuario;
}
