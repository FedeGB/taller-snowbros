/*
 * ContactListener.h
 *
 *  Created on: Sep 20, 2014
 *      Author: rodrizapico
 */

#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_

#include <Box2D/Box2D.h>
#include "../modelo/Personaje.h"

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
			if ( *((int*)(&fixtureAUserData)) == ESTATICO  )
				delete (snowball*) contact->GetFixtureB()->GetBody()->GetUserData();
		}
		if( *((int*)(&fixtureAUserData)) == PODERHIELO ){
			if ( *((int*)(&fixtureBUserData)) == ESTATICO  )
				delete (snowball*) contact->GetFixtureA()->GetBody()->GetUserData();
		}
	}

      void EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
    	  void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    	  void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
    	  if ( *((int*)(&fixtureAUserData)) == PIESPJ || *((int*)(&fixtureAUserData)) == PIESEN ){
        	  if ((*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO))
        		  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          }
          //check if fixture B was the foot sensor
    	  if ( *((int*)(&fixtureBUserData)) == PIESPJ || *((int*)(&fixtureBUserData)) == PIESEN ){
        	  if ( (*((int*)(&fixtureAUserData)) != CAMARA)&&(*((int*)(&fixtureAUserData)) != PODERHIELO))
        		  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          }
      }
  };



#endif /* CONTACTLISTENER_H_ */
