#ifndef GENERACION_CODIGO_H
#define GENERACION_CODIGO_H

#include <stack>
#include <string>
#include "polaca.h"
#include "structoperacion.h"

class Polaca;

using namespace std;
class GeneracionCodigo
{
private:
	inline static const string registros[4] = {"AX", "BX", "CX", "DX"};
	inline static bool ocupado[4] = {false, false, false, false};
	inline static stack<operacion> pilaGeneracion;
	
public:
	static bool ocupadoAX(){return ocupado[0];}
	static void ocuparAX(){ocupado[0] = true;}
	static string buscarRegistro(bool extendido){
		for(int i = 1; i < 3; i++){
			if(!ocupado[i]){
				ocupado[i] = true;
				if(extendido)
					return "E"+registros[i];
				else
					return registros[i];
			}
		}
	}
	static void desocuparRegistro(string str){
		int i = (str.length() > 2) ? 1 : 0;
		ocupado[str[i] - 65] = false;
	}
	static string generarCodigo(Polaca *polaca);
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