/*
 * EstadoJuego.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "EstadoJuego.h"

#include "Jugador.h"
#include "../../Inicializador.h"

// Representacion del estado del juego actual: jugadores conectados, vidas
// de cada jugador, puntaje, etcetera.
EstadoJuego::EstadoJuego(){
	estado = ESPERANDOCONEXIONES;
}

// Destruye la representacion del estado de juego.
EstadoJuego::~EstadoJuego(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void EstadoJuego::notificar(tipo_notificacion_t notificacion){

}

// Inicializa el estado del juego.
void EstadoJuego::inicializar(){

	// Reserva memoria para los 4 jugadores (como maximo).
	jugadores.reserve(4);

	// Inicializa los 4 jugadores.
	for(int i = 0; i < 4; i++){
		Jugador * jugadorTemp = new Jugador();
		jugadores[i] = jugadorTemp;
	}
}

// Actualiza el estado del juego.
void EstadoJuego::actualizar(){

	// Actualiza los 4 jugadores.
	for(int i = 0; i < 4; i++) {
		if (jugadores[i]->estado == Jugador::CONECTADO) {
			jugadores[i]->actualizar();
		} else if (jugadores[i]->estado == Jugador::DESCONECTADO && jugadores[i]->vidas > 0) {
			if(!jugadores[i]->personaje->inmune) jugadores[i]->personaje->inmune = true;
		}
	}

}

// Destruye el estado de juego para asegurar un correcto finalizado
// de los modulos involucrados.
void EstadoJuego::limpiar(){

	// Inicializa los 4 jugadores.
	for(int i = 0; i < 4; i++){
		jugadores[i]->limpiar();
		delete jugadores[i];
		jugadores[i] = NULL;
	}
}

// Asigna un numero de jugador.
int EstadoJuego::asignarNumeroJugador(){

	for (int i = 0; i < 4; i++)
		if (jugadores[i]->estado == Jugador::NOEXISTE) return i + 1;

	return -1;
}

// Carga el numero de jugadores del archivo de configuracion en la informacion publica, y
// ademas lo devuelve para utilizarlo en la iteracion actual.
int cargarNumJugadores(){

	std::string sConfig, configFile = LocalizadorDeServicios::obtenerInformacionPublica()->archivoConfiguracion;

	Inicializador::loadInitialValues(configFile, sConfig);

	// Obtiene la cantidad de jugadores
	int num = get_node("maxplayer", "escenario", sConfig, 2);
	LocalizadorDeServicios::obtenerInformacionPublica()->numJugadores = num;

	return num;
}

// Determina si queda lugar en el escenario para que ingresen nuevos jugadores.
// return: true si no pueden ingresar mas jugadores, false si aun hay lugar.
bool EstadoJuego::escenarioLleno(){

	uint numUsuarios = 0;
	for(int i = 0; i < 4; i++){
		if (jugadores[i]->estado == Jugador::ESPERANDORESPUESTA){
			return false;
		}
		if (jugadores[i]->estado == Jugador::DESCONECTADO) numUsuarios += 1;
		if (jugadores[i]->estado == Jugador::CONECTADO) numUsuarios += 1;
	}

	int maximoJugadores = LocalizadorDeServicios::obtenerInformacionPublica()->numJugadores;
	if (maximoJugadores == -1) maximoJugadores = cargarNumJugadores();
	return numUsuarios >= (uint)maximoJugadores ? true : false;
}

// Determina si se puede empezar la partida o nivel, de acuerdo al estado actual
// del juego y la cantidad de usuarios conectados.
bool EstadoJuego::puedeEmpezar(){

	uint numUsuarios = 0;
	for(int i = 0; i < 4; i++){
		if (jugadores[i]->estado == Jugador::ESPERANDORESPUESTA) return false;
		if (jugadores[i]->estado == Jugador::DESCONECTADO) numUsuarios += 1;
		if (jugadores[i]->estado == Jugador::CONECTADO) numUsuarios += 1;
	}

	int maximoJugadores = LocalizadorDeServicios::obtenerInformacionPublica()->numJugadores;
	if (maximoJugadores == -1) maximoJugadores = cargarNumJugadores();
	return numUsuarios >= (uint)maximoJugadores ? true : false;
}

// Determina la cantidad de jugadores conectados.
int EstadoJuego::cantidadOnline(){

	uint numUsuarios = 0;
	for(int i = 0; i < 4; i++){
		if (jugadores[i]->estado == Jugador::CONECTADO) numUsuarios += 1;
		//if (jugadores[i]->estado == Jugador::ESPERANDORESPUESTA) numUsuarios += 1;
	}

	return numUsuarios;
}

// Cambia el estado actual del juego al indicado.
void EstadoJuego::cambiarEstado(estado_juego_t e){

	// Asigna el nuevo estado.
	estado = e;

	// Verifica si tiene que hacer alguna accion adicional segun el estado indicado.
	switch (estado){

	case ESPERANDOCONEXIONES:
		break;
	case JUGANDO:
		break;
	case JUEGOTERMINADO:

		for(int i = 0; i < 4; i++){
			if (jugadores[i]->estado == Jugador::CONECTADO)	jugadores[i]->vidas = 3;
			if (jugadores[i]->estado == Jugador::ESPERANDORESPUESTA) jugadores[i]->puntaje = 0;
			if (jugadores[i]->estado == Jugador::ESPERANDORESPUESTA) jugadores[i]->vidas = 3;
		}

		// Break innecesario, quiero que entre al siguiente caso pues hace lo mismo.

	case NIVELTERMINADO:

		// Actualiza el estado de cada jugador: si esta conectado lo marca como esperando respuesta,
		// sino lo kickea.
		for(int i = 0; i < 4; i++){
			if (jugadores[i]->estado == Jugador::ESPERANDORESPUESTA && estado == NIVELTERMINADO)
				jugadores[i]->estado = Jugador::CONECTADO;
			else if (jugadores[i]->estado == Jugador::CONECTADO)
				jugadores[i]->estado = Jugador::ESPERANDORESPUESTA;
			else if (jugadores[i]->estado == Jugador::DESCONECTADO && estado == JUEGOTERMINADO)
				jugadores[i]->estado = Jugador::NOEXISTE;
			jugadores[i]->personaje = NULL;
		}
		break;
	}
}

// Agrega un nuevo jugador a los registrados en el servidor.
// username: el nombre de jugador a registrar.
// retorno: true si tuvo exito el registro, false si hubo algun error.
bool EstadoJuego::registrarJugador(std::string username){

	// Si no hay mas espacio, o el jugador ya existe, no se lo puede agregar.
	if (escenarioLleno() || jugadorExiste(username)) return false;

	int numeroUsuario = asignarNumeroJugador();

	// Determino el estado del jugador a agregar.
	Jugador * jugador = jugadores[numeroUsuario - 1];

	// TODO: sacar las vidas hardcodeadas.
	jugador->numero = numeroUsuario;
	jugador->nombre = username;
	jugador->vidas = 3;
	jugador->puntaje = 0;
	jugador->estado= Jugador::CONECTADO;
	jugador->personaje = NULL;

	// Inicializa al jugador.
	jugador->inicializar();

	return true;

}

// Elimina el jugador solicitado.
// numeroJugador: el jugador al cual se quiere eliminar.
void EstadoJuego::eliminarJugador(int numeroJugador){

	//if (!usuarioExiste(username)) return;
	jugadores[numeroJugador - 1]->estado = Jugador::NOEXISTE;
	jugadores[numeroJugador - 1]->personaje = NULL;
}

// Elimina el jugador solicitado.
// username: el jugador al cual se quiere eliminar.
void EstadoJuego::eliminarJugador(std::string username){

	//if (!usuarioExiste(username)) return;
	jugadores[numeroJugador(username) - 1]->estado = Jugador::NOEXISTE;
	jugadores[numeroJugador(username) - 1]->personaje = NULL;
}

// Devuelve el numero de conexion correspondiente al jugador solicitado,
// asignado por orden de su primera conexion.
int EstadoJuego::numeroJugador(std::string username){

	for (int i = 0; i < 4; i++)
		if (jugadores[i]->nombre == username) return i + 1;

	return -1;
}

// Verifica si el jugador requerido ya se encuentra registrado.
// username: el nombre de jugador a verificar.
// retorno: true si el jugador ya se encuentra registrado, false en caso contrario.
bool EstadoJuego::jugadorExiste(std::string username){

	for (int i = 0; i < 4; i++)
		if (jugadores[i]->estado != Jugador::NOEXISTE && jugadores[i]->nombre == username) return true;

	return false;
}

// Verifica si el jugador requerido ya se encuentra registrado.
// numeroJugador: el nombre de jugador a verificar.
// retorno: true si el jugador ya se encuentra registrado, false en caso contrario.
bool EstadoJuego::jugadorExiste(int numeroJugador){

	if (jugadores[numeroJugador - 1]->estado != Jugador::NOEXISTE) return true;

	return false;
}

// Devuelve un jugador que no haya sido vinculado aun con un personaje.
Jugador * EstadoJuego::obtenerJugadorSinPersonaje(){

	for (int i = 0; i < 4; i++)
		if (jugadores[i]->personaje == NULL && jugadores[i]->estado == Jugador::CONECTADO){
			return jugadores[i];
		}

	return NULL;
}

// Confirma que el usuario en cuestion va a jugar la siguiente partida.
//void confirmarUsuario(std::string, estado_user_t estado);

// Determina el jugador pedido.
// username: el jugador que se desea recuperar.
// return: jugador si este existe, NULL en otro caso.
Jugador * EstadoJuego::obtenerJugador(std::string username){

	for (int i = 0; i < 4; i++)
		if (jugadores[i]->nombre == username) return jugadores[i];

	return NULL;
}

// Determina el jugador pedido.
// numeroJugador: el jugador que se desea recuperar.
// return: jugador si este existe, NULL en otro caso.
Jugador * EstadoJuego::obtenerJugador(int numeroJugador){

	//if (jugadores[numeroJugador]->estado == Jugador::NOEXISTE) return NULL;

	return jugadores[numeroJugador - 1];
}
