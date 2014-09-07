#include "parser.h"
using namespace std;

string get_node(string data, string param, string file, char* defaultData) {
	Json::Value root;
	Json::Reader reader;
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		string errorLectura;
		errorLectura << "no se pudo leer el archivo "
				<< reader.getFormattedErrorMessages() << endl;
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("ERROR", "campo vacio");
		log.cerrarLog();
	}
	return root[param].get(data, defaultData).asString();

}

string get_node(char* datas, string param, string file, char* defaultData) {
	string data(datas);
	Json::Value root;
	Json::Reader reader;
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		string errorLectura;
		errorLectura << "no se pudo leer el archivo "
				<< reader.getFormattedErrorMessages() << endl;
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("ERROR", "campo vacio");
		log.cerrarLog();
	}
	return root[param].get(data, defaultData).asString();

}

string get_node(string data, string param, string file, int field,
		char* defaultData) {
	Json::Value root;
	Json::Reader reader;
	bool parsingOk = reader.parse(file, root);
	if (!parsingOk) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		string errorLectura;
		errorLectura << "no se pudo leer el archivo "
				<< reader.getFormattedErrorMessages() << endl;
		log.escribirLog("ERROR", errorLectura);
		log.cerrarLog();
	}
	if (root[param][field].empty()) {
		if (!log.abrirLog("Parser.log")) {
			std::cout << "Error al abrir archivo de log" << std::endl;
			return false;
		}
		log.escribirLog("ERROR", "campo vacio");
		log.cerrarLog();
	}
	return root[param][field].get(data, defaultData).asString();
}
