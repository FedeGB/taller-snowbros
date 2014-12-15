/*
 * Servidor.h
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "servicios/Notificador.h"
#include "servicios/ServicioInformacion.h"
#include "servicios/LocalizadorDeServicios.h"
#include "controladorJuego/ControladorJuego.h"
#include "interfaces/Notificable.h"
#include "server/ConnectionHandler.h"
#include "server/WorldHandler.h"
#include "server/TCPAcceptor.h"
#include "Inicializador.h"

class Fabrica;

class Servidor: public Notificable {
public:

	// Instancia principal del programa.
	Servidor();
	virtual ~Servidor();

	// Ejecuta el programa.
	void ejecutar(int argc, char** argv);

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

private:

	// Carga los parametros necesarios para la ejecucion del servidor, e inicializa los
	// modulos que necesiten inicializacion.
	bool inicializar(int argc, char** argv);

	// Libera memoria y realiza las acciones necesarias para cerrar en un estado valido.
	void limpiar();

	Notificador * notificador;
	ServicioInformacion * informacion;
	TCPAcceptor * aceptorConexiones;
	Inicializador * inicializador;
	ControladorJuego * controlador;
	Fabrica * fabrica;
	bool salir;
};

#endif /* SERVIDOR_H_ */
