#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"
#include "accionessintactico.h"
#include <vector>
#include "polaca.h"
#include "log.h"

using namespace std;


vector<string> punteros;
vector<string> lista_variables;

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
	Log::tokenDetectado(token.id);
	return token.id;
}

int main(int argc, char** argv){
	Polaca::modificarPunteroPolaca(Polaca::polacaMadre);
	AccionesSintactico::inicializar(&punteros);
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