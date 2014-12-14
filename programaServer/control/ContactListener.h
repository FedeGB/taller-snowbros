/*
 * ContactListener.h
 *
 *  Created on: Sep 20, 2014
 *      Author: rodrizapico
 */

#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_

#include <Box2D/Box2D.h>
#include "../modelo/EnemigoEstandar.h"
#include "../modelo/Fireball.h"
#include "../modelo/Sorpresa.h"
#include "../modelo/BolaEnemigo.h"

class ContactListener : public b2ContactListener
  {
	void BeginContact(b2Contact* contact) {
		// Get Collision fixtures
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

		if ( *((int*)(&fixtureBUserData)) == BOLASNOW ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE ||*((int*)(&fixtureAUserData)) == PIESPJ  ){
				if(((BolaEnemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->contactcounter>=1){
					//if(((BolaEnemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->pj==NULL)
						((BolaEnemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->bindPj(((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() ));
					((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->inBall(contact->GetFixtureB()->GetBody());
				}

				((BolaEnemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->contactcounter++;
				std::cout<<((BolaEnemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->contactcounter;
			}
		}
		if ( *((int*)(&fixtureAUserData)) == BOLASNOW ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE ||*((int*)(&fixtureBUserData)) == PIESPJ  ){
				if(((BolaEnemigo*)contact->GetFixtureA()->GetBody()->GetUserData())->contactcounter>=1){
					//if(((BolaEnemigo*)contact->GetFixtureA()->GetBody()->GetUserData())->pj==NULL)
						((BolaEnemigo*)contact->GetFixtureA()->GetBody()->GetUserData())->bindPj(((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() ));
					((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->inBall(contact->GetFixtureA()->GetBody());
				}
				((BolaEnemigo*)contact->GetFixtureA()->GetBody()->GetUserData())->contactcounter++;
				std::cout<<((BolaEnemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->contactcounter;
			}
		}

		if ( *((int*)(&fixtureBUserData)) == BOLASNOW ){
			((BolaEnemigo*)contact->GetFixtureB()->GetBody()->GetUserData())->notBounce();
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO ||*((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO  ){
				((EnemigoEstandar*)contact->GetFixtureA()->GetBody()->GetUserData())->setDelete();
			}
		}

		if ( *((int*)(&fixtureAUserData)) == BOLASNOW){
			((BolaEnemigo*)contact->GetFixtureA()->GetBody()->GetUserData())->notBounce();
				if ( *((int*)(&fixtureBUserData)) == ENEMIGO ||*((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO  ){
					((EnemigoEstandar*)contact->GetFixtureB()->GetBody()->GetUserData())->setDelete();
				}
		}

		if ( *((int*)(&fixtureAUserData)) == EMPUJE ){
			if ( *((int*)(&fixtureBUserData)) == ENEMIGOBOLA ){
				orientation_t ori=(orientation_t)( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->GetOrientation();
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->Patear();
				( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->empujar(ori);
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->enemigoParaEmpujar=( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() );
			}
		}
		if ( *((int*)(&fixtureAUserData)) == ENEMIGOBOLA ){
			if ( *((int*)(&fixtureBUserData)) == EMPUJE ){
				orientation_t ori=(orientation_t)( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->GetOrientation();
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->Patear();
				( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->empujar(ori);
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->enemigoParaEmpujar=( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() );
			}
		}

		// Foot sensor collision for jump
		if ( *((int*)(&fixtureAUserData)) == PIESPJ || *((int*)(&fixtureAUserData)) == PIESEN || *((int*)(&fixtureAUserData)) == PIESENCONGELADO ){
			if ( (*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO) && (*((int*)(&fixtureBUserData)) != sensorLAGUNA)&& (*((int*)(&fixtureBUserData)) != BOLASNOW)&&(*((int*)(&fixtureBUserData)) != PERSONAJE)&&(*((int*)(&fixtureBUserData)) != PIESPJ))
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(1);
			if ( (*((int*)(&fixtureBUserData)) == ATRAVESABLE && ( (Cuadrilatero*) contact->GetFixtureB()->GetBody()->GetUserData())->hielo ) ) {
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setSobreHielo(true);
			}
		}
		if ( *((int*)(&fixtureBUserData)) == PIESPJ || *((int*)(&fixtureBUserData)) == PIESEN || *((int*)(&fixtureBUserData)) == PIESENCONGELADO ){
			if ( (*((int*)(&fixtureAUserData)) != CAMARA)&& (*((int*)(&fixtureAUserData)) != PODERHIELO) && (*((int*)(&fixtureAUserData)) != sensorLAGUNA)&& (*((int*)(&fixtureAUserData)) != BOLASNOW)&&(*((int*)(&fixtureAUserData)) != PERSONAJE)&&(*((int*)(&fixtureAUserData)) != PIESPJ))
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(1);
			if ( (*((int*)(&fixtureAUserData)) == ATRAVESABLE && ( (Cuadrilatero*) contact->GetFixtureA()->GetBody()->GetUserData())->hielo ) ) {
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setSobreHielo(true);
			}
		}

		// Collision between PJ and Enemy, apply damage
		if( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive() && !( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->trapped()) {
					( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->applyDamage(1);
				}
			}
		}
		if( *((int*)(&fixtureBUserData)) == ENEMIGO ||* ((int*)(&fixtureBUserData)) == PIESEN ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive() && !( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->trapped()) {
					( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->applyDamage(1);
				}
			}
		}

		// Collision between Snowballs and Objects
		if( *((int*)(&fixtureBUserData)) == PODERHIELO ){
			if ( *((int*)(&fixtureAUserData)) == ESTATICO || *((int*)(&fixtureAUserData)) == ATRAVESABLE || *((int*)(&fixtureAUserData)) == DINAMICO ){
				((snowball*) contact->GetFixtureB()->GetBody()->GetUserData())->setDelete();
			}
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO|| *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureAUserData)) == PIESEN ) {
				((snowball*) contact->GetFixtureB()->GetBody()->GetUserData())->setDelete();
				((EnemigoEstandar*) contact->GetFixtureA()->GetBody()->GetUserData())->applyDamage(((snowball*) contact->GetFixtureA()->GetBody()->GetUserData())->getDamage());
			}
		}
		if( *((int*)(&fixtureAUserData)) == PODERHIELO ){
			if ( *((int*)(&fixtureBUserData)) == ESTATICO  || *((int*)(&fixtureBUserData)) == ATRAVESABLE || *((int*)(&fixtureBUserData)) == DINAMICO ) {
				((snowball*) contact->GetFixtureA()->GetBody()->GetUserData())->setDelete();
			}
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureBUserData)) == PIESEN ) {
				((snowball*) contact->GetFixtureA()->GetBody()->GetUserData())->setDelete();
				((EnemigoEstandar*) contact->GetFixtureB()->GetBody()->GetUserData())->applyDamage(((snowball*) contact->GetFixtureB()->GetBody()->GetUserData())->getDamage());
			}
		}

		// Collision between Fireballs and Objects
		if( *((int*)(&fixtureBUserData)) == PODERFUEGO ){
			if ( *((int*)(&fixtureAUserData)) == ESTATICO || *((int*)(&fixtureAUserData)) == ATRAVESABLE || *((int*)(&fixtureAUserData)) == DINAMICO ){
				((Fireball*) contact->GetFixtureB()->GetBody()->GetUserData())->setDelete();
			}
			if ((*((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ)) {
				((Fireball*) contact->GetFixtureB()->GetBody()->GetUserData())->setDelete();
				if(((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive())
					((Personaje*) contact->GetFixtureA()->GetBody()->GetUserData())->applyDamage(((Fireball*) contact->GetFixtureB()->GetBody()->GetUserData())->getDamage());
			}
		}
		if( *((int*)(&fixtureAUserData)) == PODERFUEGO ){
			if ( *((int*)(&fixtureBUserData)) == ESTATICO  || *((int*)(&fixtureBUserData)) == ATRAVESABLE || *((int*)(&fixtureBUserData)) == DINAMICO ) {
				((Fireball*) contact->GetFixtureA()->GetBody()->GetUserData())->setDelete();
			}
			if ((*((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ)) {
				((Fireball*) contact->GetFixtureA()->GetBody()->GetUserData())->setDelete();
				if(((Personaje*) contact->GetFixtureB()->GetBody()->GetUserData())->isAlive())
					((Personaje*) contact->GetFixtureB()->GetBody()->GetUserData())->applyDamage(((Fireball*) contact->GetFixtureA()->GetBody()->GetUserData())->getDamage());
			}
		}

		// colision entre las sorpresas y el pj
		if( *((int*)(&fixtureBUserData)) == sensorSORPRESA ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive()) {
					Sorpresa* sorpresa = (Sorpresa*) contact->GetFixtureB()->GetBody()->GetUserData();
					sorpresa->setDelete();
					sorpresa->aplicarAlPJ( ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() ) );
				}
			}
		}

		if( *((int*)(&fixtureAUserData)) == sensorSORPRESA ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive()) {
					Sorpresa* sorpresa = (Sorpresa*) contact->GetFixtureA()->GetBody()->GetUserData();
					sorpresa->setDelete();
					sorpresa->aplicarAlPJ( ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() ) );
				}
			}
		}

		// colision entre las lagunas y el pj
		if( *((int*)(&fixtureBUserData)) == sensorLAGUNA ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive() &&
						!((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->estaSumergido()) {
					( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setSumergido(true);
				}
			}
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGOBOLA) {
				if(( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive() &&
						!((EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->estaSumergido()) {
					( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->setSumergido(true);
				}
			}
		}

		if( *((int*)(&fixtureAUserData)) == sensorLAGUNA ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE ) {
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive() &&
						!((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->estaSumergido() ) {
					( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setSumergido(true);
				}
			}
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA) {
				if(( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive() &&
						!((EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->estaSumergido()) {
					( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->setSumergido(true);
				}
			}
		}

		// colision entre los agujero y el pj
		if( *((int*)(&fixtureBUserData)) == sensorAGUJERO ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive() ){
					((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setCayoPorAgujero(true);
				}
			}
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO|| *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureAUserData)) == PIESEN || *((int*)(&fixtureAUserData)) == PIESENCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGOBOLA || *((int*)(&fixtureAUserData)) == PIESENBOLA) {
				((EnemigoEstandar*) contact->GetFixtureA()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
			if ( *((int*)(&fixtureAUserData)) == PODERHIELO ){
				((snowball*) contact->GetFixtureA()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
			if ( *((int*)(&fixtureAUserData)) == PODERFUEGO ){
				((Fireball*) contact->GetFixtureA()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
			if ( *((int*)(&fixtureAUserData)) == BOLASNOW ){
				((BolaEnemigo*) contact->GetFixtureA()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
		}

		if( *((int*)(&fixtureAUserData)) == sensorAGUJERO ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive() ){
					((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setCayoPorAgujero(true);
				}
			}
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO|| *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO|| *((int*)(&fixtureBUserData)) == PIESEN || *((int*)(&fixtureBUserData)) == PIESENCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA) {
				((EnemigoEstandar*) contact->GetFixtureB()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
			if ( *((int*)(&fixtureBUserData)) == PODERHIELO ){
				((snowball*) contact->GetFixtureB()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
			if ( *((int*)(&fixtureBUserData)) == PODERFUEGO ){
				((Fireball*) contact->GetFixtureB()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
			if ( *((int*)(&fixtureBUserData)) == BOLASNOW ){
				((BolaEnemigo*) contact->GetFixtureB()->GetBody()->GetUserData())->setCayoPorAgujero(true);
			}
//			if ( *((int*)(&fixtureBUserData)) == DINAMICO ){
//				((EnemigoEstandar*) contact->GetFixtureB()->GetBody()->GetUserData())->setCayoPorAgujero(true);
//			}
		}
	}

     void EndContact(b2Contact* contact) {
   	  // Get Collision fixtures
    	void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    	void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

//    	  if ( *((int*)(&fixtureAUserData)) == PERSONAJE ){
    			if ( *((int*)(&fixtureAUserData)) == EMPUJE ){
    	  					if ( *((int*)(&fixtureBUserData)) == ENEMIGOBOLA ){
    	  						( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->NoPatear();
    	  						( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->Noempujar();
    	  						( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->enemigoParaEmpujar= NULL;
    	  					}
    	  		}
    			if ( *((int*)(&fixtureAUserData)) == ENEMIGOBOLA ){
//    	  							if ( *((int*)(&fixtureBUserData)) == PERSONAJE ){
									if ( *((int*)(&fixtureBUserData)) == EMPUJE ){
    	  								( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->NoPatear();
    	  								( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->Noempujar();
    	  								( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->enemigoParaEmpujar= NULL;
    	  							}
    	  		}

  		// Foot sensor collision for jump
    	  if ( *((int*)(&fixtureAUserData)) == PIESPJ || *((int*)(&fixtureAUserData)) == PIESEN  || *((int*)(&fixtureAUserData)) == PIESENCONGELADO){
        	  if ((*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO) && (*((int*)(&fixtureBUserData)) != sensorLAGUNA)&& (*((int*)(&fixtureBUserData)) != BOLASNOW)&&(*((int*)(&fixtureBUserData)) != PERSONAJE)&&(*((int*)(&fixtureBUserData)) != PIESPJ))
        		  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(-1);
        	  if((*((int*)(&fixtureBUserData))) == ATRAVESABLE && ( (WorldItem*)contact->GetFixtureB()->GetBody()->GetUserData())->hielo ) {
        	  	   ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setSobreHielo(false);
        	  }
          }
    	  if ( *((int*)(&fixtureBUserData)) == PIESPJ || *((int*)(&fixtureBUserData)) == PIESEN || *((int*)(&fixtureBUserData)) == PIESENCONGELADO){
        	  if ( (*((int*)(&fixtureAUserData)) != CAMARA)&&(*((int*)(&fixtureAUserData)) != PODERHIELO) && (*((int*)(&fixtureAUserData)) != sensorLAGUNA)&& (*((int*)(&fixtureAUserData)) != BOLASNOW)&&(*((int*)(&fixtureAUserData)) != PERSONAJE)&&(*((int*)(&fixtureAUserData)) != PIESPJ))
        		  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(-1);
        	  if((*((int*)(&fixtureAUserData))) == ATRAVESABLE && ( ((Cuadrilatero*)contact->GetFixtureA()->GetBody()->GetUserData())->hielo) ) {
        	  	   ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setSobreHielo(false);
        	  }
          }

			// detecta que no haya mas contacto del pj con la laguna
			// colision entre las lagunas y el pj
			if( *((int*)(&fixtureBUserData)) == sensorLAGUNA ){
				if ( *((int*)(&fixtureAUserData)) == PERSONAJE  ) {
					if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive() &&
							((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->estaSumergido()) {
						( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setSumergido(false);
					}
				}
				if ( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureAUserData)) == ENEMIGOBOLA ) {
					if(( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive() &&
							((EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->estaSumergido()) {
						( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->setSumergido(false);
					}
				}
			}

			if( *((int*)(&fixtureAUserData)) == sensorLAGUNA ){
				if ( *((int*)(&fixtureBUserData)) == PERSONAJE ) {
					if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive() &&
							((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->estaSumergido()) {
						( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setSumergido(false);
					}
				}
				if ( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == ENEMIGOCONGELADO || *((int*)(&fixtureBUserData)) == ENEMIGOBOLA ) {
					if(( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive() &&
							((EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->estaSumergido()) {
						( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->setSumergido(false);
					}
				}
			}

			// detecta que no haya mas contacto del pj con el agujero
			// colision entre los agujeros y el pj
			if( *((int*)(&fixtureBUserData)) == sensorAGUJERO ){
				if ( *((int*)(&fixtureAUserData)) == PERSONAJE  ) {
					if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive() ){
						((Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setCayoPorAgujero(false);
					}
				}
			}

			if( *((int*)(&fixtureAUserData)) == sensorAGUJERO ){
				if ( *((int*)(&fixtureBUserData)) == PERSONAJE ) {
					if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive() ){
						((Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setCayoPorAgujero(false);
					}
				}
			}
      }

      void PreSolve(b2Contact* contact, const b2Manifold* oldManiFold){
    	  void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    	  void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
    	  Cuadrilatero* ITA = NULL;
    	  Personaje* PJB = NULL;

    	  if ( *((int*)(&fixtureAUserData)) == BOLASNOW){
    		  if (*((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ){
    			  contact->SetEnabled(false);
    		  }
    	  }
    	  if ( *((int*)(&fixtureBUserData)) == BOLASNOW){
    		  if (*((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ){
    			  contact->SetEnabled(false);
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

    	  if ( *((int*)(&fixtureAUserData)) == ATRAVESABLE){
    		  if (*((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ){
    //			  Cuadrilatero* ITA = (Cuadrilatero*) contact->GetFixtureA()->GetBody()->GetUserData();
   // 			  float PosA = ITA->posicion.y - (ITA->altura / 2.0);
 //   			  Personaje* PJB = (Personaje*) contact->GetFixtureB()->GetBody()->GetUserData();
//    			  float PosB = PJB->posicion.y + (PJB->altura / 2.0);

//    			  printf("Pos PJ: %f", PosB);
//   			  printf("Pos Plat: %f", PosA);
//    			  if ( PosB > PosA + 0.2) contact->SetEnabled(false);
    			  ITA = (Cuadrilatero*) contact->GetFixtureA()->GetBody()->GetUserData();
    			  PJB = (Personaje*) contact->GetFixtureB()->GetBody()->GetUserData();
    		  }
    	  }

    	  if (*((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ){
    		  if (*((int*)(&fixtureBUserData)) == ATRAVESABLE){
    			  ITA = (Cuadrilatero *) contact->GetFixtureB()->GetBody()->GetUserData();
				  PJB = (Personaje*)contact->GetFixtureA()->GetBody()->GetUserData();
    		  }
    	  }

    	  if ( *((int*)(&fixtureAUserData)) == ATRAVESABLE){
    	    		  if (*((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == PIESEN){
    	    			  ITA = (Cuadrilatero*) contact->GetFixtureA()->GetBody()->GetUserData();
    	    			  PJB = (EnemigoEstandar*) contact->GetFixtureB()->GetBody()->GetUserData();
    	    		  }
    	    	  }

    	    	  if (*((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN){
    	    		  if (*((int*)(&fixtureBUserData)) == ATRAVESABLE){
    	    			  ITA = (Cuadrilatero *) contact->GetFixtureB()->GetBody()->GetUserData();
    					  PJB = (EnemigoEstandar*)contact->GetFixtureA()->GetBody()->GetUserData();
    	    		  }
    	    	  }

    	  if(PJB != NULL && ITA != NULL){
    		  //Me fijo si la parte de abajo del personaje esta por arriba del la parte de arriba de la plataforma.
    		  float PosA = ITA->posicion.y - (ITA->altura / 2.0);
    	  	  float PosB = PJB->posicion.y + (PJB->altura / 2.0);

    	  	float PosC = ITA->posicion.y + (ITA->altura / 2.0);
   	  		float PosD = PJB->posicion.y - (PJB->altura / 2.0);

    	  	  // printf("Pos PJ: %f", PosB);
    	  	  // printf("Pos Plat: %f", PosA);
		  	  if ( PosB > PosA + 0.2 && PJB->GetAirborne() ){
			  	  contact->SetEnabled(false);
		  	  }

		  	if ( PosD < PosC + 4.0 && PJB->getFalling() ){
			  	  contact->SetEnabled(false);
		  	}

    	  }

      }
  };



#endif /* CONTACTLISTENER_H_ */
