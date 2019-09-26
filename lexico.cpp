#include "lexico.h"

AnalizadorLexico::AnalizadorLexico(char* ruta, TablaSimbolos* tabla){
	rutaCodigoFuente = ruta; tablaSimbolos = tabla;
	contadorLineas = 1; estadoActual = ESTADO_INICIAL;
	sem_init(&semaforo, 0, 0);

	//Precarga de palabras reservadas
	palabrasReservadas.insert({"if", IF});
	palabrasReservadas.insert({"else", ELSE});
	palabrasReservadas.insert({"end_if", END_IF});
	palabrasReservadas.insert({"print", PRINT});
	palabrasReservadas.insert({"int", INT});
	palabrasReservadas.insert({"begin", BEGIN});
	palabrasReservadas.insert({"end", END});
	palabrasReservadas.insert({"for", FOR});
	palabrasReservadas.insert({"class", CLASS});
	palabrasReservadas.insert({"public", PUBLIC});
	palabrasReservadas.insert({"private", PRIVATE});
	palabrasReservadas.insert({"ulong", ULONG});
	palabrasReservadas.insert({"extends", EXTENDS});
	palabrasReservadas.insert({"void", VOID});

	inicializarMatrizDeTransiciones();
}

int AnalizadorLexico::categorizarCaracter(char& c){
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
		case '\n':
			return CATEGORIA_ENDLINE;
		case '<':
			return CATEGORIA_MENOR;
		case '>':
			return CATEGORIA_MAYOR;
		case '/':
			return CATEGORIA_OPERADOR;
		case '*':
			return CATEGORIA_OPERADOR;
		case '+':
			return CATEGORIA_OPERADOR;
		case '-':
			return CATEGORIA_OPERADOR;
		case ' ':
			return CATEGORIA_ESPACIO;
		case '\t':
			return CATEGORIA_ESPACIO;
		case '\r':
			return CATEGORIA_ESPACIO;
		case '#':
			return CATEGORIA_COMENTARIO;
		case '{':
			return CATEGORIA_INICIOCADENA;
		case '}':
			return CATEGORIA_FINCADENA;
		case '(':
			return CATEGORIA_OPERADOR;
		case ')':
			return CATEGORIA_OPERADOR;
		case ';':
			return CATEGORIA_OPERADOR;
		case ',':
			return CATEGORIA_OPERADOR;
		case '.':
			return CATEGORIA_OPERADOR;
		case '_':
			return CATEGORIA_GUIONBAJO;
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

void AnalizadorLexico::agregarEnTabla(string key, TablaSimbolos::registro r){
	tablaSimbolos->agregar(key, r);
}

void AnalizadorLexico::guardarToken(registroToken nuevoToken){
	mtx.lock();
	colaDeTokens.push(nuevoToken);
	mtx.unlock();
	sem_post(&semaforo);
}

AnalizadorLexico::token AnalizadorLexico::getToken(){
	sem_wait(&semaforo);
	mtx.lock();
	registroToken resultado = colaDeTokens.front();
	colaDeTokens.pop();
	mtx.unlock();
	if(resultado.warning != ""){
		cout<<resultado.warning;
	}
	return resultado.token;
}