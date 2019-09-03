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
		static void tokenFinalConstante(AnalizadorLexico* lexico, char& c);
		 
		//Mayor(o Igual)
		static void terminarMayor(AnalizadorLexico* lexico, char& c);
		 
		//Menor(o Igual)
		static void terminarMenor(AnalizadorLexico* lexico, char& c);

		//Comentario
		static void terminarComentario(AnalizadorLexico* lexico, char& c);

		//Igualdad
		static void entregarIgual(AnalizadorLexico* lexico, char& c);

		//Asignacion
		static void entregarAsignacion(AnalizadorLexico* lexico, char& c);

		//Cadena
		static void entregarCadena(AnalizadorLexico* lexico, char& c);

		//Operadores('+', '-', '/', '*', '(', ')', ',', ';')
		static void entregarOperador(AnalizadorLexico* lexico, char& c);
		
};

#endif