/*
 * WorkItem.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef WORKITEM_H_
#define WORKITEM_H_

#include <string>

class WorkItem {
public:
	WorkItem(std::string message);
	virtual ~WorkItem();
	std::string m_message;
};

#endif /* WORKITEM_H_ */
