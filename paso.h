#ifndef PASO_H
#define PASO_H

#include <iostream>
#include <stack>
#include "generacionCodigo.h" 

using namespace std;

class Paso{

public:
	static TablaSimbolos *tds;
	static string variableEnCodigo(GeneracionCodigo::operacion op){
		string salida = op.operador;
		if (!op.esRegistro && tds->get(op.operador).tipoSimbolo == TablaSimbolos::VARIABLE){
			salida = "_" + salida;
		}
		return salida;
	} 
	static string conversiones(GeneracionCodigo::operacion &op1, GeneracionCodigo::operacion &op2, bool registroEspecial = false){
		bool es1Ulong = false;
		if (op1.esRegistro && op1.operador[0] == 'E' 
		|| !op1.esRegistro && tds->get(op1.operador).tipo == TablaSimbolos::TIPO_ULONG)
			es1Ulong=true;
		bool es2Ulong = false;
		if (op2.esRegistro && op2.operador[0] == 'E' 
		|| !op2.esRegistro && tds->get(op1.operador).tipo == TablaSimbolos::TIPO_ULONG)
			es2Ulong=true;

		GeneracionCodigo::operacion *aConvertir = nullptr;

		if (es1Ulong && !es2Ulong){
			aConvertir = &op2;
		}else if (es2Ulong && !es1Ulong){
			aConvertir = &op1;
		}

		string codigo = "";

		if (aConvertir != nullptr){
			if (aConvertir->esRegistro){
				aConvertir->operador = "E"+ aConvertir->operador;
				codigo += "AND "+aConvertir->operador+" 65535\n";
			}else{
				string nuevoRegistro = (registroEspecial) ? GeneracionCodigo::buscarRegistroEspecial(true) : GeneracionCodigo::buscarRegistro(true);
				codigo += "MOV "+ nuevoRegistro + " "+ variableEnCodigo(*aConvertir) + "\n";
				//codigo += "AND "+nuevoRegistro+" 65535\n";
				aConvertir->operador = nuevoRegistro;
				aConvertir->esRegistro = true;
			}
		}
		return codigo;
	}
	virtual void generarCodigo() = 0;
	virtual string toString(vector<Paso*>* tira = nullptr) = 0;
};

#endif