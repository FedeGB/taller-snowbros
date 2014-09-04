/*
 * Logger.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: matias
 */

#include "Logger.h"
#include <stddef.h> //Define NULL
#include <ctime>
using namespace std;

//Puntero global estatico para asegurar que solo se use una instancia del Logger
Logger* Logger::InstanciaActual = NULL;

/** Se llama esta funcion para crear una instacia del logger. El constructor es privado
 * y solo se llama desde adentro de esta funcion. Si ya existe uno, lo devuelve.
*/

Logger::~Logger(){
	if(this->logActual.is_open()) this->logActual.close();
}

Logger* Logger::Instancia()
{
   if (!InstanciaActual)   // Only allow one instance of class to be generated.
	   InstanciaActual = new Logger;

   return InstanciaActual;
}

bool Logger::abrirLog(std::string _logFile)
{
	if( this->logActual.is_open() ) this->logActual.close();
	this->logActual.open ( _logFile.c_str(), ios::out | ios::app);
	if (this->logActual.is_open()) return true;
	else return false;
}

void Logger::cerrarLog()
{
	if(! this->logActual.is_open() ) return;
	this->logActual.close();
	return;
}

bool Logger::escribirLog(string tipo, string detalle){
	if(! this->logActual.is_open())return false;
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	string str(buffer);
	this->logActual << str + " -> " + tipo + " -> " + detalle + "\n";

	return true;
}

bool Logger::estaAbierto()
{
	return this->logActual.is_open();
}
