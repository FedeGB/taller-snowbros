/*
 * ConnectionHandler.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

#include "TCPStream.h"
#include "ColaTrabajo.h"
#include "Message.h"
#include "RecvThread.h"
#include "WriteThread.h"


class ConnectionHandler{
	RecvThread* m_receiver;
	WriteThread* m_writer;
    TCPStream* m_stream;
    ColaTrabajo<Message*> m_toSend;

  public:
    ConnectionHandler(ColaTrabajo<Message*>& queue, TCPStream* item);
    void start();
    std::string getPeerIP();
    void queueMessage(Message* newItem);
};

#endif /* CONNECTIONHANDLER_H_ */
