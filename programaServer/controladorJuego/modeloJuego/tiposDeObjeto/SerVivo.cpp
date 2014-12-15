/*
 * SerVivo.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "SerVivo.h"

SerVivo::SerVivo(){
	comenzoAtaque = false;
	acumuladorAtaque = 0;
	numContactosPie = 0;
	moviendoDerecha = moviendoIzquierda = saltando = atacando = false;
	estado = PARADO;
	reconocerDestruccion = 0;
	salud = 3;
	sumergido = false;
	factorEscalaVelocidad = 1.0f;
	cayoPorAgujero = false;
	sorpresaCorrerActiva = false;
}

// Levanta el ser vivo desde el archivo de configuracion Json.
SerVivo::SerVivo(std::string sConfig, int numeroObjeto){

	rotacion = 0.0f;
	orientacion = DERECHA;
	comenzoAtaque = false;
	acumuladorAtaque = 0;
	numContactosPie = 0;
	moviendoDerecha = moviendoIzquierda = saltando = atacando = false;
	estado = PARADO;
	reconocerDestruccion = 0;
	salud = 3;
	sumergido = false;
	factorEscalaVelocidad = 1.0f;
	cayoPorAgujero = false;
	sorpresaCorrerActiva = false;

	// Obtiene el espacio ocupado por el personaje.
	float x = get_node("x", "objetos", sConfig, numeroObjeto, 20.0f);
	float y = get_node("y", "objetos", sConfig, numeroObjeto, 20.0f);
	float ancho = get_node("ancho", "objetos", sConfig, numeroObjeto, 2.8f);
	float alto = get_node("alto", "objetos", sConfig, numeroObjeto, 2.4f);

	// Carga los puntos del personaje.
	espacioOcupado = new FiguraGeometrica();
	Vector2D punto;
	// Carga los puntos del ladrillo.
	punto.x = x - ancho / 2; punto.y = y - alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x + ancho / 2; punto.y = y - alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x + ancho / 2; punto.y = y + alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);

	punto.x = x - ancho / 2; punto.y = y + alto / 2;
	espacioOcupado->puntosOrdenados.push_back(punto);
}

SerVivo::~SerVivo(){

}

// Aplica el danio indicado.
void SerVivo::aplicarDanio(float danio){

	salud -= danio;
}

// Modifica los contactos de los pies para determinar si esta en el aire.
void SerVivo::modificarContactosPie(int num){
	numContactosPie += num;
}

// Actualiza la informacion del objeto para poder dibujarlo.
void SerVivo::actualizar(){

	// Actualiza la posicion y rotacion.
	ObjetoModelo::actualizar();

	// Verifica si el personaje se encuentra en el aire.
	bool enElAire = (numContactosPie <= 0 ? true : false);

	float32 desiredXVel = 0, desiredYVel = 0;
	b2Vec2 velActual = cuerpoB2D->GetLinearVelocity() ;

	if( sumergido ){
		cuerpoB2D->SetGravityScale(0.5f);
		if (sorpresaCorrerActiva) factorEscalaVelocidad = 0.75f;
		else factorEscalaVelocidad = 0.5f;
	}
	else{
		cuerpoB2D->SetGravityScale(1.0f);
		if (sorpresaCorrerActiva) factorEscalaVelocidad = 1.5f;
		else factorEscalaVelocidad = 1.0f;
	}

	if (estado == ATRAPADO) return;

	// Verifica si debe moverse a la izquierda.
	if (moviendoIzquierda){
		orientacion = IZQUIERDA;
		estado = CAMINANDO;
		desiredXVel = -14 * factorEscalaVelocidad;
	}

	// Verifica si debe moverse a la derecha.
	if (moviendoDerecha){
		orientacion = DERECHA;
		estado = CAMINANDO;
		desiredXVel = 14 * factorEscalaVelocidad;
	}

	// Verifica si debe saltar.
	if ( saltando && (!enElAire || sumergido) ){
		estado = SALTANDO;
		desiredYVel = -20 * factorEscalaVelocidad;
	} else if (enElAire){
		desiredYVel = velActual.y;
	} else desiredYVel = 0;

	// Calcula las velocidades deseadas segun la direccion de movimiento.
	float32 velXChange = desiredXVel - velActual.x ;
	float32 velYChange = desiredYVel - velActual.y ;

	// Si ninguna tecla de direccion esta presionada, el PJ se debe quedar quieto.
	if (!moviendoIzquierda && !moviendoDerecha ){
		estado = PARADO;
		velXChange = -velActual.x;
	}

	if (enElAire) estado = SALTANDO;

	// Calcula los impulsos a aplicar segun en que direccion se esta moviendo el PJ.
	float impulseX = cuerpoB2D->GetMass() * velXChange ;
	float impulseY = cuerpoB2D->GetMass() * velYChange ;
	cuerpoB2D->ApplyLinearImpulse( b2Vec2(impulseX, impulseY), cuerpoB2D->GetWorldCenter(), true);
}
