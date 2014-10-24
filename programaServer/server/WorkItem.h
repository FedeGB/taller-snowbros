/*
 * WorkItem.h
 *
 *  Created on: Oct 6, 2014
 *      Author: matias
 */

#ifndef WORKITEM_H_
#define WORKITEM_H_

#include <string>
#include "../utiles/tipos.h"

enum TIPOS{
	NEWPJ,
	KEYEVENT,
	NONE,
};

class WorkItem {
public:
	WorkItem();
	virtual ~WorkItem();
	//std::string m_message;
	int type;
	int PJnum;
	int key;
};

#endif /* WORKITEM_H_ */
