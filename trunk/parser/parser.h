/*
 * parser.h
 *
 *  Created on: 02/09/2014
 *      Author: coco
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "json.h"
#include <iostream>

using namespace std;

	 string get_node(string data,string param,string file,int field,char* defaultData);
	 string get_node(char* datas,string param,string file,char* defaultData);
	 string get_node(string data,string param,string file,char* defaultData);

#endif /* PARSER_H_ */