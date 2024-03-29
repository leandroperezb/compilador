#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include "polaca.h"

using namespace std;

class Polaca;

class TablaSimbolos{
	public:
		static const int TIPO_INT = -1;
		static const int TIPO_ULONG = -2;

		static const int PRIVAT = -1;
		static const int PUBLI = -2;

		static const int CONSTANTE = -1;
		static const int VARIABLE = -2;
		static const int CLASE = -3;
		static const int METODO = -4;
		static const int CADENA = -5;
		static const int INDEFINIDO = -6;
		TablaSimbolos();
		struct registro{
			long long valor;

			int tipoSimbolo;
			int tipo;

			string clasePadre;
			Polaca *polaca;
			int visibilidad = 0;
		};

		void agregar(string key, registro r);
		void constanteNegativizada(string key);
		registro& get(string key);
		bool existe(string key);

		void guardar();

		void guardarPolacas();
		unordered_map<string, TablaSimbolos::registro> getCopyTabla();

	private:
		unordered_map<string, registro> tablaSimbolos;
};

#endif