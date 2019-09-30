#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"
#include "accionessintactico.h"
#include <pthread.h>
#include <vector>

using namespace std;

void *worker_thread(void *arg)
{
	((AnalizadorLexico *) arg)->analizarCodigo();
}

vector<string> punteros;

AnalizadorLexico *elLexico;
TablaSimbolos *laTabla;

int yylex();

void yyerror(const char *s){
	cout << s << endl;
}

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
	pthread_t my_thread;
	pthread_create(&my_thread, NULL, &worker_thread, (void *) &ana);

	cout << yyparse() << endl;

	pthread_join(my_thread, NULL);
	tabla.guardar();
	pthread_exit(NULL);

	return 0;
}