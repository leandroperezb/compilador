#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>

using namespace std;

class TablaSimbolos{
	public:
		static const int TIPO_INT = -1;
		static const int TIPO_ULONG = -2;

		static const int CONSTANTE = -1;
		static const int VARIABLE = -2;
		static const int CLASE = -3;
		static const int METODO = -4;
		TablaSimbolos();
		struct registro{
			long long valor;

			int tipoSimbolo;
			int tipo;
		};

		void agregar(string key, registro r);
		registro& get(string key);

		void guardar();

	private:
		unordered_map<string, registro> tablaSimbolos;
};

#endif