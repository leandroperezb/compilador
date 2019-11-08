#ifndef PASO_H
#define PASO_H

#include <iostream>
#include <stack>

using namespace std;

class Paso{
public:
	virtual void generarCodigo(stack<int>& pila) = 0;
	virtual string toString() = 0;
};

#endif