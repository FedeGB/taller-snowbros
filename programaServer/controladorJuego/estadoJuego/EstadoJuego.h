/*
 * EstadoJuego.h
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#ifndef ESTADOJUEGO_H_
#define ESTADOJUEGO_H_

#include <vector>
#include <cstddef>
#include "../../interfaces/Notificable.h"
#include "../../utiles/tipos.h"

class Jugador;

class EstadoJuego: public Notificable {
public:

	// Representacion del estado del juego actual: jugadores conectados, vidas
	// de cada jugador, puntaje, etcetera.
	EstadoJuego();

	// Destruye la representacion del estado de juego.
	virtual ~EstadoJuego();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Inicializa el estado del juego.
	void inicializar();

	// Actualiza el estado del juego.
	void actualizar();

	// Destruye el estado de juego para asegurar un correcto finalizado
	// de los modulos involucrados.
	void limpiar();

	// Cambia el estado actual del juego al indicado.
	void cambiarEstado(estado_juego_t estado);

	// Agrega un nuevo jugador a los registrados en el servidor.
	// username: el nombre de jugador a registrar.
	// retorno: true si tuvo exito el registro, false si hubo algun error.
	bool registrarJugador(std::string username);

	// Elimina el jugador solicitado.
	// numeroJugador: el jugador al cual se quiere eliminar.
	void eliminarJugador(int numeroJugador);

	// Elimina el jugador solicitado.
	// username: el jugador al cual se quiere eliminar.
	void eliminarJugador(std::string username);

	// Devuelve el numero de conexion correspondiente al jugador solicitado,
	// asignado por orden de su primera conexion.
	int numeroJugador(std::string username);

	// Verifica si el jugador requerido ya se encuentra registrado.
	// username: el nombre de jugador a verificar.
	// retorno: true si el jugador ya se encuentra registrado, false en caso contrario.
	bool jugadorExiste(std::string username);

	// Verifica si el jugador requerido ya se encuentra registrado.
	// numeroJugador: el nombre de jugador a verificar.
	// retorno: true si el jugador ya se encuentra registrado, false en caso contrario.
	bool jugadorExiste(int numeroJugador);

	// Devuelve un jugador que no haya sido vinculado aun con un personaje.
	Jugador * obtenerJugadorSinPersonaje();

	// Confirma que el usuario en cuestion va a jugar la siguiente partida.
	//void confirmarUsuario(std::string, estado_user_t estado);

	// Determina el jugador pedido.
	// username: el jugador que se desea recuperar.
	// return: jugador si este existe, NULL en otro caso.
	Jugador * obtenerJugador(std::string username);

	// Determina el jugador pedido.
	// numeroJugador: el jugador que se desea recuperar.
	// return: jugador si este existe, NULL en otro caso.
	Jugador * obtenerJugador(int numeroJugador);

	// Determina si queda lugar en el escenario para que ingresen nuevos jugadores.
	// return: true si no pueden ingresar mas jugadores, false si aun hay lugar.
	bool escenarioLleno();

	// Determina si se puede empezar la partida o nivel, de acuerdo al estado actual
	// del juego y la cantidad de usuarios conectados.
	bool puedeEmpezar();

	// Determina la cantidad de jugadores conectados.
	int cantidadOnline();

	friend class ControladorJuego;

	estado_juego_t estado;

private:

	// Asigna un numero de jugador.
	int asignarNumeroJugador();

	//estado_user_t jugadoresRegistrados[4];
	std::vector<Jugador*> jugadores;
};

#endif /* ESTADOJUEGO_H_ */
