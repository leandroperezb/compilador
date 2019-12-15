#include <iostream>
#include "lexico.h"
#include "tablasimbolos.h"
#include "accionessintactico.h"
#include <vector>
#include "polaca.h"
#include "log.h"
#include <fstream>

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

char* fileOutputAsm(char* sourceFile){
	int sizeFile = strlen(sourceFile);
	char *output = new char[sizeFile + 1 + 4]; //+1 for \0. +4 for ".asm"
	strncpy(output, sourceFile, sizeFile);
	
	int indexExtension = sizeFile;
	for (int i = 0; i < sizeFile; i++){
		if (sourceFile[i] == '.')
			indexExtension = i; //Write extension since last comma finded
	}

	strncpy(output + indexExtension, ".asm", 5); //Copy extension (and \0) since output at indexExtension index

	return output;
}

int main(int argc, char** argv){
	Polaca::modificarPunteroPolaca(Polaca::polacaMadre);
	char* rutaCodigoFuente;
	if (argc > 1){
		rutaCodigoFuente = argv[1];
	}else{
		cout << "Debe introducir la ruta al código fuente por parámetro" << endl;
		return 1;
	}

	TablaSimbolos tabla;
	laTabla = &tabla;
	Paso::tds = &tabla;

	AnalizadorLexico ana(rutaCodigoFuente, &tabla);
	Log::lexico = &ana;

	AccionesSintactico::inicializar(&punteros);

	int resultado = yyparse();

	tabla.guardar();

	if (!Log::abortarCompilacion){
		Polaca::polacaMadre.guardar("polaca_principal");
		tabla.guardarPolacas();

		ofstream ofs;

		char* dir = fileOutputAsm(argv[1]);
		ofs.open (dir, std::ofstream::out);
		if(ofs.fail()){
			return 1;
		}

		ofs << GeneracionCodigo::generarCodigo(&Polaca::polacaMadre);

		ofs.close();

		delete[] dir;

		cout << "Código compilado correctamente" << endl;
	}

	if (Log::abortarCompilacion)
		cout << "Fallo en la compilación" << endl;

	return 0;
}