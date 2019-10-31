#ifndef ACCIONESSINTACTICO_H
#define ACCIONESSINTACTICO_H

#include "tablasimbolos.h"
#include "lexico.h"
#include <iostream>

using namespace std;

class AccionesSintactico{
	public:
		static vector<string> *punteros;
		static void inicializar(vector<string>* p);
		static string claseActual;
		static void negativizarConstante(TablaSimbolos* tabla, vector<string>& punteros, int indice);
		//Informar errores de sintaxis
		static void informarError(string sentencia, string esperado, string obtenido, AnalizadorLexico* lex);
		static void declararVariable(TablaSimbolos* tabla, int tipo, vector<string>& variables, int modificador = 0);

		static void cargarClase(TablaSimbolos* tabla, string clase, string clasePadre);
		static void cargarClase(TablaSimbolos* tabla, string clase);
};

#endif