#include "accionessintactico.h"
#include <string>

vector<string>* AccionesSintactico::punteros = nullptr;
string AccionesSintactico::claseActual = "";

void AccionesSintactico::inicializar(vector<string>* p){
	AccionesSintactico::punteros = p;
}

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

void AccionesSintactico::declararVariable(TablaSimbolos* tabla, int tipo, vector<string>& variables, int modificador){
	for (int i = 0; i < variables.size(); i++){
		TablaSimbolos::registro* r = &tabla->get(variables[i]);
		if (r->tipoSimbolo != TablaSimbolos::INDEFINIDO)
			return;
		r->tipoSimbolo = TablaSimbolos::VARIABLE;
		(*r).tipo = tipo;
		if (modificador != 0){ //Si es una declaración de una variable dentro de una clase
			(*r).visibilidad = modificador;
			(*r).clasePadre = (*punteros)[tipo];
		}else{
			(*r).clasePadre = "";
		}
	}
	variables.clear();
}

void AccionesSintactico::informarError(string sentencia, string esperado, string obtenido, AnalizadorLexico* lex){
	string msj = "Error en la linea: "+to_string(lex->contadorLineas) + ". Sentencia "+sentencia+", se esperaba "+
	esperado+", pero se obtuvo "+obtenido+"\n";
	
	cout<< msj;
}

void AccionesSintactico::cargarClase(TablaSimbolos* tabla, string clase, string clasePadre){
	if (!tabla->existe(clasePadre) && !tabla->existe(clase))
		return;
	TablaSimbolos::registro* padre = &tabla->get(clasePadre);
	if (padre->tipoSimbolo != TablaSimbolos::CLASE)
		return;
	TablaSimbolos::registro* nuevaClase = &tabla->get(clase);
	if(nuevaClase->tipoSimbolo != TablaSimbolos::INDEFINIDO)
		return;
	nuevaClase->tipoSimbolo = TablaSimbolos::CLASE;
}

void AccionesSintactico::cargarClase(TablaSimbolos* tabla, string clase){
	if (!tabla->existe(clase))
		return;
	TablaSimbolos::registro* nuevaClase = &tabla->get(clase);
	if(nuevaClase->tipoSimbolo != TablaSimbolos::INDEFINIDO)
		return;
	nuevaClase->tipoSimbolo = TablaSimbolos::CLASE;
}