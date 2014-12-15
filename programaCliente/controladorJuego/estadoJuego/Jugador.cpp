/*
 * Jugador.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: rodrizapico
 */

#include "Jugador.h"

#include "../ControladorJuego.h"

// Crea un nuevo jugador.
Jugador::Jugador(){
	estadoJuego = ESPERANDOCONEXIONES;
	numero = 0;
	puntaje = 0;
	estado = NOEXISTE;
	vidas = 0;
	nombreGUI = NULL;
	vidasGUI = NULL;
	puntajeGUI = NULL;
	corazonGUI = NULL;
}

// Destruye un jugador.
Jugador::~Jugador(){

}

// Crea un jugador nuevo en base a los datos serializados.
Jugador * Jugador::deserializar(std::string serializado){

	Jugador * jugador = new Jugador;

	// Separa el los campos del mensaje.
	std::vector<std::string> buff;
	split(buff, serializado, SEPARADORDATOS, no_empties);

	// Salteo buff[0] pues dice TIPOJUGADOR.
	jugador->nombre = buff[1];
	jugador->numero = atoi(buff[2].c_str());
	jugador->vidas = atoi(buff[3].c_str());
	jugador->puntaje = atoi(buff[4].c_str());
	jugador->estado = (estado_t) atoi(buff[5].c_str());
	jugador->estadoJuego = (estado_juego_t) atoi(buff[6].c_str());

	return jugador;
}

// Serializa la informacion de un jugador para su almacenamiento.
std::string Jugador::serializar(){

	std::string buff;

	buff = SSTR(TIPOJUGADOR << SEPARADORDATOS << nombre << SEPARADORDATOS << numero << SEPARADORDATOS << vidas
			<< SEPARADORDATOS << puntaje << SEPARADORDATOS << estado << SEPARADORDATOS << estadoJuego);

	return buff;
}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void Jugador::notificar(tipo_notificacion_t notificacion){

}

// Inicializa al jugador.
void Jugador::inicializar(){

	// Obtiene el posicionador y setea la variable 'indicadora' para que pueda identificar
	// que elemento debe posicionar.
	ServicioPosicionador * posicionador = LocalizadorDeServicios::obtenerPosicionador();
	ServicioPosicionador::tipo_objeto_t tipo;
	tipo.numero = numero;

	// Inicializa el nombre.
	nombreGUI = new TextoGUI;

	// Obtiene la posicion asignada por el posicionador de objetos.
	tipo.tipo = ServicioPosicionador::NOMBREJUGADOR;
	posicionador->posicionar(nombreGUI, tipo);
	nombreGUI->asignarEstilo(ESTADOJUGADOR);

	// Idem vidas.
	vidasGUI = new TextoGUI;
	tipo.tipo = ServicioPosicionador::VIDASJUGADOR;
	posicionador->posicionar(vidasGUI, tipo);
	vidasGUI->asignarEstilo(ESTADOJUGADOR);

	// Idem puntaje.
	puntajeGUI = new TextoGUI;
	tipo.tipo = ServicioPosicionador::PUNTAJEJUGADOR;
	posicionador->posicionar(puntajeGUI, tipo);
	puntajeGUI->asignarEstilo(ESTADOJUGADOR);

	// Idem corazon.
	corazonGUI = new ImagenEstaticaGUI;
	tipo.tipo = ServicioPosicionador::CORAZONJUGADOR;
	posicionador->posicionar(corazonGUI, tipo);
}

// Elimina lo que sea necesario.
void Jugador::limpiar(){

	delete nombreGUI;
	delete vidasGUI;
	delete puntajeGUI;
	delete corazonGUI;
}

// Actualiza la informacion del jugador para poder dibujarla.
void Jugador::actualizar(){
	nombreGUI->reemplazarTexto(nombre);

	std::string textoVidas = SSTR("   Vidas: " << vidas);
	vidasGUI->reemplazarTexto(textoVidas);

	std::string textoPuntaje = SSTR("Puntaje: " << puntaje);
	puntajeGUI->reemplazarTexto(textoPuntaje);
}

// Dibuja la informacion del jugador.
void Jugador::dibujar(){

	// TODO: tener en cuenta el estado. Capaz grisar el nombre si esta
	// desconectado?
	nombreGUI->dibujar();
	vidasGUI->dibujar();
	puntajeGUI->dibujar();
}

// Aplica una modificacion.
void Jugador::aplicarModificacion(ControladorJuego * juego){
	juego->aplicar(this);
}
