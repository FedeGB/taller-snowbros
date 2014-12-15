/*
 * serverMain.cpp
 *
 *  Created on: Sep 30, 2014
 *      Author: matias
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "threads/Thread.h"
#include "threads/ThreadSafeList.h"
#include "threads/ConditionVariable.h"
#include "server/TCPAcceptor.h"
#include "server/ConnectionHandler.h"
#include "server/WorldHandler.h"


#include "Servidor.h"

int main(int argc, char** argv){

	srand(time(NULL));

	Servidor servidor;
	servidor.ejecutar(argc, argv);

	return 0;

}
