/*
 * Personaje.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "Personaje.h"
#include "../../../servicios/ServicioFabricaDeObjetos.h"
#include "../../../server/ConnectionHandler.h"
#include "PelotaDeNieve.h"

// Representacion de un personaje controlado por el usuario.
Personaje::Personaje(){

	rotacion = 0.0f;
	orientacion = IZQUIERDA;
	estado = PARADO;
	inicializado = false;
	puedePatear = false;
	enemigoParaEmpujar = NULL;
	murio = false;
	inmune = false;
	acumuladorInmunidad = 0;
	acabaDePatear = atrapado = false;
	acumuladorInmunidadPatada = 0;
	pelota = NULL;
	puntaje = 0;
	acumuladorMuerte = 0;
	sorpresaNievePotenteActiva = sorpresaNieveLejosActiva = sorpresaCorrerActiva = false;
	acumuladorPotente = acumuladorLejos = acumuladorCorrer = 0;

	moviendoIzquierda = moviendoDerecha = false;
	saltando = false;
	atacando = false;
	numContactosPie = 0;
	comenzoAtaque = false;
	acumuladorAtaque = 0;
	salud = 3;
	cayoPorAgujero = false;
}

// Levanta el personaje desde el archivo de configuracion Json.
Personaje::Personaje(std::string sConfig, int numeroObjeto): SerVivo(sConfig, numeroObjeto){

	rotacion = 0.0f;
	orientacion = IZQUIERDA;
	estado = PARADO;
	inicializado = false;
	puedePatear = false;
	enemigoParaEmpujar = NULL;
	murio = false;
	inmune = false;
	acumuladorInmunidad = 0;
	acabaDePatear = atrapado = false;
	acumuladorInmunidadPatada = 0;
	pelota = NULL;
	puntaje = 0;
	acumuladorMuerte = 0;
	sorpresaNievePotenteActiva = sorpresaNieveLejosActiva = sorpresaCorrerActiva = false;
	acumuladorPotente = acumuladorLejos = acumuladorCorrer = 0;

	moviendoIzquierda = moviendoDerecha = false;
	saltando = false;
	atacando = false;
	numContactosPie = 0;
	comenzoAtaque = false;
	acumuladorAtaque = 0;
	salud = 3;
}

Personaje::~Personaje(){

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void Personaje::notificar(tipo_notificacion_t notificacion){}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void Personaje::notificar(tipo_notificacion_t notificacion, EnviadorNotificaciones * origen){

	if( ((ConnectionHandler*)origen)->username != nombre ) return;

	if (notificacion == MOVERPERSONAJEIZQUIERDA){
		moviendoIzquierda = true;
		moviendoDerecha = false;
	}

	if (notificacion == MOVERPERSONAJEDERECHA){
		moviendoDerecha = true;
		moviendoIzquierda = false;
	}

	if (notificacion == DETENERMOVIMIENTOPERSONAJE){
		moviendoIzquierda = false;
		moviendoDerecha = false;
	}

	if (notificacion == MOVERPERSONAJESALTO){
		saltando = true;
	}

	if (notificacion == DETENERMOVIMIENTOPERSONAJESALTO){
		saltando = false;
	}

	if (notificacion == MOVERPERSONAJEATAQUE){
		atacando = true;
	}

	if (notificacion == DETENERMOVIMIENTOPERSONAJEATAQUE){
		atacando = false;
	}

}

// Serializa la informacion de un elemento del modelo para su almacenamiento.
std::string Personaje::serializar(){

	std::string buff;

	buff = SSTR(TIPOPERSONAJE << SEPARADORDATOS << orientacion << SEPARADORDATOS << rotacion);
	buff += SSTR(SEPARADORDATOS << nombre << SEPARADORDATOS << estado << SEPARADORDATOS << inmune
			<< SEPARADORDATOS << murio << SEPARADORDATOS << espacioOcupado->numeroVertices());

	// Serializa los puntos del objeto.
	for(std::list<Vector2D>::iterator it = espacioOcupado->puntosOrdenados.begin();
			it != espacioOcupado->puntosOrdenados.end(); it++){
		buff += SSTR ( SEPARADORDATOS << (*it).x << SEPARADORDATOS << (*it).y);
	}

	buff += SSTR( SEPARADORDATOS << paraDestruir << SEPARADORDATOS << ID);

	return buff;
}

// Inicializa al objeto.
void Personaje::inicializar(){
	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);
	inicializado = true;
}

// Elimina lo que sea necesario.
void Personaje::limpiar(){
	ObjetoModelo::limpiar();
	if (!inicializado) return;
	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);
}

// Aplica el danio indicado.
void Personaje::aplicarDanio(float danio){

	if (inmune || murio) return;

	salud -= danio;
	murio = true;
}

// Atrapa al personaje en una pelota.
void Personaje::atraparEnPelota(PelotaDeNieve * p){

	// Si acaba de patear, es inmune a ser atrapado.
	if(acabaDePatear) return;

	// En caso contrario, queda atrapado en la pelota.
	atrapado = true;
	pelota = p;
}

// Libera al personaje de una pelota.
void Personaje::liberarDePelota(){
	atrapado = false;
	estado = PARADO;
	pelota = NULL;
	//cuerpoB2D->SetActive(true);
}

// Actualiza la informacion del objeto para poder dibujarlo.
void Personaje::actualizar(){

	// Actualiza la posicion y rotacion.
	SerVivo::actualizar();

	// Chequea sorpresas.
	if(sorpresaNievePotenteActiva) {
		acumuladorPotente++;
		if (acumuladorPotente == 2000) sorpresaNievePotenteActiva = false;
	} else acumuladorPotente = 0;

	if(sorpresaNieveLejosActiva) {
		acumuladorLejos++;
		if (acumuladorLejos == 2000) sorpresaNieveLejosActiva = false;
	} else acumuladorLejos = 0;

	if(sorpresaCorrerActiva) {
		acumuladorCorrer++;
		if (acumuladorCorrer == 2000) sorpresaCorrerActiva = false;
	} else acumuladorCorrer = 0;

	// Chequea si murio.
	if (murio){
		acumuladorMuerte++;
		if (acumuladorMuerte == 50){
			inmune = true;
			b2Vec2 pos; pos.x = posicionInicial.x; pos.y = posicionInicial.y;
			cuerpoB2D->SetTransform(pos, 0);
			murio = false;
		}
	} else acumuladorMuerte = 0;

	// Chequea si se encuentra en su periodo de inmunidad.
	if (inmune) {
		acumuladorInmunidad++;
		if (acumuladorInmunidad > 100) inmune = false;
	}
	else acumuladorInmunidad = 0;

	// Ataque.
	if(atacando || comenzoAtaque){

		estado = ATACANDO;

		// Verifica si puede patear a algun enemigo.
		if (puedePatear) {
			enemigoParaEmpujar->patear();
			puntaje += 10;
			acabaDePatear = true;
			acumuladorInmunidadPatada = 12;
			return;
		}

		// Sino, ataca.
		comenzoAtaque = true;
		if ( (acumuladorAtaque % 35) == 29) {
			LocalizadorDeServicios::obtenerFabricaDeObjetos()->fabricarBolaDeNieve(this);
			comenzoAtaque = false;
		}

		acumuladorAtaque++;
	} else acumuladorAtaque = 0;

	if (acabaDePatear) {
		if (acumuladorInmunidadPatada == 0) acabaDePatear = false;
		acumuladorInmunidadPatada--;
	}
	else acumuladorInmunidadPatada = 0;

	if (atrapado) {
		estado = ATRAPADO;
		b2Vec2 pos; pos.x = -1000; pos.y = -100;
		cuerpoB2D->SetTransform(pos, 0);

		Vector2D posicionAnterior = espacioOcupado->calcularBaricentro();
		Vector2D posicionActual;
		posicionActual.x = pelota->cuerpoB2D->GetPosition().x;
		posicionActual.y = pelota->cuerpoB2D->GetPosition().y;

		espacioOcupado->trasladar(posicionActual - posicionAnterior);
	}
}
