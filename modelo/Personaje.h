/*
 * Personaje.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../control/interfaces/INotificable.h"
#include "../modelo/formas/RectanguloDibujable.h"

enum ESTADOS
{
	ESTADO_PARADO,
	ESTADO_IZQUIERDA,
	ESTADO_DERECHA,
	ESTADO_SALTANDO,
	ESTADO_ABAJO,
};

class Personaje : public RectanguloDibujable, public INotificable {
public:
	Personaje();
	virtual ~Personaje();

	void setB2DBody(b2Body * pjB2D);
	void modifyFootContacts(int i);
	void setNewAngle(float32 a);

	// metodos de INotificable
	virtual void eventoArriba();
	virtual void eventoSoltoArriba();
	virtual void eventoDerecha();
	virtual void eventoSoltoDerecha();
	virtual void eventoIzquierda();
	virtual void eventoSoltoIzquierda();
	virtual void eventoRESTART(); // NO HACE NADA

	//virtual SDL_Rect * getRecuadroDeDibujo();
	virtual void render();
	virtual bool cargarImagen(std::string path);

private:
	//int pEstado;
	b2Body * bodyB2D;
	int numFootContacts;
	float32 angle;
	bool isRightPressed;
	bool isLeftPressed;
	bool isUpPressed;
	bool wasLeftPressed1st;
	SDL_Rect activeSprite;
	SDL_Rect spriteRects[10];
	int animationCounter;
	bool leftOriented;

	enum SPRITES
	{
		PARADOIZQUIERDA,
		MOVIENDOIZQUIERDA1,
		MOVIENDOIZQUIERDA2,
		MOVIENDOIZQUIERDA3,
		MOVIENDOIZQUIERDA4,
		SALTANDOIZQUIERDA1,
		SALTANDOIZQUIERDA2,
		SALTANDOIZQUIERDA3,
		SALTANDOIZQUIERDA4,
		SALTANDOIZQUIERDA5,
	};
};

#endif /* PERSONAJE_H_ */
