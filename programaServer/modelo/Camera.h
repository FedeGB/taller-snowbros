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
#include "../threads/ThreadSafeList.h"
#include "../modelo/WorldItem.h"
#include "../modelo/Metadata.h"

class Camera{
public:

	Camera(ThreadSafeList<WorldItem*> & rList, int windowWidth, int windowHeight,
			float worldW, float worldH, float32 windowToWorldScale);
	virtual ~Camera();
	void setB2DBody(b2Body * cB2D);
	void setPJ(b2Body * pjB2D);
	void setWINDOWTOWORLDSCALE(float32 windowToWorld);
	void update();
	void reposition(b2Vec2);

	virtual void eventoZoomIn();
	virtual void eventoZoomOut();

private:

	float WORLDTOWINDOWSCALE;
	float WINDOWTOWORLDSCALE;

	b2Body * cameraB2D;
	b2Body * PJ;
	b2Vec2 posPJCamera;
	ThreadSafeList<WorldItem*> & renderList;
	int width, height;
	int worldWidth, worldHeight;
	bool canMoveLeft, canMoveRight, canMoveUp, canMoveDown;
	bool zoomChanged;

	void calculateBorderConstraints();
	void calcularPosRelativaPJ();
	void updateZoom();
	void updatePosition();
	void updateRenderList();
};

#endif /* CAMERA_H_ */
