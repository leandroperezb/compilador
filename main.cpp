#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"

using namespace std;


AnalizadorLexico *elLexico;

int yylex();

void yyerror(const char *s){
	cout << s << endl;
}

#include "y.tab.c"

int yylex(){
	AnalizadorLexico::token token = elLexico->getToken();
	yylval.cadena = token.puntero.c_str();
	cout << "Token: " << token.id << endl;
	return token.id;
}

int main(int argc, char** argv){
	char* rutaCodigoFuente;
	if (argc > 1){
		rutaCodigoFuente = argv[1];
	}else{
		return 1;
	}

	TablaSimbolos tabla;

	AnalizadorLexico ana(rutaCodigoFuente, &tabla);
	elLexico = &ana;

	cout << yyparse() << endl;

	//Asumo que existe, y lo puedo editar
	TablaSimbolos::registro *asd = &tabla.get("hola");
	(*asd).palabra = "pepe";
	cout << tabla.get("hola").palabra << endl;

	tabla.guardar();

	return 0;
}