#include "accionessemanticas.h"
#include "lexico.h"
#include <string>

void AccionesSemanticas::tokenFinal(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	token.id = TOKEN_FINAL;
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
	

	//Agregar a la tabla de símbolos:
	TablaSimbolos::registro registro;
	registro.esPalabraReservada = false;
	registro.palabra = lexico->identificador;
	lexico->agregarSiNoExiste(lexico->identificador, registro);

	//Poner un nuevo token en la cola de tokens listos (para entregar)
	AnalizadorLexico::token token;
	token.id = TOKEN_IDENTIFICADOR;
	token.puntero = lexico->identificador;
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
	lexico->agregarSiNoExiste(lexico->identificador, registro);

	//Poner un nuevo token en la cola de tokens listos (para entregar)
	AnalizadorLexico::token token;
	token.id = TOKEN_CONSTANTE;
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
		token.id = TOKEN_MAYORIGUAL;
	}else{
		token.id = TOKEN_MAYOR;
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
		token.id = TOKEN_MENORIGUAL;
	} else if(c == '>'){
		token.id = TOKEN_DISTINTO;
	} else{
		token.id = TOKEN_MENOR;
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
		TOKEN_IGUAL, ""
	};
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

//Asignacion
void AccionesSemanticas::entregarAsignacion(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token = {
		TOKEN_ASIGNACION, ""
	};
	lexico->guardarToken({token, lexico->wrnng});
	lexico->wrnng = "";
}

//Cadena
void AccionesSemanticas::entregarCadena(AnalizadorLexico* lexico, char& c){
	AnalizadorLexico::token token;
	token.id = TOKEN_STRING;
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
	AnalizadorLexico::token token;
	token.puntero = "";
	switch (c){
	case '+':
		token.id = TOKEN_SUMA;
		break;
	case '-':
		token.id = TOKEN_RESTA;
		break;
	case '/':
		token.id = TOKEN_DIVISION;
		break;
	case '*':
		token.id = TOKEN_MULTIPLICACION;
		break;
	case '(':
		token.id = TOKEN_PARENTESISAPERTURA;
		break;
	case ')':
		token.id = TOKEN_PARENTESISCIERRE;
		break;
	case ',':
		token.id = TOKEN_COMA;
		break;
	case ';':
		token.id = TOKEN_PUNTOCOMA;
		break;
	default:
		break;
	}
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
		TOKEN_ERROR, ""
	};
	lexico->guardarToken({token, lexico->wrnng+ "Error: caracter '"+s+"' no esperado en la linea "+to_string(lexico->contadorLineas)+"\n"});
	lexico->wrnng = "";
}