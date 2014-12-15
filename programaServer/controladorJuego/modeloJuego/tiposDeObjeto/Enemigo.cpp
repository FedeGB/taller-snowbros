/*
 * Enemigo.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: rodrizapico
 */

#include "Enemigo.h"
#include "../../../servicios/ServicioFabricaDeObjetos.h"

Enemigo::Enemigo() {
	salud = 10;
	fuePateado = false;
}

// Levanta el personaje desde el archivo de configuracion Json.
Enemigo::Enemigo(std::string sConfig, int numeroObjeto): SerVivo(sConfig, numeroObjeto){
	salud = 10;
	fuePateado = false;
};

Enemigo::~Enemigo() {
	reconocerDestruccion = 0;
}

// Indica que el enemigo fue pateado.
void Enemigo::patear(){

	fuePateado = true;
}


bool Enemigo::isObjectInDirection(b2World* world, Enemigo * unit, sensor_t obj, float angle, float length) {
	b2Vec2 p1 = b2Vec2(unit->espacioOcupado->calcularBaricentro().x, unit->espacioOcupado->calcularBaricentro().y);
	b2Vec2 p2 =  p1 + b2Vec2(length * sinf(angle*DEGTORAD), length * cosf(angle*DEGTORAD) );
	RayCaster caster;
	world->RayCast(&caster, p1, p2);
	if(caster.m_fixture) {
		void* fixData = caster.m_fixture->GetUserData();
		if(fixData && *((int*)(&fixData)) == obj) {
			if(obj == PERSONAJE || obj == PIESPJ) {
				if(((Personaje*)(caster.m_fixture->GetBody()->GetUserData()))->salud > 0) {
					return true;
				} else {
					return false;
				}
			} else {
				return true;
			}
		}
	}
	return false;
}


// El enemigo se mueve semialeatoriamente, hasta encontrar a un personaje para seguir.
void Enemigo::deambular(){

	// Romear
	if(moviendoDerecha) {
		if((isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ATRAVESABLE, 0, 4) && !isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ATRAVESABLE, 15, 7)) ) {
			if(numContactosPie == 0) {
				moviendoDerecha = true;
				moviendoIzquierda = false;
				saltando = false;
				return;
			} else {
				moviendoDerecha = false;
				moviendoIzquierda = false;
				saltando = true;
				return;
			}
		}
		if(numContactosPie > 0 && (isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ESTATICO, 90, 3.5) || isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ATRAVESABLE, 90, 3.5)) ) {
			moviendoDerecha = false;
			moviendoIzquierda = true;
			saltando = false;
			return;
		}
		moviendoDerecha = true;
		moviendoIzquierda = false;
		saltando = false;
		return;
	}
	if(moviendoIzquierda) {
		if(isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ATRAVESABLE, 0, 4) && !isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ATRAVESABLE, 345, 7)) {
			if(numContactosPie == 0) {
				moviendoDerecha = false;
				moviendoIzquierda = true;
				saltando = false;
				return;
			} else {
				moviendoDerecha = false;
				moviendoIzquierda = false;
				saltando = true;
				return;
			}
		}
		if(numContactosPie > 0 && (isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ESTATICO, 270, 3.5) || isObjectInDirection(this->cuerpoB2D->GetWorld(), this, ATRAVESABLE, 270, 3.5)) ) {
			moviendoDerecha = true;
			moviendoIzquierda = false;
			saltando = false;
			return;
		}
		moviendoDerecha = false;
		moviendoIzquierda = true;
		saltando = false;
		return;
	}

	int numero = rand();
	if(numero%2 == 0) {
		moviendoIzquierda = true;
		moviendoDerecha = false;
	}else {
		moviendoIzquierda = false;
		moviendoDerecha = true;
	}
}

// Actualiza la informacion del objeto para poder dibujarlo.
void Enemigo::actualizar(Personaje * pj){

	// Actualiza la posicion y rotacion.
	SerVivo::actualizar();

	estado = PARADO;

	// Ataque.
	// TODO: HARDCODEOS FOR EVERYONE.
	const float SALUDINICIAL = 10, REGEN_RATE = 0.01;

	// Chequea si fue daniado.
	if (salud < SALUDINICIAL){
		salud+= REGEN_RATE;
		estado = ATRAPADO;

		// Actualizo el estado en la representacion B2D a congelado.
		for(b2Fixture * fix= cuerpoB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
			void * userData =fix->GetUserData();
			if(*((int*)(&userData))==ENEMIGO || *((int*)(&userData))==ENEMIGOBOLA) fix->SetUserData((void*)ENEMIGOCONGELADO);
			if(*((int*)(&userData))==PIESEN || *((int*)(&userData))==PIESENBOLA) fix->SetUserData((void*)PIESENCONGELADO);
		}
	} else { // No lo fue.
		// Actualizo el estado en la representacion B2D a libre.
		for(b2Fixture * fix= cuerpoB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
			void * userData =fix->GetUserData();
			if(*((int*)(&userData))==ENEMIGOCONGELADO || *((int*)(&userData))==ENEMIGOBOLA) fix->SetUserData((void*)ENEMIGO);
			if(*((int*)(&userData))==PIESENCONGELADO || *((int*)(&userData))==PIESENBOLA) fix->SetUserData((void*)PIESEN);
		}
	}

	// Chequea si es una bola.
	if (salud < -5 && !paraDestruir){
		if (fuePateado){
			paraDestruir = true;
			LocalizadorDeServicios::obtenerFabricaDeObjetos()->fabricarPelotaDeNieve(this);
		} else {
			// Actualizo el estado en la representacion B2D a cubierto completamente.
			for(b2Fixture * fix= cuerpoB2D->GetFixtureList();fix!=NULL;fix=fix->GetNext()){
				void * userData =fix->GetUserData();
				if(*((int*)(&userData))==ENEMIGOCONGELADO) fix->SetUserData((void*)ENEMIGOBOLA);
				if(*((int*)(&userData))==PIESENCONGELADO) fix->SetUserData((void*)PIESENBOLA);
			}
		}

	}


	if (salud < SALUDINICIAL) return;


	if (!pj){
		deambular();
		return;
	}

	Vector2D posicionEnemigo = espacioOcupado->calcularBaricentro();
	Vector2D posicionPJ = pj->espacioOcupado->calcularBaricentro();
	Vector2D diferencia = posicionEnemigo - posicionPJ;
	//float moduloCuadradoDiferencia = diferencia.moduloCuadrado();

	if(diferencia.y > 0.5) {
		if(isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 180, 8)) {
			moviendoDerecha = false;
			moviendoIzquierda = false;
			saltando = true;
			return;
		}
	} else if (diferencia.y < -0.5) {
		if(isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 0, 4)) {
			moviendoDerecha = false;
			moviendoIzquierda = true;
			saltando = false;
			return;
		}
	} else {
		if(diferencia.x < 0) {
			if(numContactosPie > 0 && (isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 90, 3.5) || isObjectInDirection(cuerpoB2D->GetWorld(), this, ESTATICO, 90, 3.5)) ) {
				moviendoDerecha = false;
				moviendoIzquierda = true;
				saltando = false;
				return;
			}
			if(isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 0, 3.5) && !isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 15, 7)) {
				if(numContactosPie == 0) {
					moviendoDerecha = true;
					moviendoIzquierda = false;
					saltando = false;
					return;
				} else {
					moviendoDerecha = false;
					moviendoIzquierda = false;
					saltando = true;
					return;
				}
			}
			moviendoDerecha = true;
			moviendoIzquierda = false;
			saltando = false;
			return;
		}
		else {
			if(numContactosPie > 0 && ( isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 270, 3.5) || isObjectInDirection(cuerpoB2D->GetWorld(), this, ESTATICO, 270, 3.5)) ) {
				moviendoDerecha = true;
				moviendoIzquierda = false;
				saltando = false;
				return;
			}
			if(isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 0, 3.5) && !isObjectInDirection(cuerpoB2D->GetWorld(), this, ATRAVESABLE, 345, 7)) {
				if(numContactosPie == 0) {
					moviendoDerecha = false;
					moviendoIzquierda = true;
					saltando = false;
					return;
				} else {
					moviendoDerecha = false;
					moviendoIzquierda = false;
					saltando = true;
					return;
				}
			}
			moviendoDerecha = false;
			moviendoIzquierda = true;
			saltando = false;
			return;
		}
	}

}
