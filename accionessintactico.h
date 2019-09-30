#ifndef ACCIONESSINTACTICO_H
#define ACCIONESSINTACTICO_H

#include "tablasimbolos.h"
#include <iostream>

using namespace std;

class AccionesSintactico{
	public:
		static void negativizarConstante(TablaSimbolos* tabla, string key);
};

#endif