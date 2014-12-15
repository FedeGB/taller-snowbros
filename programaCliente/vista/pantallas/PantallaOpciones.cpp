/*
 * PantallaOpciones.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "PantallaOpciones.h"

PantallaOpciones::PantallaOpciones() {
	botonGuardarCambios = NULL;
	botonAtras = NULL;
	IPServidor = NULL;
	puertoServidor = NULL;
	salirDePantalla = false;
	mensajeIP = mensajePuerto = NULL;
}

PantallaOpciones::~PantallaOpciones() {
}

// Crea la GUI que corresponde a la pantalla de inicio de sesion.
void PantallaOpciones::inicializar(){

	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	botonGuardarCambios = new BotonGUI();
	botonGuardarCambios->asignarPosicion(240,560);
	botonGuardarCambios->asignarDimensiones(240,40);
	botonGuardarCambios->asignarTexto("Guardar cambios");
	botonGuardarCambios->inicializar();

	botonAtras = new BotonGUI();
	botonAtras->asignarPosicion(570,560);
	botonAtras->asignarDimensiones(120,40);
	botonAtras->asignarTexto("Atras");
	botonAtras->inicializar();

	mensajeIP = new BotonGUI();
	mensajeIP->asignarPosicion(60,200);
	mensajeIP->asignarDimensiones(60,40);
	mensajeIP->asignarTexto(" IP: ");
	mensajeIP->inicializar();

	mensajePuerto = new BotonGUI();
	mensajePuerto->asignarPosicion(30,280);
	mensajePuerto->asignarDimensiones(120,40);
	mensajePuerto->asignarTexto(" Puerto ");
	mensajePuerto->inicializar();

	IPServidor = new CajaDeTextoGUI();
	IPServidor->asignarPosicion(180,200);
	IPServidor->asignarDimensiones(360,40);
	IPServidor->inicializar();

	puertoServidor = new CajaDeTextoGUI();
	puertoServidor->asignarPosicion(180,280);
	puertoServidor->asignarDimensiones(360,40);
	puertoServidor->inicializar();
}

// Analiza los eventos acontecidos desde la ultima llamada a esta funcion, y actua
// en base a ellos.
void PantallaOpciones::procesarEventos(){

	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ) {

		// Le da el evento a los elementos del programa para que lo procesen.
		botonGuardarCambios->manejarEvento(evento);
		botonAtras->manejarEvento(evento);
		IPServidor->manejarEvento(evento);
		puertoServidor->manejarEvento(evento);

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
bool PantallaOpciones::dibujarPantalla(Window * ventana){

	ventana->limpiarVentana();
	botonGuardarCambios->dibujar();
	botonAtras->dibujar();
	mensajeIP->dibujar();
	mensajePuerto->dibujar();
	IPServidor->dibujar();
	puertoServidor->dibujar();
	ventana->actualizarVentana();
	return true;
}

// Destruye la GUI que utilizada durante la pantalla de inicio de sesion.
void PantallaOpciones::limpiar(){
	delete botonGuardarCambios;
	delete botonAtras;
	delete mensajePuerto;
	delete mensajeIP;
	delete IPServidor;
	delete puertoServidor;

	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);
}

// Muestra una pantalla de login. En la misma, se pide al jugador que ingrese un
// nombre de usuario, con el cual se lo reconocera durante la partida.
// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
void PantallaOpciones::ejecutar(Window * ventana){

	inicializar();

	salirDePantalla = false;

	while (!salirDePantalla){
		procesarEventos();
		dibujarPantalla(ventana);
	}

	limpiar();
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void PantallaOpciones::notificar(tipo_notificacion_t notificacion){
	if (notificacion == BOTONCLICKEADO && botonGuardarCambios->estaClickeado()) {
		//salirDePantalla = true;
		std::cout << "guardando cambios..." << std::endl;
		botonGuardarCambios->declickear();
		LocalizadorDeServicios::obtenerInformacionPublica()->IP = IPServidor->obtenerContenido();
		LocalizadorDeServicios::obtenerInformacionPublica()->puerto = atoi(puertoServidor->obtenerContenido().c_str());
	}

	if (notificacion == BOTONCLICKEADO && botonAtras->estaClickeado()) {
		salirDePantalla = true;
		botonAtras->declickear();
	}

	if (notificacion == CERRARPROGRAMA) salirDePantalla = true;
}
