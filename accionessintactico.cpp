#include "accionessintactico.h"

void AccionesSintactico::negativizarConstante(TablaSimbolos* tabla, string key){
	TablaSimbolos::registro* r = &tabla->get(key);
	if ((*r).palabra != ""){
		(*r).valor = (*r).valor * (-1);
		(*r).tipo = TablaSimbolos::TIPO_INT;
		if ((*r).valor < -32768){
			cout << "Constante " << (*r).valor << " fuera de rango" << endl;
			(*r).valor = -32768;
		}
	}
}

void AccionesSintactico::asignarTipos(TablaSimbolos* tabla, int tipo, vector<string> variables){
	for (int i = 0; i < variables.size(); i++){
		TablaSimbolos::registro* r = &tabla->get(variables[i]);
		(*r).tipo = tipo;
	}
}