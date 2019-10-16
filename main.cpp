#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"
#include "accionessintactico.h"
#include <vector>

using namespace std;


vector<string> punteros;
vector<vector<string>> listas_variables;

AnalizadorLexico *elLexico;
TablaSimbolos *laTabla;

int yylex();

void yyerror(const char *s){
	cout << s << endl;
}

bool abortarCompilacion = false;

#include "y.tab.c"

int yylex(){
	AnalizadorLexico::token token = elLexico->getToken();
	yylval = punteros.size();
	punteros.push_back(token.puntero);
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
	laTabla = &tabla;

	AnalizadorLexico ana(rutaCodigoFuente, &tabla);
	elLexico = &ana;

	int resultado = yyparse();
	if (abortarCompilacion)
		resultado = 1;
	cout << "Resultado del parser: " << resultado << endl;

	tabla.guardar();

	return 0;
}