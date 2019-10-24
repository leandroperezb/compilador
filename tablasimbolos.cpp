#include "tablasimbolos.h"

TablaSimbolos::TablaSimbolos(){}

void TablaSimbolos::agregar(string key, registro r){
	auto search = tablaSimbolos.find(key);
	if (search == tablaSimbolos.end()) {
		//Si no existe 'key' en la tabla de símbolos:
		tablaSimbolos.insert({key, r});
	}
}

TablaSimbolos::registro& TablaSimbolos::get(string key){
	auto search = tablaSimbolos.find(key);
	if (search != tablaSimbolos.end()) {
		return search->second;
	}
}

bool TablaSimbolos::existe(string key){
	auto search = tablaSimbolos.find(key);
	return (search != tablaSimbolos.end());
}

void TablaSimbolos::guardar(){
	ofstream ofs;
	ofs.open ("tablaDeSimbolos.txt", std::ofstream::out);
	if(ofs.fail()){
		return;
	}

	ofs << "Tabla de símbolos detectados (-1 = CONSTANTE) (-2 = VARIABLES) (-3 = CLASE) (-4 = METODO):\n(Clave)\t\t(Tipo de símbolo)\t\t(Tipo de variable)\t\t(Valor)\n";
	unordered_map<string , TablaSimbolos::registro>::iterator it;
	for (it = tablaSimbolos.begin(); it != tablaSimbolos.end(); ++it){
		ofs << it->first << "\t\t" << it->second.tipoSimbolo << "\t\t\t" << it->second.tipo << "\t\t\t" << it->second.valor << '\n';
	}

	ofs.close();
}