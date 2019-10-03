#include "accionessintactico.h"

void AccionesSintactico::negativizarConstante(TablaSimbolos* tabla, string key){
	TablaSimbolos::registro* r = &tabla->get(key);
	if ((*r).palabra != ""){
		(*r).valor = (*r).valor * (-1);
		(*r).esUlong = false;
		if ((*r).valor < -32768){
			cout << "Constante " << (*r).valor << " fuera de rango" << endl;
			(*r).valor = -32768;
		}
	}
}