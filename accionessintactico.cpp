#include "accionessintactico.h"

void AccionesSintactico::negativizarConstante(TablaSimbolos* tabla, vector<string>& punteros, int indice){
	string key = punteros[indice];
	TablaSimbolos::registro r = tabla->get(key);
	if (r.tipoSimbolo == TablaSimbolos::CONSTANTE){
		r.valor = r.valor * (-1);
		r.tipo = TablaSimbolos::TIPO_INT;
		if (r.valor < -32768){
			cout << "Constante " << r.valor << " fuera de rango de los int negativos. Se modificará por -32768" << endl;
			r.valor = -32768;
		}
		tabla->agregar(to_string(r.valor), r); //Agregar una nueva constante a la tabla de símbolos, la negativa
		punteros[indice] = to_string(r.valor); //Para que la lista de punteros ahora apunte a la constante modificada en negativo
	}
}

void AccionesSintactico::asignarTipos(TablaSimbolos* tabla, int tipo, vector<string> variables){
	for (int i = 0; i < variables.size(); i++){
		TablaSimbolos::registro* r = &tabla->get(variables[i]);
		(*r).tipo = tipo;
	}
}
void AccionesSintactico::informarError(string sentencia, string esperado, string obtenido, AnalizadorLexico* lex){
	string msj = "Error en la linea: "+to_string(lex->contadorLineas) + ". Sentencia "+sentencia+", se esperaba "+
	esperado+", pero se obtuvo "+obtenido+"\n";
	
	cout<< msj;
}
