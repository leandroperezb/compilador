#include "accionessemanticas.h"
#include "lexico.h"

void AccionesSemanticas::tokenFinal(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	token.id = TOKEN_FINAL;
	lexico->guardarToken(token);
}

void AccionesSemanticas::nuevaLinea(AnalizadorLexico* lexico, char& c){
	lexico->contadorLineas++;
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
	//Control de longitud máxima
	if (lexico->identificador.length() > 25){
		//Warning **HAY QUE MODIFICAR ESTO. NO ESTÁ BUENO IMPRIMIR ACÁ**
		string warning = "Warning: te trunqué la variable en la línea "+to_string(lexico->contadorLineas)+"\n";
		cout << warning;
		lexico->identificador.resize(25);
	}

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