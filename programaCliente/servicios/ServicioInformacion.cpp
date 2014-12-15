/*
 * ServicioInformacion.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: rodrizapico
 */

#include "ServicioInformacion.h"

ServicioInformacion::ServicioInformacion() {
	nombreUsuario = "Jugador";
	IP = "127.0.0.1";
	puerto = 2020;
	tamanioMapa.x = 720; tamanioMapa.y = 640;
	resolucionPantalla.x = 720; resolucionPantalla.y = 640;
	sonidoEncendido = true;
	pantallaCompleta = false;
}

ServicioInformacion::~ServicioInformacion() {
}

