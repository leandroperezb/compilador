#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"
#include <pthread.h>

using namespace std;

void *worker_thread(void *arg)
{
	((AnalizadorLexico *) arg)->analizarCodigo();
}

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
	pthread_t my_thread;
	pthread_create(&my_thread, NULL, &worker_thread, (void *) &ana);

	cout << yyparse() << endl;

	pthread_join(my_thread, NULL);
	tabla.guardar();
	pthread_exit(NULL);

	return 0;
}