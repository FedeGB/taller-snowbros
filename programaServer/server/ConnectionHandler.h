/*
 * ConnectionHandler.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

#include "TCPStream.h"
#include "../threads/ColaTrabajo.h"
#include "WorkItem.h"
#include "../modelo/WorldItem.h"
#include "../threads/Thread.h"
#include "../threads/ThreadSafeList.h"
#include "../threads/ConditionVariable.h"
#include "../ControladorUsuarios.h"

#define OK 0
#define SERVERFULL 1
#define USERONLINE 2

class ConnectionHandler : public Thread{
private:
	ControladorUsuarios & controlador;
    TCPStream * m_stream;
    std::string username;

    // Intenta conectar un usuario al servidor, ya sea alguien que
    // ya estaba en la partida y se habia desconectado, o alguien nuevo.
    // username: el usuario a intentar conectarse.
    // return: true si la conexion fue exitosa, false en caso contrario.
    int logIn(std::string username);

public:
    ConnectionHandler(ControladorUsuarios & c, TCPStream * stream);
    void* run();
};

#endif /* CONNECTIONHANDLER_H_ */
