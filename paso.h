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
	inline static const string L_ERROR_DIV_CERO = "lErrorDivCero";
	inline static const string L_ERROR_CONVERSION = "lErrorConversion";

	static string labelsError(){
		string labels = "";
		//label que contiene el codigo de error de division por cero
		labels = "lerrorDivCero:\ninvoke MessageBox, NULL, addr err2, addr err2, MB_OK\ninvoke ExitProcess, 1\n";

		//label que contiene el codigo de error de conversion
		labels += "lErrorConversion:\ninvoke MessageBox, NULL, addr err1, addr err1, MB_OK\ninvoke ExitProcess, 1\n";

		//label de comienzo de programa
		labels += "start:\n";
		return labels;
	}
	static TablaSimbolos *tds;
	static string variableEnCodigo(operacion op);
	static string conversiones(operacion &op1, operacion &op2, bool registroEspecial = false);
	static bool esUlong(operacion &op);
	virtual string generarCodigo(Polaca *polaca) = 0;
	virtual string toString(vector<Paso*>* tira = nullptr) = 0;
};

#endif