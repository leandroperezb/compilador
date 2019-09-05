#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"
#include <pthread.h>

using namespace std;

void *worker_thread(void *arg)
{
	((AnalizadorLexico *) arg)->analizarCodigo();
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
	pthread_t my_thread;
	pthread_create(&my_thread, NULL, &worker_thread, (void *) &ana);

	//Leer todos los tokens que generó en léxico (no será así el procedimiento real, pero para probar)
	AnalizadorLexico::token token;
	while (true){
		token = ana.getToken();
		if (token.id == TOKEN_FINAL)
			break;
		cout << token.puntero << endl;
	}

	pthread_join(my_thread, NULL);
	tabla.guardar();
	pthread_exit(NULL);

	return 0;
}