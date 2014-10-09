/*
 * WorkItem.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef WORKITEM_H_
#define WORKITEM_H_

#include <string>

class Message {
public:
	Message(std::string message, std::string from);
	virtual ~Message();
	std::string m_message;
	std::string m_from;
};

#endif /* WORKITEM_H_ */
