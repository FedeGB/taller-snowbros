/*
 * ITexturizable.h
 *
 *  Created on: 20/10/2014
 *      Author: manuel
 */

#ifndef ITEXTURIZABLE_H_
#define ITEXTURIZABLE_H_

#include <sstream>

#include "../Textura.h"
#include "../interfaces/IDibujable.h"

class ITexturizable : public IDibujable{
public:
	ITexturizable() : _tex(NULL), s(NULL), t(NULL){}
	virtual ~ITexturizable(){
		if( s != NULL )
			delete [] s;

		if( t != NULL )
			delete [] t;
	}

	void setCoord_s(float* _s){ s = _s; }
	void setCoord_t(float* _t){ t =_t; }

	virtual void setTex(Textura* t, float escalaX, float escalaY){
		_tex = t;
		_tex->mapearCoordenadas(this, escalaX, escalaY);
	}

protected:
	Textura* _tex;

	float32* s;
	float32* t;
};



#endif /* ITEXTURIZABLE_H_ */
