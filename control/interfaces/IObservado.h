/*
 * IObservado.h
 *
 *  Created on: 3/9/2014
 *      Author: manuel
 */

#ifndef IOBSERVADO_H_
#define IOBSERVADO_H_

#include "IObservador.h"
#include "../../utiles/tipos.h"

class IObservado {
public:
	IObservado(){};
	virtual ~IObservado()
	{
		for( ListaObservadores::iterator it = oLista.begin(); it != oLista.end(); it++)
		{
			oLista.erase(it);
			if( *it != NULL )
				delete(*it);
		}
	};

	virtual void notificarObservadores(int EVENTO)
	{
		// recorro la lista de observadores haciendo que cada uno notifique del evento sucedido.
		for( ListaObservadores::iterator it = oLista.begin(); it != oLista.end(); it++)
		{
			(*it)->notificar(EVENTO);
		}
	}

	virtual void agregarObservador(IObservador* observador)
	{
		// agrego un observador a la lista.
		oLista.push_back(observador);
	};

	virtual void eliminarObservador(IObservador* observador)
	{
		if( oLista.size() == 0 ) return;

		ListaObservadores::iterator it = oLista.begin();

		// si tiene 1 solo elemnto, elimino el primero y listo.
		if( oLista.size() == 1 )
		{
			oLista.erase(it);
			delete(*it);
			return;
		}

		// recorro la lista hasta encontrar el observador que quiero eliminar,
		// el iterador me queda posicionado en el observador a eliminar.
		for( ; (*it) != observador; it++)
			;
		oLista.erase(it);
		delete(*it);
	};

private:
	ListaObservadores oLista;
};



#endif /* IOBSERVADO_H_ */
