/*
 * TCPAcceptor.h
 *
 *  Created on: Oct 3, 2014
 *      Author: matias
 */

#ifndef TCPACCEPTOR_H_
#define TCPACCEPTOR_H_

#include <string>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "TCPStream.h"

using namespace std;

class TCPAcceptor
{
    int    m_lsd;
    int    m_port;
    string m_address;
    bool   m_listening;

  public:
    TCPAcceptor(int port, const char* address="");
    ~TCPAcceptor();

    int        start();
    TCPStream* accept();

};

#endif /* TCPACCEPTOR_H_ */
