/*
 * LocalizadorDeServicios.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#include "LocalizadorDeServicios.h"

ServicioControladorDeTexturas * LocalizadorDeServicios::proveedorServicioTexturas = NULL;
ServicioNotificador * LocalizadorDeServicios::proveedorServicioNotificacion = NULL;
ServicioPosicionador * LocalizadorDeServicios::proveedorServicioPosicion = NULL;
ServicioInformacion * LocalizadorDeServicios::proveedorServicioInformacion = NULL;
SonidosMap * LocalizadorDeServicios::proveedorSonidos = NULL;

// Devuelve el objeto encargado de proveer la funcionalidad
// relacionada a texturas.
ServicioControladorDeTexturas * LocalizadorDeServicios::obtenerControladorDeTexturas(){
	return proveedorServicioTexturas;
}

// Asigna a 'proveedor' como el objeto que se encargara de proveer
// la funcionalidad relacionada a texturas.
void LocalizadorDeServicios::proveer(ServicioControladorDeTexturas * proveedor){
	proveedorServicioTexturas = proveedor;
}

// Devuelve el objeto encargado de notificar eventos sucedidos
// a aquellos modulos que necesiten la informacion.
ServicioNotificador * LocalizadorDeServicios::obtenerNotificador(){
	return proveedorServicioNotificacion;
}

// Asigna a 'proveedor' como el objeto que se encargara de manejar
// las noficaciones del programa.
void LocalizadorDeServicios::proveer(ServicioNotificador * proveedor){
	proveedorServicioNotificacion = proveedor;
}

// Devuelve el objeto encargado de posicionar objetos en pantalla.
ServicioPosicionador * LocalizadorDeServicios::obtenerPosicionador(){
	return proveedorServicioPosicion;
}

// Asigna a 'proveedor' como el objeto que se encargara de posicionar
// objetos en pantalla.
void LocalizadorDeServicios::proveer(ServicioPosicionador * proveedor){
	proveedorServicioPosicion = proveedor;
}

// Devuelve el objeto encargado de proveer informacion publica.
ServicioInformacion * LocalizadorDeServicios::obtenerInformacionPublica(){
	return proveedorServicioInformacion;
}

// Asigna a 'proveedor' como el objeto que se encargara de proveer
// informacion publica
void LocalizadorDeServicios::proveer(ServicioInformacion * proveedor){
	proveedorServicioInformacion = proveedor;
}

// Devuelve el objeto encargado de proveer sonidos.
SonidosMap * LocalizadorDeServicios::obtenerSonidos(){
	return proveedorSonidos;
}

// Asigna a 'proveedor' como el objeto que se encargara de proveer
// sonidos
void LocalizadorDeServicios::proveer(SonidosMap * proveedor){
	proveedorSonidos = proveedor;
}
