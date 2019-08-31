#include "lexico.h"


void AnalizadorLexico::inicializarMatrizDeTransiciones(){
	//**COMPLETAR CON TODAS LAS INICIALIZACIONES**
	inicializarEstadoInicial();
	inicializarEstadoLeyendoIdentificador();
}

AnalizadorLexico::AnalizadorLexico(char* ruta){
	rutaCodigoFuente = ruta; contadorLineas = 1; estadoActual = ESTADO_INICIAL;
	sem_init(&semaforo, 0, 0);
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

	//Cuando termina, ejecutar la última acción semántica con el fin de archivo
	accion = matrizTransiciones[estadoActual][CATEGORIA_FIN_ARCHIVO];
	if (accion.accionSemantica != nullptr)
		accion.accionSemantica(this, c);
	estadoActual = accion.nuevoEstado;


	infile.close();
}

void AnalizadorLexico::retrocederLectura(){ infile.seekg(infile.tellg() - 1); }

void AnalizadorLexico::agregarSiNoExiste(string key, registroIdentificador r){
	auto search = tablaSimbolosIdentificadores.find(key);
	if (search == tablaSimbolosIdentificadores.end()) {
		//Si no existe 'key' en la tabla de símbolos:
		tablaSimbolosIdentificadores.insert({key, r});
	}
}

void AnalizadorLexico::guardarToken(token nuevoToken){
	mtx.lock();
	colaDeTokens.push(nuevoToken);
	mtx.unlock();
	sem_post(&semaforo);
}

AnalizadorLexico::token AnalizadorLexico::getToken(){
	sem_wait(&semaforo);
	mtx.lock();
	token resultado = colaDeTokens.front();
	colaDeTokens.pop();
	mtx.unlock();
	return resultado;
}