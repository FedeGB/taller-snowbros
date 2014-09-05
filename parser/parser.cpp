
#include "parser.h"
using namespace std;

string get_node(string data,string param,string file,char* defaultData){
	Json::Value root;
	Json::Reader reader;
	bool parsingOk= reader.parse(file, root);
	if (!parsingOk)
		cout<<"no se pudo leer el archivo "<< reader.getFormattedErrorMessages()<<endl;
	return root[param].get(data,defaultData ).asString();

}

string get_node(char* datas,string param,string file,char* defaultData){
	string data(datas);
	Json::Value root;
	Json::Reader reader;
	bool parsingOk= reader.parse(file, root);
	if (!parsingOk)
		cout<<"no se pudo leer el archivo "<< reader.getFormattedErrorMessages()<<endl;
	return root[param].get(data,defaultData ).asString();

}

string get_node(string data,string param,string file,int field,char* defaultData){
	Json::Value root;
	Json::Reader reader;
	bool parsingOk= reader.parse(file, root);
	if (!parsingOk)
		cout<<"no se pudo leer el archivo "<< reader.getFormattedErrorMessages()<<endl;
	return root[param][field].get(data,defaultData).asString();
}
