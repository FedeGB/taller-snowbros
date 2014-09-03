
#include "parser.h"
using namespace std;

string get_node(string data,string param,string file){
	Json::Value root;
	Json::Reader reader;
	bool parsingSucefull= reader.parse(file, root);
	if (!parsingSucefull)
		cout<<"no se pudo leer el archivo "<< reader.getFormattedErrorMessages()<<endl;
	return root[param].get(data,"UTF-8" ).asString();

}

string get_node(char* datas,string param,string file){
	string data(datas);
	Json::Value root;
	Json::Reader reader;
	bool parsingSucefull= reader.parse(file, root);
	if (!parsingSucefull)
		cout<<"no se pudo leer el archivo "<< reader.getFormattedErrorMessages()<<endl;
	return root[param].get(data,"UTF-8" ).asString();

}

string get_node(string data,string param,string file,int field){
	Json::Value root;
		Json::Reader reader;
		bool parsingSucefull= reader.parse(file, root);
				if (!parsingSucefull)
					cout<<"no se pudo leer el archivo "<< reader.getFormattedErrorMessages()<<endl;
		return root[param][field].get(data,"0").asString();
}
