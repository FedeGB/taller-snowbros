/*
 * TCPStream.h
 *
 *  Created on: Oct 3, 2014
 *      Author: matias
 */

#ifndef TCPSTREAM_H_
#define TCPSTREAM_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using namespace std;

class TCPStream {

	int     m_sd;
	string  m_peerIP;
	int     m_peerPort;

public:
	friend class TCPConnector;
	friend class TCPAcceptor;

	ssize_t send(const std::string & sent);
	ssize_t receive(std::string & received, int timeout=0);
	string getPeerIP();
	int    getPeerPort();

	enum {
		connectionClosed = 0,
	    connectionReset = -1,
	    connectionTimedOut = -2,
	    connectionError = -3
		};

	~TCPStream();

private:
    bool waitForReadEvent(int timeout);

    TCPStream(int sd, struct sockaddr_in* address);
    TCPStream();
    TCPStream(const TCPStream& stream);

};

#endif /* TCPSTREAM_H_ */
