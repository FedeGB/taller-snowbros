/*
 * Camera.h
 *
 *  Created on: Sep 26, 2014
 *      Author: rodrizapico
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <Box2D/Box2D.h>
#include "../modelo/interfaces/IDibujable.h"
#include "../control/interfaces/INotificable.h"
//#include "../modelo/Personaje.h"

class Camera: public INotificable {
public:

	static float WORLDTOWINDOWSCALE;
	static float WINDOWTOWORLDSCALE;

	Camera();
	Camera(int windowWidth, int windowHeight, float32 windowToWorldScale);
	virtual ~Camera();
	void setB2DBody(b2Body * cB2D);
	void setWINDOWTOWORLDSCALE(float32 windowToWorld);
	void renderVisibleObjects();

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
	int width, height;
	bool canMoveLeft, canMoveRight, canMoveUp, canMoveDown;

	void calculateBorderConstraints();

};

#endif /* CAMERA_H_ */
