#include "accionessemanticas.h"
#include "lexico.h"


//Identificadores y constantes
void AccionesSemanticas::iniciarIdentificador(AnalizadorLexico* lexico, char& c){
	lexico->identificador = c;
}
void AccionesSemanticas::agregarCaracter(AnalizadorLexico* lexico, char& c){
	lexico->identificador = lexico->identificador + c;
}

//Identificadores
void AccionesSemanticas::terminarIdentificador(AnalizadorLexico* lexico, char& c){
	//Agregar a la tabla de símbolos:
	auto search = lexico->tablaSimbolosIdentificadores.find(lexico->identificador);
	if (search == lexico->tablaSimbolosIdentificadores.end()) {
		//Si no existe previamente en la tabla de símbolos:
		AnalizadorLexico::registroIdentificador registro;
		registro.esPalabraReservada = false; //Sabemos esto porque a la spalabras reservadas las habremos precargado
		lexico->tablaSimbolosIdentificadores.insert({lexico->identificador, registro});
	}

	//Poner un nuevo token en la cola de tokens listos (para entregar)
	AnalizadorLexico::token token;
	token.id = TOKEN_IDENTIFICADOR;
	token.puntero = lexico->identificador;
	lexico->mtx.lock();
	lexico->colaDeTokens.push(token);
	lexico->mtx.unlock();
	sem_post(&(lexico->semaforo));

	lexico->identificador = "";
	lexico->retrocederLectura();
}

//Constantes
void AccionesSemanticas::terminarConstante(AnalizadorLexico* lexico, char& c){
	//**ENTREGAR EL TOKEN**

	lexico->identificador = "";
	lexico->retrocederLectura();
}