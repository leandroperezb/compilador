#include "accionessemanticas.h"
#include "lexico.h"
#include <string>

void AccionesSemanticas::tokenFinal(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	token.id = FINAL;
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

void AccionesSemanticas::nuevaLinea(AnalizadorLexico* lexico, char& c){
	lexico->contadorLineas++;
}

//Identificadores y constantes
void AccionesSemanticas::iniciarIdentificador(AnalizadorLexico* lexico, char& c){
	lexico->identificador = c;
}
void AccionesSemanticas::agregarCaracter(AnalizadorLexico* lexico, char& c){
	if (c == '\r') return; //En casos de Strings se puede llegar a llamar con Carriage Return, pero lo ignoramos
	lexico->identificador = lexico->identificador + c;
}

//Identificadores
void AccionesSemanticas::terminarIdentificador(AnalizadorLexico* lexico, char& c){
	//Control de longitud máxima
	if (lexico->identificador.length() > 25){
		lexico->wrnng = lexico->wrnng+"Warning: te trunqué la variable en la línea "+to_string(lexico->contadorLineas)+"\n";
		lexico->identificador.resize(25);
	}

	//Poner un nuevo token en la cola de tokens listos (para entregar)
	AnalizadorLexico::token token;
	auto search = lexico->palabrasReservadas.find(lexico->identificador);
	if (search != lexico->palabrasReservadas.end()) {
		//Si es una palabra reservada, guardar el token con el ID de la palabra reservada
		token.id = search->second;
	}else{
		token.id = ID;
		token.puntero = lexico->identificador;

		//Agregar a la tabla de símbolos:
		TablaSimbolos::registro registro;
		registro.palabra = lexico->identificador;
		lexico->agregarEnTabla(lexico->identificador, registro);
	}
	lexico->guardarToken({token, lexico->wrnng});

	lexico->identificador = "";
	lexico->retrocederLectura();
	lexico->wrnng = "";
}

void AccionesSemanticas::tokenFinalIdentificador(AnalizadorLexico* lexico, char& c){
	AccionesSemanticas::terminarIdentificador(lexico, c);
	AccionesSemanticas::tokenFinal(lexico, c);
}

//Constantes
void AccionesSemanticas::terminarConstante(AnalizadorLexico* lexico, char& c){
	unsigned long long numero = 0;
	for (int i = 0; i < lexico->identificador.length(); i++){
		numero = numero * 10 + int(lexico->identificador[i]) - 48;
		if (numero > 4294967295LL){
			lexico->wrnng = lexico->wrnng+"Warning: constante fuera de rango en la línea "+to_string(lexico->contadorLineas)+"\n";
			lexico->identificador = "";
			lexico->retrocederLectura();
			return;
		}
	}

	//Agregar a la tabla de símbolos:
	TablaSimbolos::registro registro;
	registro.esUlong = (numero > 32767); registro.valor = numero;
	lexico->agregarEnTabla(lexico->identificador, registro);

	//Poner un nuevo token en la cola de tokens listos (para entregar)
	AnalizadorLexico::token token;
	token.id = CTE;
	token.puntero = lexico->identificador;
	lexico->guardarToken({token, lexico->wrnng});
	

	lexico->identificador = "";
	lexico->retrocederLectura();
	lexico->wrnng = "";
}

void AccionesSemanticas::tokenFinalConstante(AnalizadorLexico* lexico, char& c){
	AccionesSemanticas::terminarConstante(lexico, c);
	AccionesSemanticas::tokenFinal(lexico, c);
}

//Mayor( o Igual)
void AccionesSemanticas::terminarMayor(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	if(c == '='){
		token.id = MAYORIGUAL;
	}else{
		token.id = toascii('>');
		lexico->retrocederLectura();
	}
	token.puntero = "";
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

void AccionesSemanticas::terminarFinalMayor(AnalizadorLexico* lexico, char& c){
	AccionesSemanticas::terminarMayor(lexico, c);
	AccionesSemanticas::tokenFinal(lexico, c);
}

//Menor(o Igual, o distinto)
void AccionesSemanticas::terminarMenor(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	if(c == '='){
		token.id = MENORIGUAL;
	} else if(c == '>'){
		token.id = DISTINTO;
	} else{
		token.id = toascii('<');
		lexico->retrocederLectura();
	}
	token.puntero = "";
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

void AccionesSemanticas::terminarFinalMenor(AnalizadorLexico* lexico, char& c){
	AccionesSemanticas::terminarMenor(lexico, c);
	AccionesSemanticas::tokenFinal(lexico, c);
}

//Igualdad
void AccionesSemanticas::entregarIgual(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token = {
		IGUAL, ""
	};
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

//Asignacion
void AccionesSemanticas::entregarAsignacion(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token = {
		ASIGNACION, ""
	};
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

//Cadena
void AccionesSemanticas::entregarCadena(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	token.id = STRING;
	token.puntero = lexico->identificador;
	lexico->identificador = "";
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

void AccionesSemanticas::entregarFinalCadena(AnalizadorLexico* lexico, char& c){
	lexico->wrnng = lexico->wrnng + "Warning: se esperaba '}' al final de cadena en la línea "+to_string(lexico->contadorLineas)+"\n";
	AccionesSemanticas::entregarCadena(lexico, c);
	AccionesSemanticas::tokenFinal(lexico, c);
}

//Operadores('+', '-', '/', '*', '(', ')', ',', ';')
void AccionesSemanticas::entregarOperador(AnalizadorLexico *lexico, char& c){
	AnalizadorLexico::token token = {toascii(c), ""};
	lexico->guardarToken({token,lexico->wrnng});
	lexico->wrnng = "";
}

void AccionesSemanticas::warning(AnalizadorLexico* lexico, char& c){
	string s(1, c);
	lexico->wrnng = lexico->wrnng + "Warning: supresión caracter '"+s+"' no esperado en la línea "+to_string(lexico->contadorLineas)+"\n";
}

void AccionesSemanticas::error(AnalizadorLexico* lexico, char& c){
	string s(1, c);
	AnalizadorLexico::token token = {
		ERROR, ""
	};
	lexico->guardarToken({token, lexico->wrnng+ "Error: caracter '"+s+"' no esperado en la linea "+to_string(lexico->contadorLineas)+"\n"});
	lexico->wrnng = "";
}