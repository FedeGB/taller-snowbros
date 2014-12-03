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

	// Indica que la partida actual ha finalizado.
	bool finDePartida;
	resultado_t resultadoPartida;

	// Asigna un numero de usuario.
	int asignarNumeroUsuario();

	// Agrega un nuevo usuario a los registrados en el servidor.
	// username: el nombre de usuario a registrar.
	// retorno: true si tuvo exito el registro, false si hubo algun error.
	bool registrarUsuario(std::string username);

	// Elimina el usuario solicitado.
	// username: el usuario al cual se quiere eliminar.
	void eliminarUsuario(std::string username);

	// Devuelve el numero de conexion correspondiente al usuario solicitado,
	// asignado por orden de su primera conexion.
	int numeroUsuario(std::string username);

	// Verifica si el usuario requerido ya se encuentra registrado.
	// username: el nombre de usuario a verificar.
	// retorno: true si el usuario ya se encuentra registrado, false en caso contrario.
	bool usuarioExiste(std::string username);

	// Confirma que el usuario en cuestion va a jugar la siguiente partida.
	void confirmarUsuario(std::string, estado_user_t estado);

	// Determina el ID de usuario.
	// username: el usuario del cual se quiere obtener su ID.
	// return: ID del usuario si este existe, NULL en otro caso.
	Usuario * obtenerUsuario(std::string username);

	// Determina si queda lugar en el escenario para que ingresen nuevos usuarios.
	// return: true si no pueden ingresar mas usuarios, false si aun hay lugar.
	bool escenarioLleno();

	// Notifica a todos los jugadores conectados que el juego finalizo, informando el resultado
	// de la partida. Ademas, inicia el protocolo para mantenerlos conectados a una nueva partida,
	// o desconectarlos en caso que no quieran jugar nuevamente.
	void notificarFinDePartida(resultado_t resultado);

	//setea el maximo de conecciones permitidas
	void setConnectionLimit(int max);

	// Obtiene una version serializada de lo que se ve en pantalla del usuario
	// pedido, para ser enviada al cliente para renderear.
	// username:el nombre de usuario para el que se quiere obtener la pantalla
	// serializada.
	// return: la pantalla serializada para username.
	std::string obtenerPantallaSerializada(std::string username);

	void sumarPuntaje(int);

private:

	estado_user_t usuariosRegistrados[4];
	unsigned int tamanioMaximo;
	long int puntajeKills;
};

#endif /* CONTROLADORUSUARIOS_H_ */
