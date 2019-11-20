#include "accionessintactico.h"
#include "pasofactor.h"
#include <string>
#include "log.h"

vector<string>* AccionesSintactico::punteros = nullptr;
string AccionesSintactico::claseActual = "";
unordered_map<string, vector<string>> AccionesSintactico::variablesDeClase;

void AccionesSintactico::inicializar(vector<string>* p){
	AccionesSintactico::punteros = p;
}

void AccionesSintactico::negativizarConstante(TablaSimbolos* tabla, vector<string>& punteros, int indice){
	if (indice < 0){
		TablaSimbolos::registro r;
		r.tipoSimbolo = TablaSimbolos::CONSTANTE; r.tipo = TablaSimbolos::TIPO_INT; r.valor = -1;
		tabla->agregar("-1", r);
		Polaca::polacaEnEdicion->cargarFactor("-1");
		Polaca::polacaEnEdicion->cargarOperador('*');
		return;
	}
	string key = punteros[indice];
	TablaSimbolos::registro r = tabla->get(key);
	if (r.tipoSimbolo == TablaSimbolos::CONSTANTE){
		r.valor = r.valor * (-1);
		r.tipo = TablaSimbolos::TIPO_INT;
		if (r.valor < -32768){
			Log::warning("Constante " +to_string(r.valor)+ " en la linea " +to_string(Log::lexico->contadorLineas)+" fuera de rango de los int negativos. Se modificará por -32768\n");
			r.valor = -32768;
		}
		tabla->agregar(to_string(r.valor), r); //Agregar una nueva constante a la tabla de símbolos, la negativa
		punteros[indice] = to_string(r.valor); //Para que la lista de punteros ahora apunte a la constante modificada en negativo
		((PasoFactor*) Polaca::polacaEnEdicion->getLastPaso())->setFactor(to_string(r.valor));

		tabla->constanteNegativizada(key);
	}
}

void AccionesSintactico::inicializarVariablesDeObjeto(TablaSimbolos* tabla, string objeto, string clase){
	while (clase != ""){//Mientras esté recorriendo la línea de herencia
		//Por cada variable de esta clase
		for (int i = 0; i < variablesDeClase[clase].size(); i++){
			string nombreVariable = variablesDeClase[clase][i];
			TablaSimbolos::registro* r = &tabla->get(nombreVariable);
			TablaSimbolos::registro nuevaVariable;
			nuevaVariable.tipo = (*r).tipo; nuevaVariable.visibilidad = (*r).visibilidad;
			nuevaVariable.clasePadre = (*r).clasePadre; nuevaVariable.tipoSimbolo = (*r).tipoSimbolo;
			tabla->agregar(objeto + "." + nombreVariable, nuevaVariable);
		}
		clase = (&tabla->get(clase))->clasePadre;
	}
}

void AccionesSintactico::declararVariable(TablaSimbolos* tabla, int tipo, vector<string>& variables, int modificador){
	auto search = AccionesSintactico::variablesDeClase.find(AccionesSintactico::claseActual);
	if (search == AccionesSintactico::variablesDeClase.end()) {
		AccionesSintactico::variablesDeClase.insert({AccionesSintactico::claseActual, vector<string>()});
		search = AccionesSintactico::variablesDeClase.find(AccionesSintactico::claseActual);
	}
	vector<string>* vectorVariables = &(search->second);

	for (int i = 0; i < variables.size(); i++){
		TablaSimbolos::registro* r = &tabla->get(variables[i]);
		if (r->tipoSimbolo != TablaSimbolos::INDEFINIDO){
			if ( r->tipoSimbolo == TablaSimbolos::VARIABLE )
				Log::redeclaracionVariable(": Redeclaracion, Existe una variable/atributo con el nombre :\""+variables[i]+"\"");
			else
				if (r->tipoSimbolo == TablaSimbolos::METODO)
					Log::redeclaracionVariable(": Redeclaracion, Existe un metodo con el nombre :\""+variables[i]+"\"");
				else
					Log::redeclaracionVariable(": Redeclaracion, Existe una clase con el nombre :\""+variables[i]+"\"");
				variables.clear();
				return;
		}

		if (modificador != 0){ //Si es una declaración de una variable dentro de una clase
			(*r).visibilidad = modificador;
			(*r).clasePadre = claseActual;
			vectorVariables->push_back(variables[i]);
		}else{
			(*r).clasePadre = "";
			if (tipo >= 0){ //Si el tipo no es un primitivo, guardar en la tabla de símbolos las variables para el objeto
				if (tabla->get((*punteros)[tipo]).tipoSimbolo != TablaSimbolos::CLASE){
					Log::noExisteClase((*punteros)[tipo]);
					return;
				}
				inicializarVariablesDeObjeto(tabla, variables[i], (*punteros)[tipo]);
			}
		}

		r->tipoSimbolo = TablaSimbolos::VARIABLE;
		(*r).tipo = tipo;
	}
	variables.clear();
}



void AccionesSintactico::cargarClase(TablaSimbolos* tabla, string clase, string clasePadre){
	if (!tabla->existe(clasePadre)/*  && !tabla->existe(clase) */){
		Log::noExisteClase(clasePadre);
		if(!tabla->existe(clase))
			Log::noExisteClase(clase);
		return;
	}
	TablaSimbolos::registro* padre = &tabla->get(clasePadre);
	if (padre->tipoSimbolo != TablaSimbolos::CLASE){
		Log::identificadorNoCorresponde(clasePadre, "una clase");
		return;
	}
	TablaSimbolos::registro* nuevaClase = &tabla->get(clase);
	if(nuevaClase->tipoSimbolo != TablaSimbolos::INDEFINIDO){
		Log::redeclaracionClase(clase);
		return;
	}
	nuevaClase->tipoSimbolo = TablaSimbolos::CLASE;
	nuevaClase->clasePadre = clasePadre;
	AccionesSintactico::claseActual = clase;
}

void AccionesSintactico::cargarClase(TablaSimbolos* tabla, string clase){
	if (!tabla->existe(clase)){
		Log::noExisteClase(clase);
		return;
	}
	TablaSimbolos::registro* nuevaClase = &tabla->get(clase);
	if(nuevaClase->tipoSimbolo != TablaSimbolos::INDEFINIDO){
		Log::redeclaracionClase(clase);
		return;
	}
	nuevaClase->tipoSimbolo = TablaSimbolos::CLASE;
	AccionesSintactico::claseActual = clase;
}

void AccionesSintactico::finalizarClase(){
	AccionesSintactico::claseActual = "";
}

void AccionesSintactico::nuevoFactor(TablaSimbolos* tabla, string factor){
	if(!tabla->existe(factor)){
		Log::identificadorNoDefinido(factor);
		return;
	}
	TablaSimbolos::registro* variable = &tabla->get(factor);
	if(variable->tipoSimbolo != TablaSimbolos::VARIABLE){
		Log::identificadorNoCorresponde(factor, "una variable");
		return;
	}
	if(variable->tipo >= 0){
		Log::operacionConObjeto(factor);
		return;
	}
	if(claseActual == ""){ //Si estamos en el "main"
		if(variable->clasePadre != ""){
			Log::variableDeClase(factor, variable->clasePadre);
			return;
		}
	}else{ // Si estamos dentro de un metodo
		if(claseActual != variable->clasePadre && variable->visibilidad == TablaSimbolos::PRIVAT){ //Si es privado, que sea sólo de clase actual
			Log::accesoAtributoPrivado(factor, claseActual, variable->clasePadre);
			return;
		}
		if(!hereda(tabla, claseActual, variable->clasePadre)){ //Por el contrario, para los públicos, que sea de la línea de herencia
			Log::accesoAtributoFueraHerencia(factor, claseActual, variable->clasePadre);
			return;
		}
	}
	Polaca::polacaEnEdicion->cargarFactor(factor);
}
void AccionesSintactico::nuevoFactorDeClase(TablaSimbolos* tabla, string obj,string variable){
	if(!tabla->existe(obj + "." + variable)){ //Si no existe, algo está mal (o el objeto, o la variable)
		if(!tabla->existe(obj)){
			Log::identificadorNoDefinido(obj);
			return;
		}
		TablaSimbolos::registro r = tabla->get(obj);
		if(r.tipoSimbolo != TablaSimbolos::VARIABLE || r.tipo < 0){
			Log::identificadorNoCorresponde(obj, "un objeto");
			return;
		}
		Log::identificadorNoCorresponde(variable, "un atributo del objeto \""+obj+"\"");
		return;
	}
	TablaSimbolos::registro* var = &tabla->get(obj + "." + variable);
	if(var->tipoSimbolo != TablaSimbolos::VARIABLE){
		Log::identificadorNoCorresponde(variable, "un atributo del objeto \""+obj+"\"");
		return;
	}
	if(var->visibilidad == TablaSimbolos::PRIVAT){
		Log::accesoAtributoPrivado(variable, var->clasePadre);
		return;
	}

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
	if (r->tipoSimbolo != TablaSimbolos::INDEFINIDO){
		if ( r->tipoSimbolo == TablaSimbolos::VARIABLE )
			Log::redeclaracionVariable(": Redeclaracion, Existe una variable con el nombre :\""+nombre+"\"");
		else
			if (r->tipoSimbolo == TablaSimbolos::METODO)
				Log::redeclaracionVariable(": Redeclaracion, Existe un metodo con el nombre :\""+nombre+"\"");
			else
				Log::redeclaracionVariable(": Redeclaracion, Existe una clase con el nombre :\""+nombre+"\"");
		return;
	}
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

void AccionesSintactico::llamadoAMetodo(TablaSimbolos* tabla, string objeto, string metodo){
	if(!tabla->existe(objeto)){
		Log::identificadorNoDefinido(objeto);
		return;
	}
	if(!tabla->existe(metodo)){
		Log::identificadorNoDefinido(metodo);
		return;
	}
	TablaSimbolos::registro* obj = &tabla->get(objeto);
	TablaSimbolos::registro* met = &tabla->get(metodo);
	if(obj->tipoSimbolo != TablaSimbolos::VARIABLE){
		Log::identificadorNoCorresponde(objeto, "un objeto");
		return;
	}
	if(met->tipoSimbolo != TablaSimbolos::METODO){
		Log::identificadorNoCorresponde(metodo, "un metodo");
		return;
	}
	if(obj->tipo < 0){
		Log::identificadorNoCorresponde(objeto, "un objeto");
		return;
	}

	// Si el método no es de la línea de herencia del objeto
	if (!hereda(tabla, (*punteros)[obj->tipo], met->clasePadre)){
		Log::metodoNoHeredado(metodo, (*punteros)[obj->tipo]);
		return;
	}

	if(met->visibilidad == TablaSimbolos::PRIVAT){ // Si es método privado
		Log::accesoAtributoPrivado(metodo, met->clasePadre);
		return;
	}
	Polaca::polacaEnEdicion->invocacionMetodo(objeto, metodo, (&tabla->get(metodo))->polaca);
}