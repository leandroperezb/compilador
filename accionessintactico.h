#ifndef ACCIONESSINTACTICO_H
#define ACCIONESSINTACTICO_H

#include "tablasimbolos.h"
#include "lexico.h"
#include "polaca.h"
#include <iostream>

using namespace std;

class AccionesSintactico{
	private:
		static bool hereda(TablaSimbolos* tabla, string claseHijo, string clasePadre);
		static void inicializarVariablesDeObjeto(TablaSimbolos* tabla, string objeto, string clase);
	public:
		static unordered_map<string, vector<string>> variablesDeClase;
		static vector<string> *punteros;
		static void inicializar(vector<string>* p);
		static string claseActual;
		static void negativizarConstante(TablaSimbolos* tabla, vector<string>& punteros, int indice);
		//Informar errores de sintaxis
		static void declararVariable(TablaSimbolos* tabla, int tipo, vector<string>& variables, int modificador = 0);

		static void cargarClase(TablaSimbolos* tabla, string clase, string clasePadre);
		static void cargarClase(TablaSimbolos* tabla, string clase);

		static void nuevoFactor(TablaSimbolos* tabla, string factor);
		static void nuevoFactorDeClase(TablaSimbolos* tabla, string obj, string variable);

		static void nuevoMetodo(TablaSimbolos* tabla, string nombre, int visibilidad);
		static void finalizarMetodo();
		static void finalizarClase();

		static void llamadoAMetodo(TablaSimbolos* tabla, string objeto, string metodo);
		static void llamadoAMetodo(TablaSimbolos* tabla, string metodo);

		static void verificarIntFor(TablaSimbolos* tabla, string simbolo);
};

#endif