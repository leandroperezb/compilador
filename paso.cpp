#include "paso.h"
TablaSimbolos* Paso::tds = nullptr;
bool Paso::esUlong(operacion &op){
	if (op.esRegistro)
		return (op.operador[0] == 'E');
	return (tds->get(op.operador).tipo == TablaSimbolos::TIPO_ULONG);
}

string Paso::variableEnCodigo(operacion op){
	string salida = op.operador;
	if (!op.esRegistro && tds->get(op.operador).tipoSimbolo == TablaSimbolos::VARIABLE){
		salida = "_" + salida;
	}
	return salida;
} 
string Paso::conversiones(operacion &op1, operacion &op2, bool registroEspecial){
	bool es1Ulong = false;
	if (op1.esRegistro && op1.operador[0] == 'E' 
		|| !op1.esRegistro && tds->get(op1.operador).tipo == TablaSimbolos::TIPO_ULONG)
		es1Ulong=true;
	bool es2Ulong = false;
	if (op2.esRegistro && op2.operador[0] == 'E' 
		|| !op2.esRegistro && tds->get(op2.operador).tipo == TablaSimbolos::TIPO_ULONG)
		es2Ulong=true;

	operacion *aConvertir = nullptr;

	if (es1Ulong && !es2Ulong){
		aConvertir = &op2;
	}else if (es2Ulong && !es1Ulong){
		aConvertir = &op1;
	}

	string codigo = "";

	if (aConvertir != nullptr){
		//verificar que no sea de un numero negativo
		if (aConvertir->esRegistro || tds->get(aConvertir->operador).tipoSimbolo != TablaSimbolos::CONSTANTE)
			codigo += "CMP "+variableEnCodigo(*aConvertir)+", 0\nJL "+Paso::L_ERROR_CONVERSION+"\n";
		else if (tds->get(aConvertir->operador).valor < 0)
			codigo += "JL "+Paso::L_ERROR_CONVERSION+"\n";

		if (aConvertir->esRegistro){
			aConvertir->operador = "E"+ aConvertir->operador;
			codigo += "AND "+aConvertir->operador+", 65535\n";
		}else{
			string nuevoRegistro = GeneracionCodigo::buscarRegistro(false);
			codigo += "MOV "+ nuevoRegistro + ", "+ variableEnCodigo(*aConvertir) + "\n";
			codigo += "AND E"+nuevoRegistro+", 65535\n";
			aConvertir->operador = "E"+nuevoRegistro;
			aConvertir->esRegistro = true;
		}
	}

	return codigo;
}