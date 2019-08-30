#include <iostream>
#include "lexico.h"

using namespace std;

int main(int argc, char** argv){
	char* rutaCodigoFuente;
	if (argc > 1){
		rutaCodigoFuente = argv[1];
	}else{
		return 1;
	}

	AnalizadorLexico ana(rutaCodigoFuente);
	ana.analizarCodigo();

	//Leer todos los tokens que generó en léxico (no será así el procedimiento real, pero para probar)
	AnalizadorLexico::token token;
	while (true){
		token = ana.getToken();
		if (token.id == TOKEN_FINAL)
			break;
		cout << token.puntero << endl;
	}

	return 0;
}