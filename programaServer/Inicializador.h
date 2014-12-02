/*
 * Inicializador.h
 *
 *  Created on: Sep 21, 2014
 *      Author: rodrizapico
 */

#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

#include <Box2D/Box2D.h>

#include "utiles/tipos.h"
#include "utiles/Logger.h"
#include "parser/parser.h"

#include "modelo/formas/Circulo.h"
#include "modelo/formas/PoligonoRegular.h"
#include "modelo/formas/Cuadrilatero.h"

#include "control/ContactListener.h"

#include "modelo/Personaje.h"
#include "modelo/Camera.h"
#include "modelo/EnemigoTiraFuego.h"
#include "modelo/Laguna.h"
#include "modelo/Agujero.h"
#include "server/ControladorEnemigos.h"

#include "threads/ThreadSafeList.h"


class Inicializador {

public:

	bool init(std::string configFile, b2World ** worldB2D, ContactListener * contactListener, ControladorEnemigos & army);
	Personaje * pjInit(b2World ** worldB2D, ThreadSafeList<WorldItem*> & rList, int numeroUsuario, std::string configFile);
	void enemysInit(b2World ** worldB2D, std::string configFile, ControladorEnemigos & army);

private:

	Camera * cameraInit(b2World ** worldB2D, b2Body * pj, ThreadSafeList<WorldItem*> & rList,
			float32 windowWidth, float32 windowHeight);
	static float widthWorld;
	static float heightWorld;
};

EnemigoEstandar * createEnemy(std::string data, b2World ** wB2D, int num);


#endif /* INICIALIZADOR_H_ */
