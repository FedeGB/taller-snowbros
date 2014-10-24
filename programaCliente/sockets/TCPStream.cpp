/*
 * TCPStream.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: matias
 */

#include "TCPStream.h"

#include <arpa/inet.h>
#include <stdlib.h>
#include "TCPStream.h"
#include <cstdio>
#include <iostream>


TCPStream::TCPStream(int sd, struct sockaddr_in* address) : m_sd(sd) {
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip)-1);
    m_peerIP = ip;
    m_peerPort = ntohs(address->sin_port);
}

TCPStream::~TCPStream()
{
    close(m_sd);
}

ssize_t TCPStream::send(const std::string & sent){

	char buff[4];
	sprintf(buff, "%d", (int)sent.length());
	write(m_sd, buff, 4);
	uint totalSent = 0;
	const char * buffer = new char(sent.length());
	buffer = sent.c_str();
	while (totalSent < sent.length()){
		int itSent = write(m_sd, buffer, sent.length() - totalSent);
		if (itSent <= 0) return connectionError;
		buffer += itSent;
		totalSent += itSent;
	}
    return totalSent;
}

ssize_t TCPStream::receive(std::string & received, int timeout){

	received.clear();
	if (timeout <= 0 || waitForReadEvent(timeout) == true) {
    	char buff[5];
    	int r = read(m_sd, buff, 4);
    	if (r <= 0) return connectionError;
    	buff[r] = '\0';
    	int size = strtol(buff, NULL, 10);
    	int totalRead = 0;
    	char buffer[size+1];
    	while (totalRead < size){
    		int itRead = read(m_sd, buffer, size - totalRead);
    		if (itRead <= 0) return connectionError;
    		buffer[itRead] = '\0';
    		totalRead += itRead;
    		received += buffer;
    	}
    	return totalRead;
    }

    return connectionTimedOut;

}

string TCPStream::getPeerIP()
{
    return m_peerIP;
}

int TCPStream::getPeerPort()
{
    return m_peerPort;
}

bool TCPStream::waitForReadEvent(int timeout)
{
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(m_sd, &sdset);
    if (select(m_sd+1, &sdset, NULL, NULL, &tv) > 0)
    {
        return true;
    }
    return false;
}

