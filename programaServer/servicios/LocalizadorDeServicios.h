/*
 * LocalizadorDeServicios.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef LOCALIZADORDESERVICIOS_H_
#define LOCALIZADORDESERVICIOS_H_

#include <stddef.h>
#include "ServicioNotificador.h"
#include "ServicioPosicionador.h"
#include "ServicioInformacion.h"

class ServicioFabricaDeObjetos;

class LocalizadorDeServicios {
public:

/*	// Devuelve el objeto encargado de proveer la funcionalidad
	// relacionada a texturas.
	static ServicioControladorDeTexturas * obtenerControladorDeTexturas();

	// Asigna a 'proveedor' como el objeto que se encargara de proveer
	// la funcionalidad relacionada a texturas.
	static void proveer(ServicioControladorDeTexturas * proveedor);
*/
	// Devuelve el objeto encargado de notificar eventos sucedidos
	// a aquellos modulos que necesiten la informacion.
	static ServicioNotificador * obtenerNotificador();

	// Asigna a 'proveedor' como el objeto que se encargara de manejar
	// las noficaciones del programa.
	static void proveer(ServicioNotificador * proveedor);

	// Devuelve el objeto encargado de posicionar objetos en pantalla.
	static ServicioPosicionador * obtenerPosicionador();

	// Asigna a 'proveedor' como el objeto que se encargara de posicionar
	// objetos en pantalla.
	static void proveer(ServicioPosicionador * proveedor);

	// Devuelve el objeto encargado de proveer informacion publica.
	static ServicioInformacion * obtenerInformacionPublica();

	// Asigna a 'proveedor' como el objeto que se encargara de
	// proveer informacion publica.
	static void proveer(ServicioInformacion * proveedor);

	// Devuelve el objeto encargado de fabricar objetos y agregarlos al modelo.
	static ServicioFabricaDeObjetos * obtenerFabricaDeObjetos();

	// Asigna a 'proveedor' como el objeto que se encargara de
	// fabricar objetos y agregarlos al modelo
	static void proveer(ServicioFabricaDeObjetos * proveedor);

private:

	// El objeto encargado de proveer la funcionalidad de texturas.
	//static ServicioControladorDeTexturas * proveedorServicioTexturas;

	// El objeto encargado de las notificaciones.
	static ServicioNotificador * proveedorServicioNotificacion;

	// El objeto encargado de asignar posiciones en pantalla.
	static ServicioPosicionador * proveedorServicioPosicion;

	// El objeto encargado de asignar posiciones en pantalla.
	static ServicioInformacion * proveedorServicioInformacion;

	// El objeto encargado de asignar posiciones en pantalla.
	static ServicioFabricaDeObjetos * proveedorServicioFabrica;

};

#endif /* LOCALIZADORDESERVICIOS_H_ */
