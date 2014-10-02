#include "parser.h"
//#include "json.h"
#include <sstream>
#include <cctype>

using namespace std;

bool parsingOk(string file){
		Json::Value root;
		Json::Reader reader(Json::Features::strictMode());
		Logger& log = *Logger::Instancia();
		bool parsingOk = reader.parse(file, root);
		if (!parsingOk) {
			if (!log.abrirLog(PARSERLOG)) {
				std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
				return false;
			}
			string errorLectura;
			errorLectura = "no se pudo leer el archivo "
					+ reader.getFormattedErrorMessages();
			log.escribirLog(ERROR, errorLectura);
			log.cerrarLog();
			return false;
		}
		return true;
}

string get_node(string data, string param, string file, char* defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo: "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING, "campo '" + data + "' de '" + param + "' vacio. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][data].isString()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"tipo incorrecto del campo '" + data + "' de '" + param
						+ "'. Se espera string. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	std::string result = root[param].get(data, defaultData).asString();
	if(data.compare("color") == 0) {
		if(!validarColor(result)) {
			if (!log.abrirLog(PARSERLOG)) {
				std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
				return defaultData;
			}
			log.escribirLog(WARNING, "El color " + result + " del campo " + data
							+ " de " + param +" no es valido. Cargando datos por defecto.");
			log.cerrarLog();
			return defaultData;
		}
		return result.substr(1);
	}
	return result;
}

string get_node(char* datas, string param, string file, char* defaultData) {
	string data(datas);
	return get_node(data, param, file, defaultData);
}

string get_node(string data, string param, string file, int field,
		char* defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "no se pudo leer el archivo "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"campo '" + data + "' de '" + param + "' vacio, del elemento " + s + ". Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][field][data].isString()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				" tipo incorrecto del campo " + data + " de " + param
						+ " del elemento " + s + ". Se espera string. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	std::string result = root[param][field].get(data, defaultData).asString();
	if(data.compare("color") == 0) {
		if(!validarColor(result)) {
			if (!log.abrirLog(PARSERLOG)) {
				std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
				return defaultData;
			}
			log.escribirLog(WARNING, "El color " + result + " del elemento " + s + " de " + param + " no es valido. Cargando datos por defecto.");
			log.cerrarLog();
			return defaultData;
		}
		return result.substr(1);
	}
	return result;
}

int get_node(string data, string param, string file, int defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "No se pudo leer el archivo "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING, "Campo '" + data + "' de '" + param + "' vacio. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][data].isInt()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				" Tipo incorrecto del campo '" + data + "' de '" + param
						+ "'. Se espera 'int'. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	float result = root[param].get(data, defaultData).asInt();
	if(data.compare("x") == 0 || data.compare("y") == 0 || data.compare("masa") == 0
		|| data.compare("base") == 0 || data.compare("tapa") == 0 || data.compare("desp") == 0
		|| data.compare("alto") == 0 || data.compare("ancho") == 0 || data.compare("friccion") == 0 ) {
		if(result < 0) {
			if (!log.abrirLog(PARSERLOG)) {
				std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
				return defaultData;
			}
			log.escribirLog(WARNING, "El valor de " + data + " de " + param + " no puede ser negativo. Cargando datos por defecto.");
			log.cerrarLog();
			return defaultData;
		}
	}
	if(data.compare("rot") == 0) {
		result = ajustarAngulo(result);
	}
	return result;
}

int get_node(char* datas, string param, string file, int defaultData) {
	string data(datas);
	return get_node(data, param, file, defaultData);
}

int get_node(string data, string param, string file, int field,
		int defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "No se pudo leer el archivo: "
				+ reader.getFormattedErrorMessages() +".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"campo '" + data + "' de '" + param + "' vacio, del elemento " + s + ". Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][field][data].isInt()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				" Tipo incorrecto del campo '" + data + "' de '" + param
						+ "' del elemento " + s + ". Se espera 'int'. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	int result = root[param][field].get(data, defaultData).asInt();
	if(data.compare("lados")<3 ||data.compare("lados")>8){
		if (!log.abrirLog(PARSERLOG)) {
						std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
						return defaultData;
					}
					log.escribirLog(WARNING, "El valor de " + data + " de " + param + " del elemento " + s + " no puede ser menor a 3 o mayor a 8. Cargando datos por defecto.");
					log.cerrarLog();
					return defaultData;
				}

	if(data.compare("x") == 0 || data.compare("y") == 0 || data.compare("masa") == 0
		|| data.compare("base") == 0 || data.compare("tapa") == 0 || data.compare("desp") == 0
		|| data.compare("alto") == 0 || data.compare("ancho") == 0 || data.compare("friccion") == 0  ) {
		if(result < 0) {
			if (!log.abrirLog(PARSERLOG)) {
				std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
				return defaultData;
			}
			log.escribirLog(WARNING, "El valor de " + data + " de " + param + " del elemento " + s + " no puede ser negativo. Cargando datos por defecto.");
			log.cerrarLog();
			return defaultData;
		}
	}
	if(data.compare("rot") == 0) {
		result = ajustarAngulo(result);
	}
	return result;
}

float get_node(string data, string param, string file, float defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "No se pudo leer el archivo "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING, "Campo '" + data + "' de '" + param + "' vacio. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][data].isNumeric()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"Tipo incorrecto del campo '" + data + "' de '" + param
						+ "'. Se espera 'float'. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	float result = root[param].get(data, defaultData).asFloat();
	if(data.compare("x") == 0 || data.compare("y") == 0 || data.compare("masa") == 0
		|| data.compare("base") == 0 || data.compare("tapa") == 0
		|| data.compare("alto") == 0 || data.compare("ancho") == 0 || data.compare("friccion") == 0 ) {
		if(result < 0) {
			if (!log.abrirLog(PARSERLOG)) {
				std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
				return defaultData;
			}
			log.escribirLog(WARNING, "El valor de " + data + " de " + param + " no puede ser negativo. Cargando datos por defecto.");
			log.cerrarLog();
			return defaultData;
		}
	}
	if(data.compare("rot") == 0) {
		result = (float)ajustarAngulo((int)result);
	}
	return result;
}

float get_node(char* datas, string param, string file, float defaultData) {
	string data(datas);
	return get_node(data, param, file, defaultData);
}

float get_node(string data, string param, string file, int field,
		float defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "No se pudo leer el archivo "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"Campo '" + data + "' de '" + param + "' vacio, del elemento " + s + ". Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][field][data].isNumeric()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"Tipo incorrecto del campo '" + data + "' de '" + param
						+ "' del elemento " + s + ". Se espera 'int'. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	float result = root[param][field].get(data, defaultData).asFloat();
	if(data.compare("x") == 0 || data.compare("y") == 0 || data.compare("masa") == 0
		|| data.compare("base") == 0 || data.compare("tapa") == 0
		|| data.compare("alto") == 0 || data.compare("ancho") == 0 || data.compare("friccion") == 0 ) {
		if(result < 0) {
			if (!log.abrirLog(PARSERLOG)) {
				std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
				return defaultData;
			}
			log.escribirLog(WARNING, "El valor de " + data + " de " + param + " del elemento " + s + " no puede ser negativo. Cargando datos por defecto.");
			log.cerrarLog();
			return defaultData;
		}
	}
	if(data.compare("rot") == 0) {
		result = (float)ajustarAngulo((int)result);
	}
	return result;
}

bool get_node(string data, string param, string file, bool defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "No se pudo leer el archivo "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING, "Campo '" + data + "' de '" + param + "' vacio. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][data].isBool()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"Tipo incorrecto del campo '" + data + "' de '" + param
						+ "'. Se espera 'Bool'. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	return root[param].get(data, defaultData).asBool();
}

bool get_node(char* datas, string param, string file, bool defaultData) {
	string data(datas);
	return get_node(data, param, file, defaultData);
}

bool get_node(string data, string param, string file, int field,
		bool defaultData) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	std::string s;
	std::stringstream out;
	out << field;
	s = out.str();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		string errorLectura;
		errorLectura = "No se pudo leer el archivo "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return defaultData;
	}
	if (root[param][field][data].empty()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"Campo '" + data + "' de '" + param + "' vacio, del elemento " + s + ". Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	if (!root[param][field][data].isBool()) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return defaultData;
		}
		log.escribirLog(WARNING,
				"Tipo incorrecto del campo '" + data + "' de '" + param
						+ "' del elemento " + s + ". Se espera 'int'. Cargando datos por defecto.");
		log.cerrarLog();
		return defaultData;
	}
	return root[param][field].get(data, defaultData).asBool();
}

int get_size(string param, string file) {
	Json::Value root;
	Json::Reader reader;
	Logger& log = *Logger::Instancia();
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog(PARSERLOG)) {
			std::cout << "Error al abrir archivo de log " << PARSERLOG << std::endl;
			return -1;
		}
		string errorLectura;
		errorLectura = "No se pudo leer el archivo "
				+ reader.getFormattedErrorMessages() + ".";
		log.escribirLog(ERROR, errorLectura);
		log.cerrarLog();
		return -1;
	}
	return root[param].size();

}

bool validarColor(std::string parametro) {
	if (parametro[0] != '#') {
		return false;
	}
	int n = parametro.length();
	if(n > 7 || n < 7) {
		return false;
	}
	for(int i = 1; i < n; i++) {
		if(!isxdigit(parametro[i])) {
			return false;
		}
	}
	return true;
}

int ajustarAngulo(int angulo) {
	int aux = angulo;
	if(angulo < 0) {
		if(angulo < -360) {
			aux = angulo % 360;
		}
		aux = 360 + aux;
	} else if (angulo > 360) {
		aux = angulo % 360;
	}
	return aux;
}
