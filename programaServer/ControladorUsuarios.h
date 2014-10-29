/*
 * ControladorUsuarios.h
 *
 *  Created on: Oct 26, 2014
 *      Author: rodrizapico
 */

#ifndef CONTROLADORUSUARIOS_H_
#define CONTROLADORUSUARIOS_H_

#include <map>
#include "Usuario.h"

class ControladorUsuarios: public map <std::string, Usuario*> {
public:
	ControladorUsuarios();
	virtual ~ControladorUsuarios();

	// Agrega un nuevo usuario a los registrados en el servidor.
	// username: el nombre de usuario a registrar.
	// retorno: true si tuvo exito el registro, false si hubo algun error.
	bool registrarUsuario(std::string username);

	// Verifica si el usuario requerido ya se encuentra registrado.
	// username: el nombre de usuario a verificar.
	// retorno: true si el usuario ya se encuentra registrado, false en caso contrario.
	bool usuarioExiste(std::string username);

	// Determina el ID de usuario.
	// username: el usuario del cual se quiere obtener su ID.
	// return: ID del usuario si este existe, NULL en otro caso.
	Usuario * obtenerUsuario(std::string username);

	// Determina si queda lugar en el escenario para que ingresen nuevos usuarios.
	// return: true si no pueden ingresar mas usuarios, false si aun hay lugar.
	bool escenarioLleno();

	// Obtiene una version serializada de lo que se ve en pantalla del usuario
	// pedido, para ser enviada al cliente para renderear.
	// username:el nombre de usuario para el que se quiere obtener la pantalla
	// serializada.
	// return: la pantalla serializada para username.
	std::string obtenerPantallaSerializada(std::string username);

private:
	unsigned int tamanioMaximo;
};

#endif /* CONTROLADORUSUARIOS_H_ */
