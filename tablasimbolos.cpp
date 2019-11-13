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

void TablaSimbolos::constanteNegativizada(string key){
	auto search = tablaSimbolos.find(key);
	if (search != tablaSimbolos.end()) {
		if (--search->second.visibilidad == 0 && --search->second.valor != 0){
			tablaSimbolos.erase(key);
		}
	}
}

void TablaSimbolos::guardar(){
	ofstream ofs;
	ofs.open ("tablaDeSimbolos.csv", std::ofstream::out);
	if(ofs.fail()){
		return;
	}
	string visibilidad[] = {"GLOBAL", "PRIVADO", "PUBLICO"};
	string usos[] = {"", "CONSTANTE", "VARIABLE", "CLASE", "METODO", "CADENA"};
	string tipos[] = {"OTRO", "INT", "ULONG"};
	ofs << "Tabla de símbolos detectados\n(Clave), (Uso), (Tipo de dato), (Clase Padre), (Visibilidad)\n";
	unordered_map<string , TablaSimbolos::registro>::iterator it;
	for (it = tablaSimbolos.begin(); it != tablaSimbolos.end(); ++it){
		int tipoDato = (it->second.tipo < 0 ) ? -(it->second.tipo) : 0;
		ofs << it->first << ", " << usos[-(it->second.tipoSimbolo)] << ", " << tipos[tipoDato] << ", " << it->second.clasePadre << ", " << visibilidad[-(it->second.visibilidad)] << '\n';
	}

	ofs.close();
}

void TablaSimbolos::guardarPolacas(){
	unordered_map<string , TablaSimbolos::registro>::iterator it;
	for (it = tablaSimbolos.begin(); it != tablaSimbolos.end(); ++it){
		if (it->second.tipoSimbolo == TablaSimbolos::METODO){
			it->second.polaca->guardar(it->first);
		}
	}
}