#include "lexico.h"


void AnalizadorLexico::inicializarMatrizDeTransiciones(){
	//**COMPLETAR CON TODAS LAS INICIALIZACIONES**
	inicializarEstadoInicial();
	inicializarEstadoLeyendoIdentificador();
}

AnalizadorLexico::AnalizadorLexico(char* ruta){
	rutaCodigoFuente = ruta; contadorLineas = 1; estadoActual = ESTADO_INICIAL;
	//**PRECARGAR TABLA DE SÍMBOLOS DE IDENTIFICADORES**
	inicializarMatrizDeTransiciones();
}

int AnalizadorLexico::categorizarCaracter(char& c){
	//**FALTA COMPLETAR CON TODAS LAS CATEGORÍAS NECESARIAS**
	switch(c) {
		case '0' ... '9':
			return CATEGORIA_DIGITO;
		case 'A' ... 'Z':
			return CATEGORIA_LETRA;
		case 'a' ... 'z':
			return CATEGORIA_LETRA;
		case ':':
			return CATEGORIA_DOSPUNTOS;
		case '=':
			return CATEGORIA_IGUAL;
		default:
			return CATEGORIA_INVALIDO;
	}
}

void AnalizadorLexico::analizarCodigo(){
	infile.open(this->rutaCodigoFuente, std::ifstream::in);
	if(infile.fail()){
		return;
	}

	char c; transicion accion;
	while((infile.get(c), infile.eof()) == false){
		//Por cada carácter, ejecutar la acción semántica (si existe) e ir al nuevo estado
		accion = matrizTransiciones[estadoActual][categorizarCaracter(c)];
		if (accion.accionSemantica != nullptr)
			accion.accionSemantica(this, c);
		estadoActual = accion.nuevoEstado;
	}

	//Cuando termina, si no está en el estado inicial, finalizar el token actual (accion a realizar con EOF)
	if (estadoActual != ESTADO_INICIAL){
		c = '\n';
		accion = matrizTransiciones[estadoActual][categorizarCaracter(c)];
		if (accion.accionSemantica != nullptr)
			accion.accionSemantica(this, c);
		estadoActual = accion.nuevoEstado;
	}

	AnalizadorLexico::token tokenFinal;
	tokenFinal.id = TOKEN_FINAL;
	colaDeTokens.push(tokenFinal);

	infile.close();
}

void AnalizadorLexico::aumentarLinea(){ contadorLineas++; }

void AnalizadorLexico::retrocederLectura(){ infile.seekg(infile.tellg() - 1); }

AnalizadorLexico::token AnalizadorLexico::getToken(){
	token resultado = colaDeTokens.front();
	colaDeTokens.pop();
	return resultado;
}