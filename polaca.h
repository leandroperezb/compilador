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
	vector<Paso> tira;

public:
	void terminoIfRamaTrue(){}
	void terminoCondicion(){}
	void terminoIf(){}

	// Soporte Expresiones
	void cargarFactor(string factor);
	void cargarOperador(int op);

};

#endif