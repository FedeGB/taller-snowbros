/*
 * ContactListener.h
 *
 *  Created on: Sep 20, 2014
 *      Author: rodrizapico
 */

#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_

#include <Box2D/Box2D.h>
#include "../controladorJuego/modeloJuego/tiposDeObjeto/SerVivo.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/Enemigo.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/BolaDeNieve.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/PelotaDeNieve.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/BolaDeFuego.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/Personaje.h"
#include "../controladorJuego/modeloJuego/tiposDeObjeto/Sorpresa.h"

class ContactListener : public b2ContactListener{

	void BeginContact(b2Contact* contact) {
		// Get Collision fixtures
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

		if ( *((int*)(&fixtureBUserData)) == BOLASNOW ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE ||*((int*)(&fixtureAUserData)) == PIESPJ  ){
				((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->atraparEnPelota((PelotaDeNieve*)contact->GetFixtureB()->GetBody()->GetUserData());
				((PelotaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData() )->atraparPersonaje((Personaje*)contact->GetFixtureA()->GetBody()->GetUserData());
			}
		}
		if ( *((int*)(&fixtureAUserData)) == BOLASNOW ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE ||*((int*)(&fixtureBUserData)) == PIESPJ  ){
				 ((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->atraparEnPelota((PelotaDeNieve*)contact->GetFixtureA()->GetBody()->GetUserData());
				 ((PelotaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData() )->atraparPersonaje((Personaje*)contact->GetFixtureB()->GetBody()->GetUserData());
			}
		}

		if ( *((int*)(&fixtureBUserData)) == BOLASNOW ){
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO ||*((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO ||*((int*)(&fixtureAUserData)) == ENEMIGOBOLA){
				((Enemigo*)contact->GetFixtureA()->GetBody()->GetUserData())->paraDestruir = true;
			}
		}

		if ( *((int*)(&fixtureAUserData)) == BOLASNOW){
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO ||*((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO ||*((int*)(&fixtureAUserData)) == ENEMIGOBOLA){
				((Enemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->paraDestruir = true;
			}
		}

		if ( *((int*)(&fixtureAUserData)) == EMPUJE ){
			if ( *((int*)(&fixtureBUserData)) == ENEMIGOBOLA ){
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->puedePatear = true;
				( (Enemigo *) contact->GetFixtureB()->GetBody()->GetUserData() )->orientacion = ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->orientacion;
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->enemigoParaEmpujar=( (Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData() );
			}
		}
		if ( *((int*)(&fixtureAUserData)) == ENEMIGOBOLA ){
			if ( *((int*)(&fixtureBUserData)) == EMPUJE ){
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->puedePatear = true;
				( (Enemigo *) contact->GetFixtureA()->GetBody()->GetUserData() )->orientacion = ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->orientacion;
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->enemigoParaEmpujar=( (Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData() );
			}
		}

		// Foot sensor collision for jump
		if ( *((int*)(&fixtureAUserData)) == PIESPJ || *((int*)(&fixtureAUserData)) == PIESEN ){
			if ( (*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO) && (*((int*)(&fixtureBUserData)) != sensorLAGUNA) && (*((int*)(&fixtureBUserData)) != BOLASNOW) && (*((int*)(&fixtureBUserData)) != sensorAGUJERO))
				( (SerVivo *) contact->GetFixtureA()->GetBody()->GetUserData() )->modificarContactosPie(1);
		}
		if ( *((int*)(&fixtureBUserData)) == PIESPJ || *((int*)(&fixtureBUserData)) == PIESEN ){
			if ( (*((int*)(&fixtureAUserData)) != CAMARA)&& (*((int*)(&fixtureAUserData)) != PODERHIELO) && (*((int*)(&fixtureAUserData)) != sensorLAGUNA)&& (*((int*)(&fixtureAUserData)) != BOLASNOW) && (*((int*)(&fixtureBUserData)) != sensorAGUJERO))
				( (SerVivo *) contact->GetFixtureB()->GetBody()->GetUserData() )->modificarContactosPie(1);
		}

		// Collision between PJ and Enemy, apply damage
		if( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->aplicarDanio(1);

			}
		}
		if( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == PIESEN ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
					( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->aplicarDanio(1);
			}
		}

		// Collision between Snowballs and Objects
		if( *((int*)(&fixtureBUserData)) == PODERHIELO ){
			if ( *((int*)(&fixtureAUserData)) == ESTATICO || *((int*)(&fixtureAUserData)) == ATRAVESABLE || *((int*)(&fixtureAUserData)) == DINAMICO ){
				((BolaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData())->paraDestruir = true;
			}
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO|| *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureAUserData)) == PIESEN ) {
				((Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData())->aplicarDanio(((BolaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData())->danio);
				((BolaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData())->paraDestruir = true;
			}
		}
		if( *((int*)(&fixtureAUserData)) == PODERHIELO ){
			if ( *((int*)(&fixtureBUserData)) == ESTATICO  || *((int*)(&fixtureBUserData)) == ATRAVESABLE || *((int*)(&fixtureBUserData)) == DINAMICO ) {
				((BolaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData())->paraDestruir = true;
			}
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureBUserData)) == PIESEN ) {
				((Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData())->aplicarDanio( ((BolaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData())->danio );
				((BolaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData())->paraDestruir = true;
			}
		}

		// Collision between Fireballs and Objects
		if( *((int*)(&fixtureBUserData)) == PODERFUEGO ){
			if ( *((int*)(&fixtureAUserData)) == ESTATICO || *((int*)(&fixtureAUserData)) == ATRAVESABLE || *((int*)(&fixtureAUserData)) == DINAMICO ){
				((BolaDeFuego*) contact->GetFixtureB()->GetBody()->GetUserData())->paraDestruir = true;
			}
			if ((*((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ)) {
				((BolaDeFuego*) contact->GetFixtureB()->GetBody()->GetUserData())->paraDestruir = true;
				if(((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0)
					((Personaje*) contact->GetFixtureA()->GetBody()->GetUserData())->aplicarDanio((((BolaDeFuego*) contact->GetFixtureB()->GetBody()->GetUserData())->danio));
			}
		}
		if( *((int*)(&fixtureAUserData)) == PODERFUEGO ){
			if ( *((int*)(&fixtureBUserData)) == ESTATICO  || *((int*)(&fixtureBUserData)) == ATRAVESABLE || *((int*)(&fixtureBUserData)) == DINAMICO ) {
				((BolaDeFuego*) contact->GetFixtureA()->GetBody()->GetUserData())->paraDestruir = true;
			}
			if ((*((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ)) {
				((BolaDeFuego*) contact->GetFixtureA()->GetBody()->GetUserData())->paraDestruir = true;
				if(((Personaje*) contact->GetFixtureB()->GetBody()->GetUserData())->salud > 0)
					((Personaje*) contact->GetFixtureB()->GetBody()->GetUserData())->aplicarDanio((((BolaDeFuego*) contact->GetFixtureA()->GetBody()->GetUserData())->danio));
			}
		}

		// colision entre las sorpresas y el pj
		if( *((int*)(&fixtureBUserData)) == sensorSORPRESA ){
			std::cout << "detecte el contacto con sorpresa" << std::endl;
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
				std::cout << "detecte el contacto PJ con sorpresa" << std::endl;
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0) {
					Sorpresa* sorpresa = (Sorpresa*) contact->GetFixtureB()->GetBody()->GetUserData();
					sorpresa->paraDestruir = true;
					sorpresa->aplicarAlPJ( ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() ) );
				}
			}
		}

		if( *((int*)(&fixtureAUserData)) == sensorSORPRESA ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				if(( (Personaje*) contact->GetFixtureB()->GetBody()->GetUserData() )->salud > 0) {
					std::cout << "detecte el contacto PJ con sorpresa" << std::endl;
					Sorpresa * sorpresa = (Sorpresa*) contact->GetFixtureA()->GetBody()->GetUserData();
					sorpresa->paraDestruir = true;
					sorpresa->aplicarAlPJ( ( (Personaje*) contact->GetFixtureB()->GetBody()->GetUserData() ) );
				}
			}
		}

		// colision entre las lagunas y el pj
		if( *((int*)(&fixtureBUserData)) == sensorLAGUNA ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0 &&
						!((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido) {
					( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido = true;
				}
			}
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGOBOLA) {
				if(( (Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0 &&
						!((Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido) {
					( (Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido = true;
				}
			}
		}

		if( *((int*)(&fixtureAUserData)) == sensorLAGUNA ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE ) {
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->salud > 0 &&
						!((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido ) {
					( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido = true;
				}
			}
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA) {
				if(( (Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData() )->salud > 0 &&
						!((Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido) {
					( (Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido = true;
				}
			}
		}

		// colision entre los agujero y el pj
		if( *((int*)(&fixtureBUserData)) == sensorAGUJERO ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0 ){
					((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->cayoPorAgujero = true;
				}
			}
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO|| *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureAUserData)) == PIESEN || *((int*)(&fixtureAUserData)) == PIESENCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGOBOLA) {
				((Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureAUserData)) == PODERHIELO ){
				((BolaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureAUserData)) == PODERFUEGO ){
				((BolaDeFuego*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureAUserData)) == BOLASNOW ){
				std::cout << "detecte que la bola cayo" << std::endl;
				((PelotaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureAUserData)) == DINAMICO ){
				((ObjetoModelo*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
		}

		if( *((int*)(&fixtureAUserData)) == sensorAGUJERO ){
			std::cout << "encontre el contacto buscado" << std::endl;
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				std::cout << "encontre el contacto con pj" << std::endl;
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->salud > 0){
					((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->cayoPorAgujero = true;
				}
			}
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO|| *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureBUserData)) == PIESEN || *((int*)(&fixtureBUserData)) == PIESENCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA) {
				std::cout << "encontre el contacto con enemigo" << std::endl;
				((Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureBUserData)) == PODERHIELO ){
				((BolaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureBUserData)) == PODERFUEGO ){
				((BolaDeFuego*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureBUserData)) == BOLASNOW ){
				std::cout << "detecte que la bola cayo" << std::endl;
				((PelotaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
			if ( *((int*)(&fixtureBUserData)) == DINAMICO ){
				((ObjetoModelo*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = true;
			}
		}

	}

     void EndContact(b2Contact* contact) {
   	  // Get Collision fixtures
    	void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    	void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

    	if ( *((int*)(&fixtureAUserData)) == EMPUJE ){
			if ( *((int*)(&fixtureBUserData)) == ENEMIGOBOLA || *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGO){
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->puedePatear = false;
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->enemigoParaEmpujar = NULL;
			}
		}

		if ( *((int*)(&fixtureAUserData)) == ENEMIGOBOLA ||  *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGO){
			if ( *((int*)(&fixtureBUserData)) == EMPUJE ){
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->puedePatear = false;
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->enemigoParaEmpujar = NULL;
			}
		}

  		// Foot sensor collision for jump
    	  if ( *((int*)(&fixtureAUserData)) == PIESPJ || *((int*)(&fixtureAUserData)) == PIESEN ){
        	  if ((*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO) && (*((int*)(&fixtureBUserData)) != sensorLAGUNA)&& (*((int*)(&fixtureBUserData)) != BOLASNOW) && (*((int*)(&fixtureBUserData)) != sensorAGUJERO))
        		  ( (SerVivo *) contact->GetFixtureA()->GetBody()->GetUserData() )->modificarContactosPie(-1);
          }
    	  if ( *((int*)(&fixtureBUserData)) == PIESPJ || *((int*)(&fixtureBUserData)) == PIESEN ){
        	  if ( (*((int*)(&fixtureAUserData)) != CAMARA)&&(*((int*)(&fixtureAUserData)) != PODERHIELO) && (*((int*)(&fixtureAUserData)) != sensorLAGUNA)&& (*((int*)(&fixtureAUserData)) != BOLASNOW) && (*((int*)(&fixtureBUserData)) != sensorAGUJERO))
        		  ( (SerVivo *) contact->GetFixtureB()->GetBody()->GetUserData() )->modificarContactosPie(-1);
          }

			// detecta que no haya mas contacto del pj con la laguna
			// colision entre las lagunas y el pj
			if( *((int*)(&fixtureBUserData)) == sensorLAGUNA ){
				if ( *((int*)(&fixtureAUserData)) == PERSONAJE  ) {
					if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0 &&
							((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido) {
						( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido = false;
					}
				}
				if ( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGOBOLA ) {
					if(( (Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0 &&
							((Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido) {
						( (Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData() )->sumergido = false;
					}
				}
			}

			if( *((int*)(&fixtureAUserData)) == sensorLAGUNA ){
				if ( *((int*)(&fixtureBUserData)) == PERSONAJE ) {
					if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->salud > 0 &&
							((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido) {
						( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido =false;
					}
				}
				if ( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA ) {
					if(( (Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData() )->salud > 0 &&
							((Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido) {
						( (Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData() )->sumergido = false;
					}
				}
			}
    }

      void PreSolve(b2Contact* contact, const b2Manifold* oldManiFold){
    	  void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    	  void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
    	  ObjetoInanimado * ITA = NULL;
    	  SerVivo * PJB = NULL;

  		// colision entre los agujero y el pj
  		if( *((int*)(&fixtureBUserData)) == sensorAGUJERO ){
  			std::cout << "encontre el contacto buscado" << std::endl;
  			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
  				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->salud > 0 ){
  					std::cout << "encontre el contacto con pj" << std::endl;
  					((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->cayoPorAgujero = false;
  				}
  			}
  			if ( *((int*)(&fixtureAUserData)) == ENEMIGO|| *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureAUserData)) == PIESEN || *((int*)(&fixtureAUserData)) == PIESENCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGOBOLA) {
  				std::cout << "encontre el contacto con enemigo" << std::endl;
  				((Enemigo*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureAUserData)) == PODERHIELO ){
  				((BolaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureAUserData)) == PODERFUEGO ){
  				((BolaDeFuego*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureAUserData)) == BOLASNOW ){
  				((PelotaDeNieve*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureAUserData)) == DINAMICO ){
  				((ObjetoModelo*) contact->GetFixtureA()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  		}

  		if( *((int*)(&fixtureAUserData)) == sensorAGUJERO ){
  			std::cout << "encontre el contacto buscado" << std::endl;
  			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
  				std::cout << "encontre el contacto con pj" << std::endl;
  				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->salud > 0){
  					((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->cayoPorAgujero = false;
  				}
  			}
  			if ( *((int*)(&fixtureBUserData)) == ENEMIGO|| *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureBUserData)) == PIESEN || *((int*)(&fixtureBUserData)) == PIESENCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA) {
  				std::cout << "encontre el contacto con enemigo" << std::endl;
  				((Enemigo*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureBUserData)) == PODERHIELO ){
  				((BolaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureBUserData)) == PODERFUEGO ){
  				((BolaDeFuego*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureBUserData)) == BOLASNOW ){
  				((PelotaDeNieve*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  			if ( *((int*)(&fixtureBUserData)) == DINAMICO ){
  				((ObjetoModelo*) contact->GetFixtureB()->GetBody()->GetUserData())->cayoPorAgujero = false;
  			}
  		}

    	  if ( *((int*)(&fixtureAUserData)) == ATRAVESABLE){
    		  if (*((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ){
    			  ITA = (ObjetoInanimado*) contact->GetFixtureA()->GetBody()->GetUserData();
    			  PJB = (SerVivo*) contact->GetFixtureB()->GetBody()->GetUserData();
    		  }
    	  }

    	  if (*((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ){
    		  if (*((int*)(&fixtureBUserData)) == ATRAVESABLE){
    			  ITA = (ObjetoInanimado*) contact->GetFixtureB()->GetBody()->GetUserData();
				  PJB = (SerVivo*)contact->GetFixtureA()->GetBody()->GetUserData();
    		  }
    	  }

    	  if ( *((int*)(&fixtureAUserData)) == ATRAVESABLE){
			  if (*((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == PIESEN){
				  ITA = (ObjetoInanimado*) contact->GetFixtureA()->GetBody()->GetUserData();
				  PJB = (SerVivo*) contact->GetFixtureB()->GetBody()->GetUserData();
			  }
		  }

		  if (*((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN){
			  if (*((int*)(&fixtureBUserData)) == ATRAVESABLE){
				  ITA = (ObjetoInanimado*) contact->GetFixtureB()->GetBody()->GetUserData();
				  PJB = (SerVivo*)contact->GetFixtureA()->GetBody()->GetUserData();
			  }
		  }

		  if ( *((int*)(&fixtureAUserData)) == PERSONAJE|| *((int*)(&fixtureAUserData)) == PIESPJ){
			  if (*((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ){
				  contact->SetEnabled(false);
			  }
		  }
		  if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ){
			  if (*((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ){
				  contact->SetEnabled(false);
			  }
		  }

    	  if(PJB != NULL && ITA != NULL){
    		  float velocidadSerVivoY = PJB->cuerpoB2D->GetLinearVelocity().y;
    		  if(velocidadSerVivoY < 0) contact->SetEnabled(false);
    	  }
      }
};



#endif /* CONTACTLISTENER_H_ */
