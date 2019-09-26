#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>

using namespace std;

class TablaSimbolos{
	public:
		TablaSimbolos();
		struct registro{
			bool esUlong;
			long long valor;

			string palabra;
		};

		void agregarSiNoExiste(string key, registro r);
		registro& get(string key);

		void guardar();

	private:
		unordered_map<string, registro> tablaSimbolos;
};

#endif