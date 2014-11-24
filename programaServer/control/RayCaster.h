/*
 * RayCaster.h
 *
 *  Created on: Nov 23, 2014
 *      Author: fedevm
 */

#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include <Box2D/Box2D.h>

class RayCaster : public b2RayCastCallback {
public:

	RayCaster() : m_fixture(NULL) {
	}
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
        m_fixture = fixture;
        void* fixData = fixture->GetUserData();

        m_point = point;
        m_normal = normal;
        m_fraction = fraction;
        if( *((int*)(&fixData)) != ATRAVESABLE) {
        	return 1;
        }
        return fraction;
	}

	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float32 m_fraction;
};



#endif /* RAYCASTER_H_ */
