/*
 * Cliente.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "Cliente.h"

// Instancia principal del programa.
Cliente::Cliente(){
	ventana = NULL;
	mapaTexturas = NULL;
	notificador = NULL;
	posicionador = NULL;
	informacion = NULL;
	salir = false;
}

Cliente::~Cliente(){

}

// Ejecuta el programa.
void Cliente::ejecutar(){

	// Inicializa aquello que sea necesario para la ejecucion del cliente.
	if (inicializarCliente() == ERROR_CLIENTE) return;

	// Primero inicia sesion, registrando un nombre de usuario; luego entra al menu principal.
	while (!salir){
		// Muestra la pantalla de inicio de sesion.
		PantallaInicioSesion inicioSesion;
		inicioSesion.ejecutar(ventana);
		if (salir == true) continue;

		// Determina el nombre de usuario.
		std::string nombreDeUsuario = inicioSesion.obtenerNombreDeUsuario();
		LocalizadorDeServicios::obtenerInformacionPublica()->nombreUsuario = nombreDeUsuario;

		// Ejecuta el loop del menu principal.
		ejecutarLoopMenuPrincipal();
	}

	limpiarCliente();
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void Cliente::notificar(tipo_notificacion_t notificacion){
	if (notificacion == CERRARPROGRAMA) salir = true;
}

// Carga los parametros necesarios para la ejecucion del cliente, e inicializa los
// modulos que necesiten inicializacion.
bool Cliente::inicializarCliente(){

	// Inicializo la ventana.
	ventana = new Window();
	if (ventana->init(720, 640) == ERROR_CLIENTE) return false;

	// Inicializo el mapa de texturas y lo establezco como proveedor de texturas.
	mapaTexturas = new TextureMap();
	if (mapaTexturas->inicializar() == ERROR_CLIENTE) return false;
	LocalizadorDeServicios::proveer(mapaTexturas);

	// Inicializo el notificador y lo establezco como proveedor de notificaciones.
	notificador = new Notificador();
	LocalizadorDeServicios::proveer(notificador);
	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);

	// Inicializo el posicionador y lo establezco como proveedor de posiciones.
	posicionador = new PosicionadorObjetos();
	LocalizadorDeServicios::proveer(posicionador);

	// Inicializo el servicio de informacion y lo establezco como proveedor de informacion.
	informacion = new ServicioInformacion();
	LocalizadorDeServicios::proveer(informacion);

	// Inicializo el sonido y lo establece como proveedor de sonidos.
	sonidos = new SonidosMap();
	sonidos->init();
	LocalizadorDeServicios::proveer(sonidos);

	return true;
}

// Libera memoria y realiza las acciones necesarias para cerrar en un estado valido.
void Cliente::limpiarCliente(){
	delete ventana;
	delete mapaTexturas;
	delete notificador;
	delete posicionador;
	delete informacion;
	delete sonidos;
}

// Ejecuta el loop del menu principal, que va alternando entre el menu en si mismo,
// la pantalla de opciones y el juego.
void Cliente::ejecutarLoopMenuPrincipal(){
	// Carga el menu principal.
	PantallaMenuPrincipal menuPrincipal;
	PantallaMenuPrincipal::eleccion_t eleccion = PantallaMenuPrincipal::INICIARJUEGO;

	// Alterna entre el menu principal, las opciones, y jugar el juego; o rompe el loop y
	// vuelve a la pantalla de inicio de sesion.
	while (eleccion != PantallaMenuPrincipal::ATRAS){

		menuPrincipal.ejecutar(ventana);
		if (salir == true) break;

		eleccion = menuPrincipal.obtenerEleccion();
		if (eleccion == PantallaMenuPrincipal::INICIARJUEGO) {
			//TODO: simular el juego.
			std::cout << "iniciarJuego presionado" << std::endl;
			PantallaJuego juego;
			juego.ejecutar(ventana);
			if (salir == true) break;
		} else if (eleccion == PantallaMenuPrincipal::OPCIONES) {
			//TODO: implementar menu de opciones.
			PantallaOpciones opciones;
			opciones.ejecutar(ventana);
			if (salir == true) break;
		}
	}
}
