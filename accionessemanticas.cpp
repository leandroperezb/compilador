#include "accionessemanticas.h"
#include "lexico.h"

void AccionesSemanticas::tokenFinal(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	token.id = TOKEN_FINAL;
	lexico->guardarToken(token);
}

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
	AnalizadorLexico::registroIdentificador registro;
	registro.esPalabraReservada = false;
	lexico->agregarSiNoExiste(lexico->identificador, registro);

	//Poner un nuevo token en la cola de tokens listos (para entregar)
	AnalizadorLexico::token token;
	token.id = TOKEN_IDENTIFICADOR;
	token.puntero = lexico->identificador;
	lexico->guardarToken(token);

	lexico->identificador = "";
	lexico->retrocederLectura();
}

void AccionesSemanticas::tokenFinalIdentificador(AnalizadorLexico* lexico, char& c){
	AccionesSemanticas::terminarIdentificador(lexico, c);
	AccionesSemanticas::tokenFinal(lexico, c);
}

//Constantes
void AccionesSemanticas::terminarConstante(AnalizadorLexico* lexico, char& c){
	//**ENTREGAR EL TOKEN**

	lexico->identificador = "";
	lexico->retrocederLectura();
}