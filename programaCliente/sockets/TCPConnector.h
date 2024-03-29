/*
 * TCPConnector.h
 *
 *  Created on: Oct 3, 2014
 *      Author: matias
 */

#ifndef TCPCONNECTOR_H_
#define TCPCONNECTOR_H_

#include <netinet/in.h>
#include "TCPStream.h"

class TCPConnector {

public:
	TCPStream* connect(const char* server, int port);
	TCPStream* connect(const char* server, int port, int timeout);

private:
	int resolveHostName(const char* host, struct in_addr* addr);
};

#endif /* TCPCONNECTOR_H_ */
