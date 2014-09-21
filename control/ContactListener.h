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
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		if ( *((int*)(&fixtureUserData)) == 3 )
		  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(1);
		//check if fixture B was the foot sensor
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if ( *((int*)(&fixtureUserData)) == 3 )
		  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(1);

	}

      void EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( *((int*)(&fixtureUserData)) == 3 )
          	  ( (Personaje *) contact->GetFixtureA()->GetBody()->GetUserData() )->modifyFootContacts(-1);
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( *((int*)(&fixtureUserData)) == 3 )
        	  ( (Personaje *) contact->GetFixtureB()->GetBody()->GetUserData() )->modifyFootContacts(-1);
      }
  };



#endif /* CONTACTLISTENER_H_ */
