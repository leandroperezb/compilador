#ifndef LOG_H
#define LOG_H

#include <iostream>
#include "lexico.h"

using namespace std;

class Log{
private:
	inline static const string tokens[] = {"ID", "CTE", "MAYORIGUAL", "MENORIGUAL", "IGUAL", "DISTINTO", "ASIGNACION", "STRING", "IF", "ELSE", "END_IF", "PRINT", "INT", "BEGIN", "END", "FOR", "CLASS", "EXTENDS", "PUBLIC", "PRIVATE", "VOID", "ULONG", "ERROR"};
public:
	static AnalizadorLexico* lexico;
	static bool abortarCompilacion;
	static void estructuraDetectada(string estructura){
		//cout << "Estructura sintáctica detectada en línea " << lexico->contadorLineas << ": " << estructura << endl;
	}

	static void errorSintactico(string mensaje){
		cout << "Línea " << lexico->contadorLineas << ": " << mensaje << endl;
		abortarCompilacion = true;
	}
	static void warning(string mensaje){
		cout << mensaje;
	}

	static void tokenDetectado(int token){
		/*string nombreToken;
		if (token > 256){
			nombreToken = tokens[token - 257];
		}else if (token < 0){
			nombreToken = "FIN";
		}else{
			char a = (char) token;
			nombreToken = string(1, a);
		}
		cout << "Token: " << nombreToken << endl;*/
	}
	
	
	static void redeclaracionVariable(string mensaje){
		cout <<"Linea "<<lexico->contadorLineas<< mensaje << endl;
		abortarCompilacion = true;
	}
	static void noExisteClase(string clase){
		cout << "Linea " << lexico->contadorLineas << ": No existe la clase \"" << clase << "\", a la que se hace referencia" << endl;
		abortarCompilacion = true;
	}
	static void identificadorNoCorresponde(string identificador, string tipo){
		cout << "Linea "<<lexico->contadorLineas<<": El identificador \"" << identificador << "\" no corresponde a " << tipo << endl;
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
		cout << "Linea "<<lexico->contadorLineas<<": el miembro \"" << atributo << "\" de la clase " << clase << " es privado"<<endl;
		abortarCompilacion = true;
	}
	static void metodoNoHeredado(string metodo, string claseObjeto){
		cout << "Linea "<<lexico->contadorLineas<<": el metodo \""<<metodo<<"\" no corresponde a la linea de herencia de "<<claseObjeto<<endl;
	}
	static void operacionConObjeto(string objeto){
		cout << "Linea "<<lexico->contadorLineas << ": No se permite la operacion directa con el objeto " <<objeto<<endl;
		abortarCompilacion = true;
	}
	static void incompatibilidadAsignacion(){
		cout << "Se detectó una incompatibilidad de tipos en una asignación (lado izquierdo INT, lado derecho ULONG)"<<endl;
		abortarCompilacion = true;
	}
	static void seEsperabaIntEnFor(string variable){
		cout << "Linea "<<lexico->contadorLineas <<": el argumento \"" << variable << "\" del for debe ser de tipo int" <<endl;
		abortarCompilacion = true;
	}

};

#endif