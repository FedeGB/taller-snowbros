/*
 * WorkItem.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#include "Message.h"

Message::Message(std::string message, std::string from){
	m_message = message;
	m_from = from;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

