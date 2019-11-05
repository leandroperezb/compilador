#ifndef POLACA_H
#define POLACA_H

#include <iostream>
#include <vector>
#include <stack>
#include "paso.h"

using namespace std;

class Polaca{
private:
	stack<int> pila;
	vector<Paso*> tira;

public:
	static Polaca polacaMadre;
	static Polaca* polacaEnEdicion;

	static void modificarPunteroPolaca(Polaca &polaca){
		polacaEnEdicion = &polaca;
	}
	void terminoIfRamaTrue(){}
	void terminoCondicion(){}
	void terminoIf(){}

	// Soporte Expresiones
	int cargarFactor(string factor);
	void cargarOperador(int op);

};

#endif