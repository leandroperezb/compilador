#ifndef POLACA_H
#define POLACA_H

#include <iostream>
#include <vector>
#include <stack>
#include "paso.h"

using namespace std;

class Polaca{
private:
	stack<Paso> pila;
	vector<Paso> tira;

public:
	void terminoIfRamaTrue(){}
	void terminoCondicion(){}
	void terminoIf(){}

	void cargarFactor(string factor){}

};

#endif