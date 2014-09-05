/*
 * ObservadorPersonaje.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef OBSERVADORPERSONAJE_H_
#define OBSERVADORPERSONAJE_H_

#include "../modelo/Personaje.h"
#include "interfaces/IObservador.h"
#include "../utiles/tipos.h"

// el T DEBE SER EL NOMBRE EXACTO de una clase que implemente la interfaz INotificable
template<class T>
class Observador : public IObservador {
public:
	Observador() : puntero_al_objeto_a_notificar(NULL) {};
	Observador(T* p) : puntero_al_objeto_a_notificar(p) {};
	virtual ~Observador()
	{
		if( puntero_al_objeto_a_notificar != NULL ){
			delete(puntero_al_objeto_a_notificar);
			puntero_al_objeto_a_notificar = NULL;
		}
	};

	virtual void notificar(int EVENTO)
	{
		switch( EVENTO )
		{
		case ARRIBA: puntero_al_objeto_a_notificar->eventoArriba(); break;
		case DERECHA: puntero_al_objeto_a_notificar->eventoDerecha(); break;
		case IZQUIERDA: puntero_al_objeto_a_notificar->eventoIzquierda(); break;
		case ABAJO: puntero_al_objeto_a_notificar->eventoAbajo(); break;
		case RESTART: puntero_al_objeto_a_notificar->eventoRESTART(); break;
		}
	}

	void setPunteroANotificar(T* ptr)
	{
		puntero_al_objeto_a_notificar = ptr;
	}

private:
	T* puntero_al_objeto_a_notificar;
};



#endif /* OBSERVADORPERSONAJE_H_ */
