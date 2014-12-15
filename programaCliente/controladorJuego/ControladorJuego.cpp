/*
 * ControladorJuego.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "ControladorJuego.h"

#include "estadoJuego/Jugador.h"
#include "modeloJuego/ObjetoModelo.h"

// Crea un controlador de juego.
ControladorJuego::ControladorJuego(){

}

// Destruye el controlador de juego.
ControladorJuego::~ControladorJuego(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void ControladorJuego::notificar(tipo_notificacion_t notificacion){

}

// Establece los valores iniciales y configura los modulos que conforman
// el controlador.
void ControladorJuego::inicializar(){

	estado.inicializar();
	modelo.inicializar();
}

// Actualiza el juego.
void ControladorJuego::actualizar(){

	modelo.actualizar();
	estado.actualizar();
}

// Destruye el modelo y el estado de juego para asegurar un correcto finalizado
// de los modulos involucrados.
void ControladorJuego::limpiar(){

	estado.limpiar();
	modelo.limpiar();
}

// Aplica una modificacion al estado del juego.
void ControladorJuego::aplicar(Jugador * modificacion){

	bool deboInicializar = false;

	// Actualiza el estado global del juego: jugando o esperando conexiones.
	//estado.estado = modificacion->estadoJuego;

	// Actualiza el estado del jugador a modificar.
	Jugador * jugadorModificado = estado.jugadores[modificacion->numero - 1];

	// Si el estado de la modificacion indica que no existe, se debe eliminar el
	// jugador.
	if (modificacion->estado == Jugador::NOEXISTE) {
		jugadorModificado->estado = Jugador::NOEXISTE;
		return;
	}

	// Si el estado anterior es NOEXISTE, quiere decir que debe inicializar al
	// jugador luego de cargar sus datos.
	if (jugadorModificado->estado == Jugador::NOEXISTE) deboInicializar = true;

	// Carga los nuevo datos del jugador.
	jugadorModificado->numero = modificacion->numero;
	jugadorModificado->nombre = modificacion->nombre;
	jugadorModificado->vidas = modificacion->vidas;
	jugadorModificado->puntaje = modificacion->puntaje;
	jugadorModificado->estado= modificacion->estado;

	// Inicializa al jugador si es necesario.
	if (deboInicializar) jugadorModificado->inicializar();

	// Actualiza.
	jugadorModificado->actualizar();

	modificacion->limpiar();
	delete modificacion;
}

// Aplica una modificacion al modelo de juego.
void ControladorJuego::aplicar(ObjetoModelo * modificacion){

	// Verifico si existe el objeto, o es un objeto nuevo en el modelo.
	if( modelo.existeObjeto(modificacion->ID) ) {
		if (modificacion->paraDestruir){
			modelo.destruirObjeto(modificacion);
		}
		else modelo.modificarObjeto(modificacion);
	}
	else if (!modificacion->paraDestruir){
		std::cout << "cree un objeto de ID: " << modificacion->ID << std::endl;
		modelo.agregarObjeto(modificacion);
	}

}

// Dibuja el juego en pantalla.
void ControladorJuego::dibujar(){

	modelo.dibujar();
	estado.dibujar();
}


// Verifica si los jugadores ganaron la partida actual.
bool ControladorJuego::ganaron(){

	for(int i = 0; i < 4; i++){
		if(estado.jugadores[i]->estado == Jugador::NOEXISTE) continue;
		if(estado.jugadores[i]->estado == Jugador::DESCONECTADO) continue;
		if (estado.jugadores[i]->vidas > 0) return true;
	}

	return false;
}
