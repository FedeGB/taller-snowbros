/*
 * Camera.h
 *
 *  Created on: Sep 26, 2014
 *      Author: rodrizapico
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <Box2D/Box2D.h>
#include "WorldItem.h"
#include "../Threads/ThreadSafeList.h"
#include "../modelo/WorldItem.h"

class Camera{
public:

	static float WORLDTOWINDOWSCALE;
	static float WINDOWTOWORLDSCALE;

	Camera(ThreadSafeList<WorldItem*> & rList, int windowWidth, int windowHeight, float32 windowToWorldScale);
	virtual ~Camera();
	void setB2DBody(b2Body * cB2D);
	void setPJ(b2Body * pjB2D);
	void setWINDOWTOWORLDSCALE(float32 windowToWorld);
	void update();

	//Interfaz notificable
	virtual void eventoArriba();
	virtual void eventoSoltoArriba();
	virtual void eventoDerecha();
	virtual void eventoSoltoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoSoltoIzquierda();
	virtual void eventoRESTART();
	virtual void eventoZoomIn();
	virtual void eventoZoomOut();

private:

	b2Body * cameraB2D;
	b2Body * PJ;
	ThreadSafeList<WorldItem*> & renderList;
	int width, height;
	bool canMoveLeft, canMoveRight, canMoveUp, canMoveDown;

	void calculateBorderConstraints();
	void updatePosition();
	void updateRenderList();
};

#endif /* CAMERA_H_ */
