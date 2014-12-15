/*
 * PantallaJuego.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "PantallaJuego.h"

PantallaJuego::PantallaJuego() {
	modificaciones = NULL;
	juego = NULL;
	salirDePantalla = false;
	finDeNivel = finDeJuego = false;
	respuesta = ESPERANDO;
	botonSalir = botonVolverAJugar = botonSiguienteNivel = NULL;
	mensajeFinDeJuego = mensajeFinDeNivel = NULL;
	mensajeJugadorPerdio = botonSeguirMirando = NULL;
	jugadorPerdio = seguirMirando = false;
}

PantallaJuego::~PantallaJuego() {
}

// Crea la GUI que corresponde a la pantalla de juego.
void PantallaJuego::inicializar(){

	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	// Interfaz entre el thread de comunicacion y este, donde se renderea.
	modificaciones = new ControladorModificaciones();

	// Lanza el thread que se comunicara con el servidor.
	ControladorDeConexion * conexionConServidor= new ControladorDeConexion();
	if (!conexionConServidor) printf("No se pudo crear una conexion con el servidor.\n");
	else {
		conexionConServidor->establecerControladorModificaciones(modificaciones);
		conexionConServidor->iniciar();
	}

	// Inicializa el controlador de juego.
	juego = new ControladorJuego();
	juego->inicializar();

	// Inicializa los botones para el fin de juego / nivel.

	mensajeFinDeNivel = new BotonGUI();
	mensajeFinDeNivel->asignarPosicion(180,240);
	mensajeFinDeNivel->asignarDimensiones(360,40);
	mensajeFinDeNivel->asignarTexto("Cargar el siguiente nivel?");
	mensajeFinDeNivel->inicializar();

	botonSiguienteNivel = new BotonGUI();
	botonSiguienteNivel->asignarPosicion(240,380);
	botonSiguienteNivel->asignarDimensiones(240,40);
	botonSiguienteNivel->asignarTexto("Siguiente nivel");
	botonSiguienteNivel->inicializar();

	mensajeFinDeJuego = new BotonGUI();
	mensajeFinDeJuego->asignarPosicion(180,240);
	mensajeFinDeJuego->asignarDimensiones(360,40);
	mensajeFinDeJuego->asignarTexto("Fin del juego.");
	mensajeFinDeJuego->inicializar();

	botonSalir = new BotonGUI();
	botonSalir->asignarPosicion(60,380);
	botonSalir->asignarDimensiones(120,40);
	botonSalir->asignarTexto("Salir");
	botonSalir->inicializar();

	botonVolverAJugar = new BotonGUI();
	botonVolverAJugar->asignarPosicion(560,380);
	botonVolverAJugar->asignarDimensiones(120,40);
	botonVolverAJugar->asignarTexto("Volver a jugar");
	botonVolverAJugar->inicializar();

	mensajeJugadorPerdio = new BotonGUI();
	mensajeJugadorPerdio->asignarPosicion(180,240);
	mensajeJugadorPerdio->asignarDimensiones(360,40);
	mensajeJugadorPerdio->asignarTexto("PERDISTE");
	mensajeJugadorPerdio->inicializar();

	botonSeguirMirando = new BotonGUI();
	botonSeguirMirando->asignarPosicion(240,380);
	botonSeguirMirando->asignarDimensiones(240,40);
	botonSeguirMirando->asignarTexto("Seguir mirando");
	botonSeguirMirando->inicializar();

}

// Analiza los eventos acontecidos desde la ultima llamada a esta funcion, y actua
// en base a ellos.
void PantallaJuego::procesarEventos(){

	SDL_Event evento;
	while( SDL_PollEvent( &evento ) != 0 ) {

		if(jugadorPerdio && !finDeJuego && !finDeNivel){
			botonSeguirMirando->manejarEvento(evento);
		}
		if (finDeNivel){
			botonSiguienteNivel->manejarEvento(evento);
		}
		if (finDeJuego){
			botonSalir->manejarEvento(evento);
			botonVolverAJugar->manejarEvento(evento);
		}

		// Maneja para ver si sale.
		switch(evento.type){
		case SDL_QUIT:
			LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(CERRARPROGRAMA);
			break;
		case SDL_KEYDOWN:
			if (evento.key.keysym.sym == SDLK_ESCAPE)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(CERRARPROGRAMA);
			if (evento.key.keysym.sym == SDLK_UP)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJESALTO);
			if (evento.key.keysym.sym == SDLK_DOWN)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJEABAJO);
			if (evento.key.keysym.sym == SDLK_LEFT)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJEIZQUIERDA);
			if (evento.key.keysym.sym == SDLK_RIGHT)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJEDERECHA);
			if (evento.key.keysym.sym == SDLK_SPACE)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(MOVERPERSONAJEATAQUE);
			if (evento.key.keysym.sym == SDLK_KP_PLUS)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(ACERCARCAMARA);
			if (evento.key.keysym.sym == SDLK_KP_MINUS)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(ALEJARCAMARA);
			break;
		case SDL_KEYUP:
			if (evento.key.keysym.sym == SDLK_UP)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(DETENERMOVIMIENTOPERSONAJESALTO);
			if (evento.key.keysym.sym == SDLK_LEFT)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(DETENERMOVIMIENTOPERSONAJEIZQUIERDA);
			if (evento.key.keysym.sym == SDLK_RIGHT)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(DETENERMOVIMIENTOPERSONAJEDERECHA);
			if (evento.key.keysym.sym == SDLK_SPACE)
				LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(DETENERMOVIMIENTOPERSONAJEATAQUE);

			break;
		}
	}
}

// Actualiza el estado de todos los objetos del mundo en base a lo indicado por el thread
// controlador.
void PantallaJuego::actualizarObjetos(){

	if ( (finDeNivel == true || finDeJuego == true) && respuesta == VOLVERAJUGAR ){
		// TODO: mostrar una pantalla que deje elegir al jugador.
		juego->limpiar();
		juego->inicializar();
		LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(RESPUESTAVOLVERAJUGAR);
		finDeNivel = finDeJuego = false;
		respuesta = ESPERANDO;
	} else if ((finDeJuego == true) && respuesta == SALIR){
		LocalizadorDeServicios::obtenerNotificador()->enviarNotificaciones(RESPUESTASALIR);
	}

	while(ObjetoJuego * modificacion = modificaciones->obtenerModificacionSinBloquear())
		modificacion->aplicarModificacion(juego);

	juego->actualizar();
}

// Dibuja la pantalla de juego.
// 'ventana' es la ventana sobre la cual se mostrara la pantalla.
bool PantallaJuego::dibujarPantalla(Window * ventana){

	ventana->limpiarVentana();
	juego->dibujar();
	if (jugadorPerdio && !finDeJuego && !finDeNivel){
		mensajeJugadorPerdio->dibujar();
		if (!seguirMirando) botonSeguirMirando->dibujar();
	}
	if(finDeNivel){
		mensajeFinDeNivel->dibujar();
		botonSiguienteNivel->dibujar();
	}
	if (finDeJuego){
		mensajeFinDeJuego->dibujar();
		botonSalir->dibujar();
		botonVolverAJugar->dibujar();
	}
	ventana->actualizarVentana();
	return true;
}

// Destruye la GUI que utilizada durante la pantalla de juego.
void PantallaJuego::limpiar(){
	delete modificaciones;

	juego->limpiar();
	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);

	delete mensajeFinDeNivel;
	delete mensajeFinDeJuego;
	delete mensajeJugadorPerdio;
	delete botonSeguirMirando;
	delete botonSalir;
	delete botonVolverAJugar;
	delete botonSiguienteNivel;
}

// Muestra una pantalla de juego, donde se el jugador podra efectivamente jugar.
void PantallaJuego::ejecutar(Window * ventana){

	inicializar();

	salirDePantalla = false;

	while (!salirDePantalla){
		procesarEventos();
		actualizarObjetos();
		dibujarPantalla(ventana);
		LocalizadorDeServicios::obtenerSonidos()->actualizarEstados();
	}

	limpiar();
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void PantallaJuego::notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * objeto){

	// Verifica si se destruyo el personaje del jugador.
	if(notificacion == PERSONAJEDESTRUIDO && ((Personaje*)objeto)->nombre == LocalizadorDeServicios::obtenerInformacionPublica()->nombreUsuario){
		jugadorPerdio = true;
		seguirMirando = false;
	}

	// Verifica si se creo el personaje del jugador.
	if(notificacion == PERSONAJECREADO && ((Personaje*)objeto)->nombre == LocalizadorDeServicios::obtenerInformacionPublica()->nombreUsuario){
		jugadorPerdio = false;
	}
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void PantallaJuego::notificar(tipo_notificacion_t notificacion){

	if (notificacion == CERRARPROGRAMA) salirDePantalla = true;
	if (notificacion == FINDENIVEL)	finDeNivel = true;
	if (notificacion == FINDEJUEGO) {
		finDeJuego = true;
		if (juego->ganaron()) mensajeFinDeJuego->asignarTexto("GANARON! Quieres volver a jugar?");
		else mensajeFinDeJuego->asignarTexto("PERDIERON... Intentar de nuevo?");
	}

	if (notificacion == BOTONCLICKEADO && botonSalir->estaClickeado()) {
		respuesta = SALIR;
		salirDePantalla = true;
		botonSalir->declickear();
	}

	if (notificacion == BOTONCLICKEADO && botonVolverAJugar->estaClickeado()) {
		respuesta = VOLVERAJUGAR;
		botonVolverAJugar->declickear();
	}

	if (notificacion == BOTONCLICKEADO && botonSiguienteNivel->estaClickeado()) {
		respuesta = VOLVERAJUGAR;
		botonSiguienteNivel->declickear();
	}

	if (notificacion == BOTONCLICKEADO && botonSeguirMirando->estaClickeado()) {
		seguirMirando = true;
		botonSeguirMirando->declickear();
	}

}
