/*
 * Camara.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#include "Camara.h"
#include "ObjetoModelo.h"

Camara::Camara() {
	regionVisible = NULL;
	objetoEnfocado = NULL;
	x = y = w = h = 0;
	libre = true;
	acercarCamara = false;
	alejarCamara = false;
	ajustarPosicion = false;
}

Camara::~Camara() {

}

// Informa al objeto que sucedio un evento del tipo 'notificacion'.
void Camara::notificar(tipo_notificacion_t notificacion){

	if (notificacion == ACERCARCAMARA){
		acercarCamara = true;
	}

	if (notificacion == ALEJARCAMARA){
		alejarCamara = true;
	}

	// TODO: sacar desplazamientos hardcodeados
	if (notificacion == MOVERPERSONAJESALTO && libre){
		std::cout << "detecte que tengo que mover la camara para arriba" << std::endl;
		x = obtenerOrigen().x;
		y = obtenerOrigen().y - 2;
	}

	if (notificacion == MOVERPERSONAJEABAJO && libre){
		x = obtenerOrigen().x;
		y = obtenerOrigen().y + 2;
	}

	if (notificacion == MOVERPERSONAJEIZQUIERDA && libre){
		x = obtenerOrigen().x - 2;
		y = obtenerOrigen().y;
	}

	if (notificacion == MOVERPERSONAJEDERECHA && libre){
		x = obtenerOrigen().x + 2;
		y = obtenerOrigen().y;
	}

}

// Ajusta la camara para que siga al objeto seleccionado.
void Camara::enfocar(ObjetoModelo * objeto){
	libre = false;
	objetoEnfocado = objeto;
}

// Deja de seguir al objeto que estuviera siguiendo. En vez de eso, se queda fija
// donde estuviera.
void Camara::desenfocar(){
	objetoEnfocado = NULL;
}

// Configura la camara en modo libre. En este modo, la camara se mueve segun las pulsaciones
// de teclado.
// NOTA: al asignarle una posicion o enfocar la camara, se quita el modo libre.
void Camara::modoLibre(){
	libre = true;
}

// Asigna la posicion de la camara, en unidades logicas.
// NOTA: la posicion dada indica el borde superior izquierdo de la camara.
void Camara::asignarPosicion(float px, float py){
	desenfocar();
	libre = false;
	x = px; y = py;
}

// Asigna las dimensiones de la region del mapa que cubre la camara,
// en unidades logicas.
// NOTA: La relacion de aspecto debe ser aquella de la ventana
// sobre la que corre el juego, en caso contrario puede pasar
// cualquier cosa.
void Camara::asignarDimensiones(float pw, float ph){
	w = pw; h = ph;
}

// Inicializa la camara, una vez que le fueron asignadas dimensiones
// y posicion inicial; o un objeto a seguir.
// NOTA: Si se llama sin haber cargado los valores indicados anteriormente,
// caos y desolacion.
void Camara::inicializar(){
	if (!objetoEnfocado) regionVisible = FiguraGeometrica::generarRectangulo(x,y,w,h,0);
	else {
		Vector2D posicion = objetoEnfocado->espacioOcupado->calcularBaricentro();
		regionVisible = FiguraGeometrica::generarRectangulo(posicion.x,posicion.y,w,h,0);
	}

	// La camara desea recibir eventos de zoom in / out, o de movimiento si esta en modo
	// libre.
	LocalizadorDeServicios::obtenerNotificador()->subscribirANotificaciones(this);
}

// Elimina cosas.
void Camara::limpiar(){
	LocalizadorDeServicios::obtenerNotificador()->finalizarNotificaciones(this);
	delete regionVisible;
}

// Mueve la camara para que quede encuadrada dentro del mundo.
void Camara::encuadrarEnMundo(){

	if (libre) return;

	Vector2D tamanio = LocalizadorDeServicios::obtenerInformacionPublica()->tamanioMapa;

	// Si la camara esta demasiado lejos, de forma que abarca mas que el mundo a lo
	// ancho, debe acercarse.
	if ( obtenerOrigen().x <= 1 && obtenerOrigen().x + calcularAncho() >= tamanio.x - 1) {
		acercarCamara = true;
		alejarCamara = false;
	}

	// Si la camara esta demasiado lejos, de forma que abarca mas que el mundo a lo
	// alto, debe acercarse.
	if ( obtenerOrigen().y <= 1 && obtenerOrigen().y + calcularAlto() >= tamanio.y - 1){
		acercarCamara = true;
		alejarCamara = false;
	}

	// Si determino que debe alejarse o acercarse la camara, retorna.
	if (acercarCamara) return;

	// En caso contrario, analiza si la camara se encuentra 'fuera' de los bordes del mapa.
	bool XModificado = false, YModificado = false;
	if (obtenerOrigen().x < 0.5) {
		ajustarPosicion = true;
		x = 0;
		XModificado = true;
	}
	if (obtenerOrigen().x + calcularAncho() > tamanio.x - 0.5) {
		ajustarPosicion = true;
		x = tamanio.x - calcularAncho();
		XModificado = true;
	}
	if (obtenerOrigen().y < 0.5) {
		ajustarPosicion = true;
		YModificado = true;
		y = 0;
	}
	if (obtenerOrigen().y + calcularAlto() > tamanio.y - 0.5) {
		ajustarPosicion = true;
		YModificado = true;
		y = tamanio.y - calcularAlto();
	}

	if (!XModificado) x = obtenerOrigen().x;
	if (!YModificado) y = obtenerOrigen().y;

}

// Actualiza la posicion de la camara, si es que esta siguiendo un objeto.
// NOTA: La camara mantiene siempre centrado al objeto enfocado.
// TODO: arreglar lo de arriba.
void Camara::actualizar(){

	if(objetoEnfocado){
		Vector2D posicionCamara = regionVisible->calcularBaricentro();
		Vector2D posicionObjeto = objetoEnfocado->espacioOcupado->calcularBaricentro();

		// 'Achico' la region visible, para verificar que el objeto
		// enfocado este en la region central de la misma.
		regionVisible->escalar(posicionCamara, 0.5);

		bool mover = false;
		// Si no es visible en la region reducida, debo mover la camara en la direccion dada.
		if(!this->esVisible(objetoEnfocado)) mover = true;

		// Recupero el tamanio original de la region visible.
		regionVisible->escalar(posicionCamara, 2);

		// Calcula el desplazamiento necesario de la camara, en base al desplazamiento
		// del objeto enfocado desde la ultima iteracion.
		Vector2D aux = (posicionObjeto - posicionAnterior);
		if (mover) {
			if (posicionObjeto.x == posicionAnterior.x && posicionObjeto.y == posicionAnterior.y){
				aux = ( posicionObjeto - posicionCamara ) * (1/10.0f);
			}
			regionVisible->trasladar(aux);
		}

		posicionAnterior = posicionObjeto;
	}

	this->encuadrarEnMundo();

	if (libre || ajustarPosicion){
		Vector2D posicionCamara = obtenerOrigen();
		Vector2D posicionNueva;
		posicionNueva.x = x;
		posicionNueva.y = y;

		regionVisible->trasladar((posicionNueva - posicionCamara));
		ajustarPosicion = false;
	}

	if(acercarCamara){
		//if (objetoEnfocado) regionVisible->escalar(objetoEnfocado->espacioOcupado->calcularBaricentro(), 0.99);
		regionVisible->escalar(obtenerOrigen(), 0.99);
		acercarCamara = false;
	}

	if (alejarCamara){
		//if (objetoEnfocado) regionVisible->escalar(objetoEnfocado->espacioOcupado->calcularBaricentro(), 1.01);
		regionVisible->escalar(obtenerOrigen(), 1.01);
		alejarCamara = false;
	}
}

// Devuelve el origen de la camara.
Vector2D Camara::obtenerOrigen(){
	return regionVisible->puntosOrdenados.front();
}

// Devuelve la escala camara -> pantalla.
float Camara::obtenerEscala(){

	float escala = LocalizadorDeServicios::obtenerInformacionPublica()->resolucionPantalla.x / calcularAncho();

	return escala;
}

// Determina si el objeto dado esta dentro de la region visible determinada por la camara.
bool Camara::esVisible (ObjetoModelo * objeto){

	for(std::list<Vector2D>::iterator it = objeto->espacioOcupado->puntosOrdenados.begin();
			it != objeto->espacioOcupado->puntosOrdenados.end(); it++){
		if (regionVisible->pertenece(*it)) 	return true;
	}
	return false;
}

// Calcula el ancho de la pantalla.
float Camara::calcularAncho(){

	std::list<Vector2D>::iterator actual = regionVisible->puntosOrdenados.begin();
	std::list<Vector2D>::iterator anterior = actual;
	actual++;

	Vector2D diferencia = (*actual) - (*anterior);

	return diferencia.x;
}

// Calcula el alto de la pantalla.
float Camara::calcularAlto(){

	Vector2D actual = regionVisible->puntosOrdenados.front();
	Vector2D anterior = regionVisible->puntosOrdenados.back();

	Vector2D diferencia = anterior - actual;

	return diferencia.y;
}
