#ifndef GENERACION_CODIGO_H
#define GENERACION_CODIGO_H

#include <stack>
#include <string>
#include "polaca.h"

using namespace std;
class GeneracionCodigo
{
public:
	struct operacion{
		bool esRegistro;
		string operador;
	};
private:
	inline static const string registros[4] = {"AX", "BX", "CX", "DX"};
	inline static bool ocupado[4] = {false, false, false, false};
	static stack<GeneracionCodigo::operacion> pilaGeneracion;
	
public:
	static string buscarRegistroEspecial(bool extendido){
		if(!ocupado[0]){
			if (extendido)
				return "AX";
			return "EAX";
		}
		if (extendido)
			return "DX";
		return "EDX";
	}
	static string buscarRegistro(bool extendido){
		for(int i = 0; i < 4; i++){
			if(!ocupado[i]){
				if(extendido)
					return "E"+registros[i];
				else
					return registros[i];
				ocupado[i] = true;
			}
		}
	}
	static void desocuparRegistro(string str){
		int i = (str.length > 2) ? 1 : 0;
		ocupado[str[i] - 65] = false;
	}
	static void generarCodigo(Polaca *polaca){
		for(int i = 0; i < polaca->size(); i++){
			Paso* p = polaca->get(i);
			p->generarCodigo();
		}
	}
	static void apilar(operacion op){
		pilaGeneracion.push(op);
	}
	static operacion desapilar(){
		operacion top= pilaGeneracion.top();
		pilaGeneracion.pop();
		return top;
	}
};

#endif