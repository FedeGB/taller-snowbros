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
		// TODO: sacar estos '2' y '3' y cambiarlos por constantes.
		if ( *((int*)(&fixtureAUserData)) == 3 ){
			( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(1);
			if ( (*((int*)(&fixtureBUserData)) == 2) ) // Check if fixture B is a static object
				( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setNewAngle(contact->GetFixtureB()->GetBody()->GetAngle());
		}
		//check if fixture B was the foot sensor
		if ( *((int*)(&fixtureBUserData)) == 3 ){
		  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(1);
		  if ( (*((int*)(&fixtureAUserData)) == 2) )  // Check if fixture A is a static object
			  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setNewAngle(contact->GetFixtureA()->GetBody()->GetAngle());
		}
	}

      void EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( *((int*)(&fixtureUserData)) == 3 ){
          	  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          	  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->setNewAngle(0);
          }
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( *((int*)(&fixtureUserData)) == 3 ){
        	  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          	  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->setNewAngle(0);
          }
      }
  };



#endif /* CONTACTLISTENER_H_ */
