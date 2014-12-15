/*
 * WorldHandler.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "WorldHandler.h"
#include <stdio.h>
#include <unistd.h>
#include "../utiles/Timer.h"


WorldHandler::WorldHandler(ControladorJuego * c):
	controlador(c), worldB2D(NULL){}


// El programa espera a que haya una cantidad suficiente de jugadores.
void WorldHandler::esperar(){
	// Espera a que se llene el escenario.
	while (!controlador->estado.puedeEmpezar()) {
		usleep(200000);
	}
}

// Cuando se llena el servidor, comienza la partida.
resultado_t WorldHandler::simularPartida(){

	std::string nextLevel;
	std::string configFile = LocalizadorDeServicios::obtenerInformacionPublica()->archivoConfiguracion;

	resultado_t resultado = GANARON;

	// Itera sobre todos los niveles.
	while (nextLevel != "LASTLEVEL" && resultado == GANARON){

		// Espera a que los jugadores restantes decidan empezar el nivel.
		esperar();

		// Carga el nivel.
		if (inicializador.init(configFile, &worldB2D, controlador, &contactListener, nextLevel)){

			// Informa que inicia el juego.
			controlador->estado.cambiarEstado(JUGANDO);

			// Juega el nivel.
			resultado = loopPrincipal();

			// Si hubo un error en el resultado, caos y desolacion.
			if (resultado == ERROR_RESULTADO) return ERROR_RESULTADO;

			// Analiza el resultado, y actualiza el estado del juego en consecuencia.
			controlador->bloquear();

			// Destruye el modelo.
			controlador->modelo.limpiar();
			delete worldB2D;
			worldB2D = NULL;


			// Actualiza el estado.
			if (resultado == PERDIERON){
				controlador->estado.cambiarEstado(JUEGOTERMINADO);
				controlador->desbloquear();
				return PERDIERON;
			} else if (resultado == GANARON && nextLevel != "LASTLEVEL"){
				controlador->estado.cambiarEstado(NIVELTERMINADO);
			} else controlador->estado.cambiarEstado(JUEGOTERMINADO);

			controlador->desbloquear();

			// Asigna el archivo de configuracion necesario para cargar el proximo nivel.
			configFile = nextLevel;

		} else {
			//limpiarNivel();
			return ERROR_RESULTADO;
		}
	}

	return GANARON;
}


void* WorldHandler::run(){

	// Loop infinito de partidas. Cada partida comienza cuando hay suficientes jugadores para comenzar,
	// segun se indique en el archivo de partida cargado al levantar el servidor.
	while (true){

		// El programa espera a que haya una cantidad suficiente de jugadores.
		esperar();

		// Cuando se llena el mapa, comienza la partida.
		//resultado_t resultado =
		simularPartida();
	}

	return NULL;
}

resultado_t WorldHandler::loopPrincipal() {

	//Loop infinito en busca de mensajes para procesar
	bool quit = false; int cuentaRegresiva = 100;
	resultado_t resultado = ERROR_RESULTADO;

	while(!quit){

		float freq = 600.0f;
		for(int i=0;i<10;i++) {
			worldB2D->Step(1.0f/freq, 8, 5);
		};

		// Bloquea el controlador para aplicar cambios al modelo.
		controlador->bloquear();
		controlador->actualizar();
		controlador->desbloquear();

		// Verifica que haya jugadores conectados.
		if (controlador->estado.cantidadOnline() == 0) {
			cuentaRegresiva--;
			if (cuentaRegresiva == 0) quit = true;
			resultado = PERDIERON;
		} if (!controlador->modelo.quedanEnemigos()){
			cuentaRegresiva--;
			if (cuentaRegresiva == 0) quit = true;
			resultado = GANARON;
		}

		usleep(20000);

/*		if (army.isMapCleared()) {
			quit = true;
			resultado = GANARON;
		}

		if (!quedaPJvivo){
			quit = true;
			resultado = PERDIERON;
		}
*/
	}

	return resultado;
}
