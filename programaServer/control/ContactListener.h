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
#include "../modelo/Sorpresa.h"

class ContactListener : public b2ContactListener
  {
	void BeginContact(b2Contact* contact) {
		// Get Collision fixtures
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

		// Foot sensor collision for jump
		if ( *((int*)(&fixtureAUserData)) == PIESPJ || *((int*)(&fixtureAUserData)) == PIESEN ){
			if ( (*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO) )
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(1);
		}
		if ( *((int*)(&fixtureBUserData)) == PIESPJ || *((int*)(&fixtureBUserData)) == PIESEN ){
			if ( (*((int*)(&fixtureAUserData)) != CAMARA)&& (*((int*)(&fixtureAUserData)) != PODERHIELO) )
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(1);
		}

		// Collision between PJ and Enemy, apply damage
		if( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive()) {
					( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->applyDamage(0.5);
				}
			}
		}
		if( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == PIESEN ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive()) {
					( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->applyDamage(0.5);
				}
			}
		}

		// Collision between Snowballs and Static Objects
		if( *((int*)(&fixtureBUserData)) == PODERHIELO ){
			if ( *((int*)(&fixtureAUserData)) == ESTATICO  ) {
				((snowball*) contact->GetFixtureB()->GetBody()->GetUserData())->setDelete();
			}
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN ) {
				((EnemigoEstandar*) contact->GetFixtureA()->GetBody()->GetUserData())->applyDamage(((snowball*) contact->GetFixtureA()->GetBody()->GetUserData())->getDamage());
			}
		}
		if( *((int*)(&fixtureAUserData)) == PODERHIELO ){
			if ( *((int*)(&fixtureBUserData)) == ESTATICO  ) {
				((snowball*) contact->GetFixtureA()->GetBody()->GetUserData())->setDelete();
			}
			if ( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == PIESEN ) {
				((EnemigoEstandar*) contact->GetFixtureB()->GetBody()->GetUserData())->applyDamage(((snowball*) contact->GetFixtureB()->GetBody()->GetUserData())->getDamage());
			}
		}

		// Plataform borders collision
		if( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == PIESEN ){
			if ( *((int*)(&fixtureAUserData)) == BORDE ) {
				((EnemigoEstandar*) contact->GetFixtureB()->GetBody()->GetUserData())->setOnBorder(true);
			}
		}
		if (  *((int*)(&fixtureBUserData)) == BORDE ){
			if ( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN ) {
				((EnemigoEstandar*) contact->GetFixtureA()->GetBody()->GetUserData())->setOnBorder(true);
			}
		}

		// colision entre las sorpresas y el pj
		if( *((int*)(&fixtureBUserData)) == sensorSORPRESA ){
			if ( *((int*)(&fixtureAUserData)) == PERSONAJE || *((int*)(&fixtureAUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->isAlive()) {
					Sorpresa* sorpresa = (Sorpresa*) contact->GetFixtureB()->GetBody()->GetUserData();
					sorpresa->setDelete();
					sorpresa->aplicarAlPJ( ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() ) );
					//( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->aplicarSorpresa(sorpresa);
				}
			}
		}

		if( *((int*)(&fixtureAUserData)) == sensorSORPRESA ){
			if ( *((int*)(&fixtureBUserData)) == PERSONAJE || *((int*)(&fixtureBUserData)) == PIESPJ ) {
				if(( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->isAlive()) {
					Sorpresa* sorpresa = (Sorpresa*) contact->GetFixtureA()->GetBody()->GetUserData();
					sorpresa->setDelete();
					sorpresa->aplicarAlPJ( ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() ) );
					//( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->aplicarSorpresa(sorpresa);

				}
			}
		}
	}

      void EndContact(b2Contact* contact) {
    	  // Get Collision fixtures
    	  void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    	  void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

  		// Foot sensor collision for jump
    	  if ( *((int*)(&fixtureAUserData)) == PIESPJ || *((int*)(&fixtureAUserData)) == PIESEN ){
        	  if ((*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO))
        		  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          }
    	  if ( *((int*)(&fixtureBUserData)) == PIESPJ || *((int*)(&fixtureBUserData)) == PIESEN ){
        	  if ( (*((int*)(&fixtureAUserData)) != CAMARA)&&(*((int*)(&fixtureAUserData)) != PODERHIELO))
        		  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          }

    	  	// Plataform borders collision
			if( *((int*)(&fixtureBUserData)) == ENEMIGO || *((int*)(&fixtureBUserData)) == PIESEN ){
				if ( *((int*)(&fixtureAUserData)) == BORDE ) {
					( (EnemigoEstandar *) contact->GetFixtureB()->GetBody()->GetUserData() )->setOnBorder(false);
				}
			}
			if (  *((int*)(&fixtureBUserData)) == BORDE ){
				if ( *((int*)(&fixtureAUserData)) == ENEMIGO || *((int*)(&fixtureAUserData)) == PIESEN ) {
					( (EnemigoEstandar *) contact->GetFixtureA()->GetBody()->GetUserData() )->setOnBorder(false);
				}
			}
      }
  };



#endif /* CONTACTLISTENER_H_ */
