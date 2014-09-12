#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include "json.h"

#include "../utiles/Logger.h"

using namespace std;

string get_node(string data, string param, string file, int field,
		char* defaultData);
string get_node(char* datas, string param, string file, char* defaultData);
string get_node(string data, string param, string file, char* defaultData);

int get_node(string data, string param, string file, int field,
		int defaultData);
int get_node(char* datas, string param, string file, int defaultData);
int get_node(string data, string param, string file, int* defaultData);

float get_node(string data, string param, string file, int field,
		float defaultData);
float get_node(char* datas, string param, string file, float defaultData);
float get_node(string data, string param, string file, float defaultData);

bool get_node(string data, string param, string file, int field,
		bool defaultData);
bool get_node(char* datas, string param, string file, bool defaultData);
bool get_node(string data, string param, string file, bool defaultData);

int get_size(char* datas, string param, string file);

#endif /* PARSER_H_ */
