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
	AccionesSintactico::claseActual = clase;
}

void AccionesSintactico::cargarClase(TablaSimbolos* tabla, string clase){
	if (!tabla->existe(clase))
		return;
	TablaSimbolos::registro* nuevaClase = &tabla->get(clase);
	if(nuevaClase->tipoSimbolo != TablaSimbolos::INDEFINIDO)
		return;
	nuevaClase->tipoSimbolo = TablaSimbolos::CLASE;
	AccionesSintactico::claseActual = clase;
}

void AccionesSintactico::finalizarClase(){
	AccionesSintactico::claseActual = "";
}

void AccionesSintactico::nuevoFactor(TablaSimbolos* tabla, string factor){
	if(!tabla->existe(factor))
		return;
	TablaSimbolos::registro* variable = &tabla->get(factor);
	if(variable->tipoSimbolo != TablaSimbolos::VARIABLE)
		return;
	if(claseActual == ""){ //Si estamos en el "main"
		if(variable->clasePadre != "")
			return;
	}else{ // Si estamos dentro de un metodo
		if(claseActual != variable->clasePadre && variable->visibilidad == TablaSimbolos::PRIVAT)
			return;
		if(!hereda(tabla, claseActual, variable->clasePadre))
			return;
	}
	Polaca::polacaEnEdicion->cargarFactor(factor);
}
void AccionesSintactico::nuevoFactorDeClase(TablaSimbolos* tabla, string obj,string variable){
	if(!tabla->existe(obj) || !tabla->existe(variable))
		return;
	TablaSimbolos::registro* objeto = &tabla->get(obj);
	TablaSimbolos::registro* var = &tabla->get(variable);
	if(objeto->tipoSimbolo != TablaSimbolos::VARIABLE || var->tipoSimbolo != TablaSimbolos::VARIABLE)
		return;
	if(objeto->tipo < 0)
		return;
	if(var->visibilidad == TablaSimbolos::PRIVAT)
		return;
	string clase = (*punteros)[objeto->tipo];
	if(!hereda(tabla, clase, var->clasePadre))
		return;
	Polaca::polacaEnEdicion->cargarFactor(obj+"."+variable);
}
bool AccionesSintactico::hereda(TablaSimbolos* tabla, string claseHijo, string clasePadre){
	do{
		if(claseHijo == clasePadre){
			return true;
		}
		claseHijo = (&tabla->get(claseHijo))->clasePadre;
	}
	while(claseHijo != "");
	return false;
}
void AccionesSintactico::nuevoMetodo(TablaSimbolos* tabla, string nombre, int visibilidad){
	TablaSimbolos::registro* r = &tabla->get(nombre);
	if (r->tipoSimbolo != TablaSimbolos::INDEFINIDO)
		return;
	r->tipoSimbolo = TablaSimbolos::METODO;
	(*r).visibilidad = visibilidad;
	(*r).clasePadre = AccionesSintactico::claseActual;
	Polaca *nuevaPolaca = new Polaca();
	(*r).polaca = nuevaPolaca;
	Polaca::modificarPunteroPolaca(*nuevaPolaca);
}
void AccionesSintactico::finalizarMetodo(){
	Polaca::modificarPunteroPolaca(Polaca::polacaMadre);
}