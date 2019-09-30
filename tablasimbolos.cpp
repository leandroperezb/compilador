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

void TablaSimbolos::guardar(){
	ofstream ofs;
	ofs.open ("tablaDeSimbolos.txt", std::ofstream::out);
	if(ofs.fail()){
		return;
	}

	ofs << "Tabla de símbolos de identificadores:\n(Clave)\t\t(Palabra)\t\t(Es_ulong)\t\t(Valor)\n";
	unordered_map<string , TablaSimbolos::registro>::iterator it;
	for (it = tablaSimbolos.begin(); it != tablaSimbolos.end(); ++it){
		ofs << it->first << "\t\t" << it->second.palabra << "\t\t\t" << it->second.esUlong << "\t\t\t" << it->second.valor << '\n';
	}

	ofs.close();
}