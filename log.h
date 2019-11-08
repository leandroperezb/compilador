#ifndef LOG_H
#define LOG_H

#include <iostream>
#include "lexico.h"

using namespace std;

class Log{
public:
	static AnalizadorLexico* lexico;
	static bool abortarCompilacion;
	static void estructuraDetectada(string estructura){
		cout << "Estructura sintáctica detectada en línea " << lexico->contadorLineas << ": " << estructura << endl;
	}

	static void errorSintactico(string mensaje){
		cout << "Línea " << lexico->contadorLineas << ": " << mensaje << endl;
		abortarCompilacion = true;
	}
	static void warning(string mensaje){
		cout << mensaje;
	}

	static void tokenDetectado(int token){
		cout << "Token: " << token << endl;
	}
	
	
	static void redeclaracionVariable(string variable){
		cout <<"Linea "<<lexico->contadorLineas<< ": Variable \"" << variable << "\" redeclarada" << endl;
		abortarCompilacion = true;
	}
	static void noExisteClase(string clase){
		cout << "Linea " << lexico->contadorLineas << ": No existe la clase \"" << clase << "\", a la que se hace referencia" << endl;
		abortarCompilacion = true;
	}
	static void identificadorNoCorresponde(string identificador, string tipo){
		cout << "Linea "<<lexico->contadorLineas<<": El identificador \"" << identificador << "\" no corresponde a un/una " << tipo << endl;
		abortarCompilacion = true;
	}
	static void redeclaracionClase(string clase){
		cout << "Linea "<<lexico->contadorLineas<<": El nombre de la clase \""<<clase<<"\" ya está en uso"<<endl;
		abortarCompilacion = true;
	}
	static void identificadorNoDefinido(string identificador){
		cout << "Linea "<<lexico->contadorLineas<<": El identificador \"" << identificador <<"\" no está definido"<<endl;
		abortarCompilacion = true;
	}
	static void informarError(string sentencia, string esperado, string obtenido){
		string msj = "Error en la linea: "+to_string(lexico->contadorLineas) + ". Sentencia "+sentencia+", se esperaba "+
		esperado+", pero se obtuvo "+obtenido+"\n";
		
		cout<< msj;
		abortarCompilacion = true;
	}
	static void variableDeClase(string variable, string clase){
		cout << "Linea "<<lexico->contadorLineas<<": uso de la variable \""<<variable << "\" fuera de un objeto de la clase "<<clase<<endl;
		abortarCompilacion = true;
	}
	static void accesoAtributoPrivado(string atributo, string claseActual, string claseAtributo){
		cout << "Linea "<<lexico->contadorLineas<<": atributo privado \"" << atributo << "\" de la clase " << claseAtributo << " accedido desde un metodo de la clase " << claseActual << endl;
		abortarCompilacion = true;
	}
	static void accesoAtributoFueraHerencia(string atributo, string claseActual, string claseAtributo){
		cout << "Linea "<<lexico->contadorLineas<<": atributo \"" << atributo << "\" de la clase " << claseAtributo << " accedido desde un metodo de la clase " << claseActual << endl;
		abortarCompilacion = true;
	}
	static void accesoAtributoPrivado(string atributo, string clase){
		cout << "Linea "<<lexico->contadorLineas<<": el atributo \"" << atributo << "\" de la clase " << clase << " es privado"<<endl;
		abortarCompilacion = true;
	}
	static void operacionConObjeto(string objeto){
		cout << "Linea "<<lexico->contadorLineas << ": No se permite la operacion directa con el objeto " <<objeto<<endl;
		abortarCompilacion = true;
	}

};

#endif