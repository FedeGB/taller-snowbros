/*
 * Camara.h
 *
 *  Created on: Dec 6, 2014
 *      Author: rodrizapico
 */

#ifndef CAMARA_H_
#define CAMARA_H_

#include "../../matematica/FiguraGeometrica.h"
#include "../../interfaces/Notificable.h"
#include "../../servicios/LocalizadorDeServicios.h"

class ObjetoModelo;

class Camara: public Notificable {
public:
	Camara();
	virtual ~Camara();

	// Informa al objeto que sucedio un evento del tipo 'notificacion'.
	virtual void notificar(tipo_notificacion_t notificacion);

	// Ajusta la camara para que siga al objeto seleccionado.
	void enfocar(ObjetoModelo * objeto);

	// Deja de seguir al objeto que estuviera siguiendo. En vez de eso, se queda fija
	// donde estuviera.
	void desenfocar();

	// Configura la camara en modo libre. En este modo, la camara se mueve segun las pulsaciones
	// de teclado.
	// NOTA: al asignarle una posicion o enfocar la camara, se quita el modo libre.
	void modoLibre();

	// Asigna la posicion de la camara, en unidades logicas.
	// NOTA: la posicion dada indica el borde superior izquierdo de la camara.
	void asignarPosicion(float x, float y);

	// Asigna las dimensiones de la region del mapa que cubre la camara,
	// en unidades logicas.
	// NOTA: La relacion de aspecto debe ser aquella de la ventana
	// sobre la que corre el juego, en caso contrario puede pasar
	// cualquier cosa.
	void asignarDimensiones(float w, float h);

	// Inicializa la camara, una vez que le fueron asignadas dimensiones
	// y posicion inicial; o un objeto a seguir.
	// NOTA: Si se llama sin haber cargado los valores indicados anteriormente,
	// caos y desolacion.
	void inicializar();

	// Elimina cosas. Usarla.
	void limpiar();

	// Actualiza la posicion de la camara, si es que esta siguiendo un objeto.
	void actualizar();

	// Devuelve el origen de la camara.
	Vector2D obtenerOrigen();

	// Devuelve la escala camara -> pantalla.
	float obtenerEscala();

	// Determina si el objeto dado esta dentro de la region visible determinada por la camara.
	bool esVisible (ObjetoModelo * objeto);

	// Calcula el ancho de la pantalla.
	float calcularAncho();

	// Calcula el alto de la pantalla.
	float calcularAlto();

private:

	// Mueve la camara para que quede encuadrada dentro del mundo.
	void encuadrarEnMundo();

	float x, y, w, h;
	bool libre;
	bool acercarCamara, alejarCamara;
	bool ajustarPosicion;
	FiguraGeometrica * regionVisible;
	ObjetoModelo * objetoEnfocado;
	Vector2D posicionAnterior;
};

#endif /* CAMARA_H_ */
