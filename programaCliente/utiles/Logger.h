/*
 * Logger.h
 *
 *  Created on: Aug 31, 2014
 *      Author: matias
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>
#include <iostream>

#define LOGDIR "log"
#define WINDOWLOG "log/Window.log"
#define DIBUJABLELOG "log/Dibujable.log"
#define HANDLERLOG "log/Handler.log"
#define SIMULACIONLOG "log/Simulacion.log"
#define PARSERLOG "log/Parser.log"
#define MAINLOG "log/Main.log"
#define SHAPESLOG "log/shapes.log"
#define THREADSLOG "log/threads.log"

#define WARNING "WAR"
#define ERROR "ERR"
#define OK "OK"

#define ERRORS_ONLY "errors_only"
#define ALL "all"
#define NO_ERRORS "no_errors"

class Logger{
public:
	~Logger(); //Destructor creado para garantizar que se cierre el log.
	static Logger* Instancia();
	bool abrirLog(std::string logFile);
	bool escribirLog(std::string tipo, std::string detalle);
	bool estaAbierto();
	void cerrarLog();
	bool crearLogs();
	bool setMode(std::string mode);
	void log(std::string logFile, std::string tipo, std::string detalle);

private:
	Logger(){};  // Constructor privado para que no lo invoquen
	Logger(Logger const&){};             // Copia privado
	Logger& operator=(Logger const&);  // Asignacion es privado
	static Logger* InstanciaActual;
	std::ofstream logActual;
	std::string mode;

};

#endif /* LOGGER_H_ */
