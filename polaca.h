#ifndef POLACA_H
#define POLACA_H

#include <iostream>
#include <vector>
#include <stack>
#include "paso.h"
#include <fstream>

using namespace std;

class Paso;

class Polaca{
private:
	stack<int> pila;
	vector<Paso*> tira;

public:
	static Polaca polacaMadre;
	static Polaca* polacaEnEdicion;

	Polaca(){
		
	}

	Paso* getLastPaso();

	static void modificarPunteroPolaca(Polaca &polaca){
		polacaEnEdicion = &polaca;
	}
	void terminoRamaIf();
	void terminoCondicion(int comparador);
	void terminoIf();


	void invocacionMetodo(string objeto, string metodo, Polaca* polaca);

	// Soporte Expresiones
	int cargarFactor(string factor);
	void cargarOperador(int op);
	//Soporte PRINT
	void cargarString(string str);
	void cargarPrint();

	//For:
	void removeLastPaso();
	void empiezaFor(string variable);
	void comparacionFor(bool descendente);
	void terminoFor(string variable, string step);

	void guardar(string nombreArchivo);
	int size();
	Paso* get(int indice);
};

#endif