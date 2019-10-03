#ifndef ACCIONESSINTACTICO_H
#define ACCIONESSINTACTICO_H

#include "tablasimbolos.h"
#include <iostream>

using namespace std;

class AccionesSintactico{
	public:
		static void negativizarConstante(TablaSimbolos* tabla, string key);
		//Informar errores en la sentencia print
		static void informarPrint(string msj);
		//Informa error en la condicion del if
		static void informarErrorIF(string msj);
		static void asignarTipos(TablaSimbolos* tabla, int tipo, vector<string> variables);
};

#endif