#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"
#include "accionessintactico.h"
#include <vector>
#include "polaca.h"
#include "log.h"

using namespace std;

bool Log::abortarCompilacion =  false;
AnalizadorLexico* Log::lexico = nullptr;

vector<string> punteros;
vector<string> lista_variables;

TablaSimbolos *laTabla;

int yylex();

void yyerror(const char *s){
	cout << s << endl;
}

#include "y.tab.c"

int yylex(){
	AnalizadorLexico::token token = Log::lexico->getToken();
	yylval = punteros.size();
	punteros.push_back(token.puntero);
	Log::tokenDetectado(token.id);
	return token.id;
}

int main(int argc, char** argv){
	Polaca::modificarPunteroPolaca(Polaca::polacaMadre);
	char* rutaCodigoFuente;
	if (argc > 1){
		rutaCodigoFuente = argv[1];
	}else{
		return 1;
	}

	TablaSimbolos tabla;
	laTabla = &tabla;

	AnalizadorLexico ana(rutaCodigoFuente, &tabla);
	Log::lexico = &ana;

	AccionesSintactico::inicializar(&punteros);

	int resultado = yyparse();
	if (Log::abortarCompilacion)
		resultado = 1;
	cout << "Resultado del parser: " << resultado << endl;

	tabla.guardar();
	Polaca::polacaMadre.guardar("polaca madre");
	tabla.guardarPolacas();

	return 0;
}