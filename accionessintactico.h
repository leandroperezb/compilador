#ifndef ACCIONESSINTACTICO_H
#define ACCIONESSINTACTICO_H

#include "tablasimbolos.h"
#include "lexico.h"
#include <iostream>

using namespace std;

class AccionesSintactico{
	public:
		static void negativizarConstante(TablaSimbolos* tabla, vector<string>& punteros, int indice);
		//Informar errores de sintaxis
		static void informarError(string sentencia, string esperado, string obtenido, AnalizadorLexico* lex);
		static void asignarTipos(TablaSimbolos* tabla, int tipo, vector<string> variables);

		static void cargarClase(TablaSimbolos* tabla, string clase, string clasePadre);
		static void cargarClase(TablaSimbolos* tabla, string clase);
};

#endif