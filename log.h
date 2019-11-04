#ifndef LOG_H
#define LOG_H

#include <iostream>

using namespace std;

class Log{
public:
	static void estructuraDetectada(int linea, string estructura){
		cout << "Estructura sintáctica detectada en línea " << linea << ": " << estructura << endl;
	}

	static void errorSintactico(int linea, string mensaje){
		cout << "Línea " << linea << ": " << mensaje << endl;
	}

	static void tokenDetectado(int token){
		cout << "Token: " << token << endl;
	}
};

#endif