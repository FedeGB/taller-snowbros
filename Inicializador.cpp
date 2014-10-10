/*
 * Inicializador.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: rodrizapico
 */

#include "Inicializador.h"

std::map<std::string, Textura*>* texturas = NULL;

bool loadInitialValues(std::string configFile, std::string& sConfig) {
	Logger& log = *Logger::Instancia();
	//abre el json y lo carga a un string
	fstream fConfig;
	fConfig.open(configFile.c_str(), ios_base::in);
	if (!fConfig.is_open()) {

		log.log(MAINLOG, WARNING,
				"No se pudo encontrar o abrir el archivo de configuracion. Cargando mapa por defecto.");
		fConfig.open("defaultConfig.json", ios_base::in);
		if (!fConfig.is_open()) {
			log.log(MAINLOG, ERROR,
					"No se pudo encontrar o abrir el archivo de configuracion por defecto.");
			return false;
		}
	}
	std::string newStr((std::istreambuf_iterator<char>(fConfig)),
			std::istreambuf_iterator<char>());
	sConfig = newStr;
	fConfig.close();

	if (!parsingOk(sConfig)) {
		log.log(MAINLOG, WARNING,
				"Hubo un problema al parsear el archivo de configuracion provisto. Cargando mapa por defecto.");
		fConfig.open("defaultConfig.json", ios_base::in);
		if (!fConfig.is_open()) {
			log.log(MAINLOG, ERROR,
					"No se pudo encontrar o abrir el archivo de configuracion por defecto.");
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

	b2Vec2 gravedad(0, 35);
	*worldB2D = new b2World(gravedad);
	(*worldB2D)->SetContactListener(contactListener);

	return;
}

Personaje * pjInit(Window ** w, b2World ** worldB2D,
		HandlerDeEventos * wHandlerEventos, std::string data) {

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
	if ((pj_x > anchoMaximo) | (pj_y > altoMaximo)) {
		log.log(WINDOWLOG, WARNING,
				"No se puede inicializar al personaje fuera del escenario. Seteado por default al medio del escenario.");
		pj_x = (anchoMaximo * 0.5);
		pj_y = (altoMaximo * 0.5);
	}

	b2dObjDef.position.Set(pj_x, pj_y);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;
	b2dObjDef.bullet = true;
	//b2dObjDef.linearDamping = 0.1;

	//lo vinculo al mundo
	b2Body *pjB2D = (*worldB2D)->CreateBody(&b2dObjDef);

	//le doy forma
	float32 halfHeight = get_node("alto", "personaje", data, 1.4f) / 2;
	float32 halfWidth = get_node("ancho", "personaje", data, 1.2f) / 2;
	polygon.SetAsBox(halfWidth, halfHeight); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.density = get_node("masa", "personaje", data, 20.0f); //le doy masa
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.friction = 0.0;
	b2Fixture * bodyFixture = pjB2D->CreateFixture(&myFixtureDef); //le asigno la forma
	bodyFixture->SetUserData((void*) 0);

	// Agrego el sensor para saltos
	polygon.SetAsBox(0.8 * halfWidth, 0.3f, b2Vec2(0.0f, halfHeight), 0);
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.isSensor = true;
	myFixtureDef.density = 1.0f; //le doy masa
	myFixtureDef.restitution = 0.0f;
	b2Fixture* footSensorFixture = pjB2D->CreateFixture(&myFixtureDef);
	footSensorFixture->SetUserData((void*) 3);

	Personaje * personaje = new Personaje();
	if (!personaje) {

		log.log(WINDOWLOG, ERROR,
				"No se pudo asignar memoria para el personaje.");
		return NULL;
	}

	personaje->setDimensiones(halfHeight * 2, halfWidth * 2);
	personaje->setPosicion(pjB2D->GetPosition());

	pjB2D->SetUserData(personaje);
	personaje->setB2DBody(pjB2D);

	(*w)->insertarFigura(personaje);
	personaje->cargarImagen(
			get_node("sprite-sheet", "personaje", data,
					"imagenes/playerSpritesheet.png"));

	Observador<Personaje>* observadorPersonaje = new Observador<Personaje>(
			personaje);
	if (!observadorPersonaje) {
		log.log(WINDOWLOG, ERROR,
				"No se pudo asignar memoria para el observador de personaje.");
		return NULL;
	}
	wHandlerEventos->agregarObservador(observadorPersonaje);

	return personaje;
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

Camera * cameraInit(b2World ** worldB2D, HandlerDeEventos * wHandlerEventos,
		b2Vec2 position, float32 windowWidth, float32 windowHeight) {

	Logger& log = *Logger::Instancia();

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;

	// Parametros iniciales.
	b2dObjDef.type = b2_dynamicBody;
	b2dObjDef.gravityScale = 0;
	float32 cameraX = position.x; //+ (windowWidth / 2) * WINDOWTOWORLDSCALE;
	float32 cameraY = position.y; //+ (windowHeight / 2) * WINDOWTOWORLDSCALE;

	b2dObjDef.position.Set(cameraX, cameraY);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;

	//lo vinculo al mundo
	b2Body *cameraB2D = (*worldB2D)->CreateBody(&b2dObjDef);

	//le doy forma
	float32 halfWidth = (windowWidth / 2) * 0.05f;
	float32 halfHeight = (windowHeight / 2) * 0.05f;
	polygon.SetAsBox(halfWidth, halfHeight); //le doy dimensiones
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.isSensor = true;

	b2Fixture * bodyFixture = cameraB2D->CreateFixture(&myFixtureDef); //le asigno la forma
	bodyFixture->SetUserData((void*) 4);

	Camera * camera = new Camera(windowWidth, windowHeight, 0.05f);
	if (!camera) {
		log.log(WINDOWLOG, ERROR, "No se pudo asignar memoria para la camara.");
		return NULL;
	}

	cameraB2D->SetUserData(camera);
	camera->setB2DBody(cameraB2D);

	Observador<Camera>* observadorCamera = new Observador<Camera>(camera);
	if (!observadorCamera) {
		log.log(WINDOWLOG, ERROR,
				"No se pudo asignar memoria para el observador de camara.");
		return NULL;
	}
	wHandlerEventos->agregarObservador(observadorCamera);

	return camera;
}

b2Body * createObject(std::string data, Window ** w, b2World ** wB2D, int num) {

	Logger& log = *Logger::Instancia();
	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2CircleShape circle;
	b2PolygonShape poligon;
	IDibujable * figura;

	std::string tex_path;
//	std::map<std::string, Textura*>* texturas = new std::map<std::string, Textura*>();

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

	int AUX = lados;
	//nLados=lados;
	switch (lados) { //dependiendo del numero de lados

	case 0: //0 es error
		log.log(SHAPESLOG, ERROR,
				"El tipo de forma '"
						+ get_node("tipo", "objetos", data, num, "rect")
						+ "' no existe.");
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

		tex_path = get_node("textura", "objetos", data, num, "vacia");
		Textura* tex = NULL;
	// chequeo si tiene textura asignada
		if ( tex_path.compare("vacia") != 0) {
		// me fijo si ya esta creada en memoria la textura
			if (texturas->count(tex_path) == 0 ) {
			// si NO esta creada, la creo y la agrego al map de texturas
				tex = new Textura;
				tex->generar(tex_path);
				(*texturas)[ tex_path ] = tex;
			}else
			// si esta creada, se la asigno al nuevo objeto
				tex = (*texturas)[tex_path];

			float tex_escalaX = get_node("tex_escalaX", "objetos", data, num, 1.0f);
			float tex_escalaY = get_node("tex_escalaY", "objetos", data, num, 1.0f);
			rect->setTex(tex, tex_escalaX, tex_escalaY);
		}

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
		tex_path = get_node("textura", "objetos", data, num, "vacia");

		Textura* tex = NULL;
	// chequeo si tiene textura asignada
		if ( tex_path.compare("vacia") != 0) {
		// me fijo si ya esta creada en memoria la textura
			if (texturas->count(tex_path) == 0 ) {
			// si NO esta creada, la creo y la agrego al map de texturas
				tex = new Textura;
				tex->generar(tex_path);
				(*texturas)[ tex_path ] = tex;
			}else
			// si esta creada, se la asigno al nuevo objeto
				tex = (*texturas)[tex_path];

			float tex_escalaX = get_node("tex_escalaX", "objetos", data, num, 1.0f);
			float tex_escalaY = get_node("tex_escalaY", "objetos", data, num, 1.0f);
			poli->setTex(tex, tex_escalaX, tex_escalaY);
		}

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
		tex_path = get_node("textura", "objetos", data, num, "vacia");
		Textura* tex = NULL;
		// chequeo si tiene textura asignada
		if ( tex_path.compare("vacia") != 0) {
		// me fijo si ya esta creada en memoria la textura
			if (texturas->count(tex_path) == 0 ) {
			// si NO esta creada, la creo y la agrego al map de texturas
				tex = new Textura;
				tex->generar(tex_path);
				(*texturas)[ tex_path ] = tex;
			}else
			// si esta creada, se la asigno al nuevo objeto
				tex = (*texturas)[tex_path];

			float tex_escalaX = get_node("tex_escalaX", "objetos", data, num, 1.0f);
			float tex_escalaY = get_node("tex_escalaY", "objetos", data, num, 1.0f);
			poli->setTex(tex, tex_escalaX, tex_escalaY);
		}

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
	if (b2dObjDef.type == b2_dynamicBody)
		shapeFixture->SetUserData((void*) 1);
	else
		shapeFixture->SetUserData((void*) 2);

	// Determina los parametros basicos de la figura.

	figura->setColor((get_node("color", "objetos", data, num, "FF0000")));
	figura->setPosicion(b2dObjDef.position.x, b2dObjDef.position.y);
	figura->setAngulo(b2dObjDef.angle);

	_shape->SetUserData(figura);

	(*w)->insertarFigura(figura);

	return _shape;
}

void checkBoundsAndOverlap(b2World ** worldB2D, float32 widthWorld,
		float32 heightWorld) {

	Logger& log = *Logger::Instancia();

	bool overlap;
	b2Body *b = (*worldB2D)->GetBodyList();
	while (b) {
		if (b->GetPosition().x > widthWorld || b->GetPosition().y > heightWorld
				|| b->GetPosition().x < 0.0 || b->GetPosition().y < 0.0) {

			ostringstream message;   // stream used for the conversion
			message << "El objeto en la posicion " << b->GetPosition().x << ","
					<< b->GetPosition().y
					<< " se encuentra fuera del mapa. Borrado.";

			log.log(WINDOWLOG, WARNING, message.str());

			(*worldB2D)->DestroyBody(b);
			b = (*worldB2D)->GetBodyList();
			continue;
		}

		bool skip = false;
		for (b2Body *b2 = b->GetNext(); b2; b2 = b2->GetNext()) {
			overlap = b2TestOverlap(b->GetFixtureList()->GetShape(), 0,
					b2->GetFixtureList()->GetShape(), 0,
					b->GetFixtureList()->GetBody()->GetTransform(),
					b2->GetFixtureList()->GetBody()->GetTransform());
			if (overlap) {

				ostringstream message;
				message << "Objeto en la posicion " << b->GetPosition().x << ","
						<< b->GetPosition().y << " borrado por solapamiento.";

				log.log(WINDOWLOG, WARNING, message.str());

				(*worldB2D)->DestroyBody(b);
				b = (*worldB2D)->GetBodyList();
				skip = true;
				break;
			}
		}
		if (!skip)
			b = b->GetNext();
	}
}

void addWorldBorders(b2World ** worldB2D, float32 widthWorld,
		float32 heightWorld) {

	Logger& log = *Logger::Instancia();

	b2BodyDef b2dObjDef;
	b2FixtureDef myFixtureDef;
	b2PolygonShape polygon;

	b2dObjDef.type = b2_staticBody;

	b2dObjDef.position.Set(widthWorld / 2, -0.5f);
	b2dObjDef.angle = 0;
	b2dObjDef.fixedRotation = true;

	//lo vinculo al mundo
	b2Body * upperBorderB2D = (*worldB2D)->CreateBody(&b2dObjDef);

	//le doy forma
	polygon.SetAsBox(widthWorld / 2, 0.5f, b2Vec2(0.0f, 0.0f), 0);
	myFixtureDef.shape = &polygon; //defino que es un poligono
	myFixtureDef.isSensor = true;
	b2Fixture* fixture = upperBorderB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData((void*) 7);

	b2dObjDef.position.Set(widthWorld / 2, heightWorld + 0.5f);
	b2Body * bottomBorderB2D = (*worldB2D)->CreateBody(&b2dObjDef);
	fixture = bottomBorderB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData((void*) 8);

	b2dObjDef.position.Set(-0.5f, heightWorld / 2);
	b2Body * leftBorderB2D = (*worldB2D)->CreateBody(&b2dObjDef);
	polygon.SetAsBox(0.5f, heightWorld / 2, b2Vec2(0.0f, 0.0f), 0);
	myFixtureDef.shape = &polygon;
	fixture = leftBorderB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData((void*) 5);

	b2dObjDef.position.Set(widthWorld + 0.5f, heightWorld / 2);
	b2Body * rightBorderB2D = (*worldB2D)->CreateBody(&b2dObjDef);
	fixture = rightBorderB2D->CreateFixture(&myFixtureDef);
	fixture->SetUserData((void*) 6);

}

bool Inicializador::init(std::string configFile, Window ** w,
		b2World ** worldB2D, ContactListener * contactListener,
		HandlerDeEventos * wHandlerEventos) {

	if ( texturas != NULL ){
		delete texturas;
	}
	texturas = new std::map<std::string, Textura*>();


	Logger& log = *Logger::Instancia();
	std::string sConfig;
	bool statusOK = true;
	statusOK = loadInitialValues(configFile, sConfig);
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

	statusOK = windowInit(w, widthScreen, heightScreen, widthRatio, heightRatio,
			path_fondo);

	worldInit(worldB2D, contactListener);

	Personaje * pj = pjInit(w, worldB2D, wHandlerEventos, sConfig);

	if (!statusOK) {
		return -1;
	}

	int formas = get_size("objetos", sConfig);
	for (int i = 0; i < formas; i++) {
		createObject(sConfig, w, worldB2D, i);
	}

//	printf("texturas creadas: %i\n", texturas->size());

	checkBoundsAndOverlap(worldB2D, widthWorld, heightWorld);

	Camera * camera = cameraInit(worldB2D, wHandlerEventos, pj->getPosicion(),
			widthScreen, heightScreen);

	(*w)->setCamera(camera);

	addWorldBorders(worldB2D, widthWorld, heightWorld);

	log.log(MAINLOG, OK, "Se ha inicializado correctamente el mundo.");

	return true;
}

