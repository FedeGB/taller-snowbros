/*
 * Inicializador.h
 *
 *  Created on: Sep 21, 2014
 *      Author: rodrizapico
 */

#ifndef INICIALIZADOR_H_
#define INICIALIZADOR_H_

//#include <Box2D/Box2D.h>

#include "utiles/tipos.h"
#include "utiles/Logger.h"
#include "parser/parser.h"
#include "control/ContactListener.h"
#include "servicios/LocalizadorDeServicios.h"
#include "parserMensajes/protocoloServidorCliente.h"
#include "controladorJuego/ControladorJuego.h"
#include "controladorJuego/estadoJuego/Jugador.h"
#include "controladorJuego/modeloJuego/tiposDeObjeto/Personaje.h"
#include "controladorJuego/modeloJuego/tiposDeObjeto/EnemigoEstandar.h"
#include "controladorJuego/modeloJuego/tiposDeObjeto/EnemigoFuego.h"
#include "controladorJuego/modeloJuego/tiposDeObjeto/Ladrillo.h"
#include "controladorJuego/modeloJuego/tiposDeObjeto/Laguna.h"
#include "controladorJuego/modeloJuego/tiposDeObjeto/Agujero.h"
#include "controladorJuego/modeloJuego/tiposDeObjeto/PelotaDeNieve.h"
//#include "control/ContactListener.h"
//#include "threads/ThreadSafeList.h"


class Inicializador {

public:

	// Clase encargada de inicializar varios modulos del juego.
	Inicializador();
	~Inicializador();

	// Valida los parametros iniciales. Si son validos, los carga como
	// informacion publica.
	bool validarParametros(int argc, char** argv);

	bool init(std::string configFile, b2World ** worldB2D, ControladorJuego * controlador, ContactListener * contactListener, std::string & nextLevel);

	static bool loadInitialValues(std::string configFile, std::string& sConfig);

private:

	//Camera * cameraInit(b2World ** worldB2D, b2Body * pj, ThreadSafeList<WorldItem*> & rList,
	//		float32 windowWidth, float32 windowHeight);
	//static float widthWorld;
	//static float heightWorld;


};

//EnemigoEstandar * createEnemy(std::string data, b2World ** wB2D, int num);


#endif /* INICIALIZADOR_H_ */
