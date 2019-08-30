#ifndef ACCIONESSEMANTICAS_H
#define ACCIONESSEMANTICAS_H

#include <iostream>

using namespace std;

class AnalizadorLexico;

class AccionesSemanticas{
	public:
		//Identificadores y constantes
		static void iniciarIdentificador(AnalizadorLexico* lexico, char& c);
		static void agregarCaracter(AnalizadorLexico* lexico, char& c);

		//Identificadores
		static void terminarIdentificador(AnalizadorLexico* lexico, char& c);

		//Constantes
		static void terminarConstante(AnalizadorLexico* lexico, char& c);
};

#endif