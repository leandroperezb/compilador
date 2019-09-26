#include "tablasimbolos.h"

TablaSimbolos::TablaSimbolos(){}

void TablaSimbolos::agregar(string key, registro r){
	mtx.lock();
	tablaSimbolos.insert_or_assign(key, r);
	mtx.unlock();
}

TablaSimbolos::registro TablaSimbolos::get(string key){
	TablaSimbolos::registro resultado;
	mtx.lock();
	auto search = tablaSimbolos.find(key);
	if (search != tablaSimbolos.end()) {
		resultado = search->second;
	}
	mtx.unlock();
	return resultado;
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