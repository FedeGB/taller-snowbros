/*
 * ServicioInformacion.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: rodrizapico
 */

#include "ServicioInformacion.h"

ServicioInformacion::ServicioInformacion() {
	IP = "127.0.0.1";
	archivoConfiguracion = "defaultConfig.json";
	puerto = 2020;
	tamanioMapa.x = 720; tamanioMapa.y = 640;
	numJugadores = -1;
}

ServicioInformacion::~ServicioInformacion() {
}

