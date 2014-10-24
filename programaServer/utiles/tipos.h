/*
 * tipos.h
 *
 *  Created on: 2/9/2014
 *      Author: manuel
 */

#ifndef TIPOS_H_
#define TIPOS_H_

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

#define PI 3.14159265
const float32 DEGTORAD = 0.0174532925199432957f;
const float32 RADTODEG = 57.295779513082320876f;

// Convierte a string.
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


// Utiles para la funcion split definida abajo.
#include <cstddef>
enum empties_t { empties_ok, no_empties };


// Separa un string dado (s), segun una serie de dalimitadores (delimiters),
// y devuelve el resultado en result.
template <typename Container>
Container& split( Container& result, const typename Container::value_type& s,
  const typename Container::value_type& delimiters,
  empties_t empties = empties_ok )
{
  result.clear();
  size_t current;
  size_t next = -1;
  do
  {
    if (empties == no_empties)
    {
      next = s.find_first_not_of( delimiters, next + 1 );
      if (next == Container::value_type::npos) break;
      next -= 1;
    }
    current = next + 1;
    next = s.find_first_of( delimiters, current );
    result.push_back( s.substr( current, next - current ) );
  }
  while (next != Container::value_type::npos);
  return result;
}

class Tamano {
public:
	Tamano();
	inline Tamano(int alto, int ancho) : tAlto(alto) , tAncho(ancho) {};
	virtual ~Tamano(){};

	inline int alto(){
		return tAlto;
	}

	inline void alto(int a){
		tAlto = a;
	}

	inline int ancho(){
		return tAncho;
	}

	inline void ancho(int a){
		tAncho = a;
	}

	inline void operator=(Tamano otroTamano){
		tAlto = otroTamano.alto();
		tAncho = otroTamano.ancho();
	}

private:
	int tAlto, tAncho;
};

enum TECLAS{
	ARRIBA,
	ABAJO,
	IZQUIERDA,
	DERECHA,
	SOLTOARRIBA,
	SOLTOABAJO,
	SOLTOIZQUIERDA,
	SOLTODERECHA,
	RESTART,
};

enum WORLDITEMS{
	CIRCULO,
	CUADRILATERO,
	POLIGONOREGULAR,
	PJ,
};

enum sprite_t{
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
#endif /* TIPOS_H_ */
