/*
 * Cliente.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "vista/pantallas/PantallaInicioSesion.h"
#include "vista/pantallas/PantallaMenuPrincipal.h"
#include "vista/pantallas/PantallaOpciones.h"
#include "vista/pantallas/PantallaJuego.h"
#include "vista/TextureMap.h"
#include "servicios/Notificador.h"
#include "servicios/PosicionadorObjetos.h"
#include "servicios/ServicioInformacion.h"
#include "servicios/LocalizadorDeServicios.h"
#include "interfaces/Notificable.h"

const bool ERROR_CLIENTE = false;

class Cliente: public Notificable {
public:

	// Instancia principal del programa.
	Cliente();
	virtual ~Cliente();

	// Ejecuta el programa.
	void ejecutar();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

private:

	// Carga los parametros necesarios para la ejecucion del cliente, e inicializa los
	// modulos que necesiten inicializacion.
	bool inicializarCliente();

	// Libera memoria y realiza las acciones necesarias para cerrar en un estado valido.
	void limpiarCliente();

	// Ejecuta el loop del menu principal, que va alternando entre el menu en si mismo,
	// la pantalla de opciones y el juego.
	void ejecutarLoopMenuPrincipal();

	Window * ventana;
	TextureMap * mapaTexturas;
	Notificador * notificador;
	PosicionadorObjetos * posicionador;
	ServicioInformacion * informacion;
	SonidosMap * sonidos;
	bool salir;
};

#endif /* CLIENTE_H_ */
