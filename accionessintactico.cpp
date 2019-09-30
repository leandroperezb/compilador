#include "accionessintactico.h"

void AccionesSintactico::negativizarConstante(TablaSimbolos* tabla, string key){
	TablaSimbolos::registro r = tabla->get(key);
	r.valor = r.valor * (-1);
	if (r.valor < -32768){
		cout << "Constante " << r.valor << " fuera de rango" << endl;
		r.valor = -32768;
		r.esUlong = false;
	}
	tabla->agregar(key, r);
}