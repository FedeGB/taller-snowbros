/*
 * Inicializador.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: rodrizapico
 */

#include "Inicializador.h"

bool loadInitialValues(std::string& sConfig) {
	Logger& log = *Logger::Instancia();
	//abre el json y lo carga a un string
	fstream fConfig;
	fConfig.open("config.json", ios_base::in);
	if (!fConfig.is_open()) {
		if (!log.abrirLog(MAINLOG)) {
			log.crearLogs();
			std::cout << "Error al abrir archivo de log " << MAINLOG
					<< ", creando..." << std::endl;
			if (!log.abrirLog(MAINLOG)) {
				std::cout << "No se pudo crear el archivo de log.";
				return false;
			}
		}

		log.escribirLog(ERROR,
				"No se pudo encontrar o abrir el archivo config.json");
		log.cerrarLog();
		return false;
	}
	std::string newStr((std::istreambuf_iterator<char>(fConfig)),
			std::istreambuf_iterator<char>());
	sConfig = newStr;
	fConfig.close();

	if (!parsingOk(sConfig)) {
		fConfig.open("default.json", ios_base::in);
		if (!fConfig.is_open()) {
			if (!log.abrirLog(MAINLOG)) {
				log.crearLogs();
				std::cout << "Error al abrir archivo de log " << MAINLOG
						<< ", creando..." << std::endl;
				if (!log.abrirLog(MAINLOG)) {
					std::cout << "No se pudo crear el archivo de log.";
					return false;
				}
			}

			log.escribirLog("ERROR",
					"No se pudo encontrar o abrir el archivo default.json");
			log.cerrarLog();
			return false;
		}
		std::string newStr((std::istreambuf_iterator<char>(fConfig)),
				std::istreambuf_iterator<char>());
		sConfig = newStr;
		fConfig.close();
	}

	return true;
}

bool windowInit(Window ** w, int widthScreen, int heightScreen, float wRatio,
		float hRatio, std::string path_fondo) {
	*w = new Window();
	bool statusOK = (*w)->init(widthScreen, heightScreen, wRatio, hRatio,
			path_fondo);
	return statusOK;
}

void worldInit(b2World ** worldB2D, ContactListener * contactListener) {

	b2Vec2 gravedad(0, 25);
	*worldB2D = new b2World(gravedad);

	(*worldB2D)->SetContactListener(contactListener);

	return;
}

void pjInit(Window ** w, b2World ** worldB2D,  HandlerDeEventos * wHandlerEventos, std::string data)
{
	Logger& log = *Logger::Instancia();

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;

	// Parametros iniciales.
	b2dObjDef.type = b2_dynamicBody;
	float32 pj_x = get_node("x", "personaje", data, 5.0f);
	float32 pj_y = get_node("y", "personaje", data, 10.0f);

	float32 anchoMaximo = get_node("ancho-un", "escenario", data, 10.0f);
	float32 altoMaximo = get_node("alto-un", "escenario", data, 10.0f);

	// si la posicion del persona esta fuera del escenario, entonces lo posicionamos en el medio
	if( (pj_x > anchoMaximo) | (pj_y > altoMaximo) ){
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return;
		}
		log.escribirLog(WARNING, "No se puede inicializar al personaje fuera del escenario. Seteado por default al medio del escenario.");
		log.cerrarLog();
		pj_x = ( anchoMaximo * 0.5 ); pj_y = ( altoMaximo * 0.5 );
	}

	b2dObjDef.position.Set(pj_x, pj_y);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;
	b2dObjDef.bullet = true;
	//b2dObjDef.linearDamping = 0.1;

	//lo vinculo al mundo
	b2Body *pjB2D = (*worldB2D)->CreateBody(&b2dObjDef);

	//le doy forma
	float32 halfHeight = get_node("alto", "personaje", data, 1.4f);
	float32 halfWidth = get_node("ancho", "personaje", data, 1.2f);
	polygon.SetAsBox(halfWidth/1.1, halfHeight/1.1); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.density =  get_node("masa", "personaje", data, 20.0f); //le doy masa
	myFixtureDef.restitution = 0.0f;
	b2Fixture * bodyFixture = pjB2D->CreateFixture(&myFixtureDef); //le asigno la forma
	bodyFixture->SetUserData( (void*)0 );

    // Agrego el sensor para saltos
    polygon.SetAsBox(halfWidth/1.2, 0.15f, b2Vec2(0.0f,1.5f), 0);
	myFixtureDef.shape = &polygon; //defino que es un poligono
    myFixtureDef.isSensor = true;
	myFixtureDef.density = 1.0f; //le doy masa
	myFixtureDef.restitution = 0.0f;
    b2Fixture* footSensorFixture = pjB2D->CreateFixture(&myFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );

	Personaje * personaje = new Personaje();
	if(!personaje) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return;
		}
		log.escribirLog(ERROR, "No se pudo asignar memoria para al personaje.");
		log.cerrarLog();
		return;
	}

	personaje->setDimensiones(halfHeight * 2, halfWidth * 2);

	pjB2D->SetUserData(personaje);
	personaje->setB2DBody(pjB2D);

	(*w)->insertarFigura(personaje);
	personaje->cargarImagen( get_node("sprite-sheet", "personaje", data, "imagenes/playerSpritesheet.png") );

	Observador<Personaje>* observadorPersonaje = new Observador<Personaje>( personaje );
	if(!observadorPersonaje) {
		if (!log.abrirLog(WINDOWLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return;
		}
		log.escribirLog(ERROR, "No se pudo asignar memoria para el observador de personaje");
		log.cerrarLog();
		return;
	}
	wHandlerEventos->agregarObservador(observadorPersonaje);
}

int num_lados(std::string data) {
	if (!data.compare("circ"))
		return 1;
	if (!data.compare("rect"))
		return 4;
	if (!data.compare("poli"))
		return 3;
	if (!data.compare("irreg"))
		return 5;
	else
		return 0;
}

b2Body * createObject(std::string data, Window ** w, b2World ** wB2D, int num) {

	Logger& log = *Logger::Instancia();
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	b2PolygonShape poligon;
	IDibujable * figura;

	if (get_node("estatico", "objetos", data, num, false))
		b2dObjDef.type = b2_staticBody;
	else {
		b2dObjDef.type = b2_dynamicBody;
		b2dObjDef.bullet = true;
	}

	//posicion inicial
	b2dObjDef.position.x = get_node("x", "objetos", data, num, 1.0f);
	b2dObjDef.position.y = get_node("y", "objetos", data, num, 1.0f);
	b2dObjDef.angle = get_node("rot", "objetos", data, num, 0.0f) * DEGTORAD;

	//lo vinculo al mundo
	b2Body *_shape = (*wB2D)->CreateBody(&b2dObjDef);

	//le doy forma
	int lados = num_lados(get_node("tipo", "objetos", data, num, "rect"));
	//nLados=lados;
	switch (lados) { //dependiendo del numero de lados
	case 0: //0 es error
		if (!log.abrirLog(SHAPESLOG)) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return NULL;
		}
		log.escribirLog(ERROR, "El tipo de forma '" + get_node("tipo", "objetos", data, num,"rect") + "' no existe.");
		log.cerrarLog();
		(*wB2D)->DestroyBody(_shape);
		return NULL;

	case 1: //1 solo lado  = circulo
	{
		circle.m_radius = get_node("escala", "objetos", data, num, 1.0f); //defino el tamaño
		myFixtureDef.shape = &circle; //defino que es un circulo

		// Determina el tipo de figura para poder dibujarla.
		CirculoDibujable * circ = new CirculoDibujable();
		circ->setRadio(circle.m_radius);
		figura = circ;
		break;
	}
	case 4: // 4 lados caja
	{
		float32 halfHeight = get_node("alto", "objetos", data, num, 1.0f) / 2;
		float32 halfWidth = get_node("ancho", "objetos", data, num, 1.0f) / 2;
		poligon.SetAsBox(halfWidth, halfHeight); //le doy dimensiones
		myFixtureDef.shape = &poligon; //defino que es un poligono

		// Determina el tipo de figura para poder dibujarla.
		RectanguloDibujable * rect = new RectanguloDibujable();
		rect->setDimensiones(halfHeight * 2, halfWidth * 2);
		figura = rect;
		break;
	}
	case 5: { // poligonos irregulares

		float base = get_node("base", "objetos", data, num, 1.0f);
		float tapa = get_node("tapa", "objetos", data, num, 1.0f);
		float alto = get_node("alto", "objetos", data, num, 1.0f);
		float desp = get_node("desp", "objetos", data, num, 1.0f); //desplazamiento

		b2Vec2 *_point = new b2Vec2[lados];
		float32 centroX = ((2 * tapa * desp + base * desp + base * tapa
				+ pow(base, 2) + pow(tapa, 2)) / (3 * (base + tapa)));
		float32 centroY = ((alto * (base + 2 * tapa)) / (3 * (base + tapa)));
		_point[0].Set(-centroX, centroY);
		_point[1].Set(-centroX + base, centroY);
		_point[2].Set(-centroX + desp, centroY - alto);
		_point[3].Set(-centroX + desp + tapa, centroY - alto);
		poligon.Set(_point, 4);
		myFixtureDef.shape = &poligon;

		// Determina el tipo de figura para poder dibujarla.
		PoligonoIrregularDibujable * poli = new PoligonoIrregularDibujable();
		poli->setBase(base);
		poli->setTapa(tapa);
		poli->setAltura(alto);
		poli->setDesplazamiento(desp);
		figura = poli;
		break;
	}

	default: // 3, 5 o mas lados poligonos regulares

		lados = get_node("lados", "objetos", data, num, 3);
		float escala = get_node("escala", "objetos", data, num, 1.0f);

		b2Vec2 * _point = new b2Vec2[lados]; //creo un vector con los vertices
		for (int i = 0; i < lados; i++) {
			float angulo = (2 * i * PI / lados); //- (b2dObjDef.angle * 0.017469944f);
			_point[i].Set(escala * cos(angulo), escala * sin(angulo));
		} //les asigno la posicion

		poligon.Set(_point, lados);
		myFixtureDef.shape = &poligon;

		// Determina el tipo de figura para poder dibujarla.
		PoligonoRegularDibujable * poli = new PoligonoRegularDibujable();
		poli->setNumVertices(lados);
		poli->setEscala(escala);
		figura = poli;
		break;

	}

	if (b2dObjDef.type == b2_dynamicBody) {
		myFixtureDef.density = get_node("masa", "objetos", data, num, 1.0f); //le doy masa
		myFixtureDef.restitution = 0.15f;
		//myFixtureDef.friction = 0.1f;
	}
	myFixtureDef.friction = get_node("friccion", "objetos", data, num, 0.3f);
	b2Fixture * shapeFixture = _shape->CreateFixture(&myFixtureDef); //le asigno la forma
	if (b2dObjDef.type == b2_dynamicBody) shapeFixture->SetUserData((void*) 1);
	else shapeFixture->SetUserData((void*) 2);

	// Determina los parametros basicos de la figura.

	figura->setColor((get_node("color", "objetos", data, num, "FF0000")));
	figura->setPosicion(b2dObjDef.position.x, b2dObjDef.position.y);
	figura->setAngulo(b2dObjDef.angle);

	_shape->SetUserData(figura);

	(*w)->insertarFigura(figura);

	return _shape;
}

bool Inicializador::init(Window ** w, b2World ** worldB2D,
		ContactListener * contactListener, HandlerDeEventos * wHandlerEventos) {
	Logger& log = *Logger::Instancia();
	std::string sConfig;
	bool statusOK = true;
	statusOK = loadInitialValues(sConfig);
	if (!statusOK)
		return false;

	int heightScreen = get_node("alto-px", "escenario", sConfig, 480);
	int widthScreen = get_node("ancho-px", "escenario", sConfig, 640);

	float heightWorld = get_node("alto-un", "escenario", sConfig, 10.0f);
	float widthWorld = get_node("ancho-un", "escenario", sConfig, 10.0f);

	std::string path_fondo = get_node("imagen-fondo", "escenario", sConfig,
			"imagenes/fondo2.png");

	float heightRatio = heightScreen / heightWorld;
	float widthRatio = widthScreen / widthWorld;

	statusOK = windowInit(w, widthScreen, heightScreen, widthRatio, heightRatio, path_fondo);

	worldInit(worldB2D, contactListener);

	pjInit(w, worldB2D, wHandlerEventos, sConfig);

	if (!statusOK) {
		return -1;
	}

	int formas = get_size("objetos", sConfig);
	for (int i = 0; i < formas; i++) {
		createObject(sConfig, w, worldB2D, i);
	}
	bool overlap;
	for (b2Body *b = (*worldB2D)->GetBodyList(); b; b = b->GetNext()) {
		for (b2Body *b2 = b->GetNext(); b2; b2 = b2->GetNext()) {
			overlap = b2TestOverlap(b->GetFixtureList()->GetShape(), 0,
					b2->GetFixtureList()->GetShape(), 0,
					b->GetFixtureList()->GetBody()->GetTransform(),
					b2->GetFixtureList()->GetBody()->GetTransform());
			if (overlap) {
				if (!log.abrirLog(WINDOWLOG)) {
					log.crearLogs();
					std::cout << "Error al abrir archivo de log " << WINDOWLOG
							<< ", creando..." << std::endl;
					if (!log.abrirLog(WINDOWLOG)) {
						std::cout << "No se pudo crear el archivo de log.";
					}
				}
				string ss = "";
				ss += "objeto en la posicion ";
				ostringstream convert;   // stream used for the conversion

				convert << b2->GetPosition().x;
				ss+= convert.str();
				ss += ",";
				convert << b2->GetPosition().y;
				ss+= convert.str();
				ss += " borrado por solapamiento";
				log.escribirLog(WARNING, ss);
				log.cerrarLog();
				(*worldB2D)->DestroyBody(b);
				b = (*worldB2D)->GetBodyList();
				b2 = b->GetNext();
			}
		}
	}

	return true;
}

