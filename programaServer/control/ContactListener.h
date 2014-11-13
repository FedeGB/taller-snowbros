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
		//check if fixture A was the foot sensor
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
		// TODO: sacar estos '3' y '4's y cambiarlos por constantes.
		if ( *((int*)(&fixtureAUserData)) == PIESPJ ){
			if ( (*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO) )
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(1);
		}
		//check if fixture B was the foot sensor
		if ( *((int*)(&fixtureBUserData)) == PIESPJ ){
			if ( (*((int*)(&fixtureAUserData)) != CAMARA)&& (*((int*)(&fixtureAUserData)) != PODERHIELO) )
				( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(1);
		}


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
          if ( *((int*)(&fixtureAUserData)) == PIESPJ ){
        	  if ((*((int*)(&fixtureBUserData)) != CAMARA)&&(*((int*)(&fixtureBUserData)) != PODERHIELO))
        		  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          }
          //check if fixture B was the foot sensor
          if ( *((int*)(&fixtureBUserData)) == PIESPJ ){
        	  if ( (*((int*)(&fixtureAUserData)) != CAMARA)&&(*((int*)(&fixtureAUserData)) != PODERHIELO))
        		  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          }
      }
  };



#endif /* CONTACTLISTENER_H_ */
