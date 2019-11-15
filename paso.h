#ifndef PASO_H
#define PASO_H

#include <iostream>
#include <stack>
#include "structoperacion.h"
#include "generacionCodigo.h"
#include "tablasimbolos.h"

class TablaSimbolos;

using namespace std;

class Paso{

public:
	static TablaSimbolos *tds;
	static string variableEnCodigo(operacion op);
	static string conversiones(operacion &op1, operacion &op2, bool registroEspecial = false);
	virtual void generarCodigo() = 0;
	virtual string toString(vector<Paso*>* tira = nullptr) = 0;
};

#endif