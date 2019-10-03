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
		TablaSimbolos();
		struct registro{
			long long valor;

			string palabra;
			int tipo;
		};

		void agregar(string key, registro r);
		registro& get(string key);

		void guardar();

	private:
		unordered_map<string, registro> tablaSimbolos;
};

#endif