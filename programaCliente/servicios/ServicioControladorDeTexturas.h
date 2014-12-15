/*
 * ControladorDeTexturas.h
 *
 *  Created on: Dec 4, 2014
 *      Author: rodrizapico
 */

#ifndef CONTROLADORDETEXTURAS_H_
#define CONTROLADORDETEXTURAS_H_

#include "../vista/Textura.h"

enum tipo_textura_t{
	BOTON1,
	BOTON2,
	FONDO,
	CAJADETEXTO,
	PJ,
	ENEMIGOESTANDAR,
	ENEMIGOFUEGO,
	LADRILLO,
	LAGUNA,
	AGUJERO,
	BOLADEFUEGO,
	BOLADENIEVE,
	PELOTADENIEVE,
	BOLAENEMIGOPARCIAL,
	INMUNIDAD,
	SORPRESACORRER,
	SORPRESAPOTENTE,
	SORPRESALEJOS,
};

enum estilo_texto_t{
	PANTALLAINICIARSESION,
	ESTADOJUGADOR,
};

class ServicioControladorDeTexturas {
public:
	virtual ~ServicioControladorDeTexturas(){};

	// Devuelve la textura correspondiente a tipoTextura.
	virtual Textura * obtenerTextura(tipo_textura_t tipoTextura) = 0;

	// Devuelve una textura correspondiente al texto pedido.
	// A diferencia de las texturas de elementos de la UI, las texturas de
	// textos deben ser liberadas cuando se terminan de utilizar.
	virtual Textura * generarTexturaTexto(std::string texto, estilo_texto_t estilo) = 0;
};

#endif /* CONTROLADORDETEXTURAS_H_ */
