#ifndef ACCIONESSEMANTICAS_H
#define ACCIONESSEMANTICAS_H

#include <iostream>

using namespace std;

class AnalizadorLexico;

class AccionesSemanticas{
	public:
		static void tokenFinal(AnalizadorLexico* lexico, char& c);
		static void nuevaLinea(AnalizadorLexico* lexico, char& c);

		//Identificadores y constantes
		static void iniciarIdentificador(AnalizadorLexico* lexico, char& c);
		static void agregarCaracter(AnalizadorLexico* lexico, char& c);

		//Identificadores
		static void terminarIdentificador(AnalizadorLexico* lexico, char& c);
		static void tokenFinalIdentificador(AnalizadorLexico* lexico, char& c);

		//Constantes
		static void terminarConstante(AnalizadorLexico* lexico, char& c);
};

#endif