#ifndef PASO_H
#define PASO_H

#include <iostream>
#include <stack>
#include "paso.h"

using namespace std;

class Paso{
public:
	void generarCodigo(stack<Paso>& pila);
};

#endif