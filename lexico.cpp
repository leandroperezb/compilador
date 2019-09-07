#include "lexico.h"

AnalizadorLexico::AnalizadorLexico(char* ruta, TablaSimbolos* tabla){
	rutaCodigoFuente = ruta; tablaSimbolos = tabla;
	contadorLineas = 1; estadoActual = ESTADO_INICIAL;

	//Precarga de palabras reservadas
	string arr[12] = {"if","else","end_if","print","int","begin","end","for","class","public","private","ulong"};
	for (int i= 0 ; i< 12; i++){
		TablaSimbolos::registro registro;
		registro.esPalabraReservada = true;
		registro.palabra = arr[i];
		agregarSiNoExiste(arr[i], registro);
	}

	inicializarMatrizDeTransiciones();

	infile.open(this->rutaCodigoFuente, std::ifstream::in);
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
		case '_':
			return CATEGORIA_GUIONBAJO;
		default:
			return CATEGORIA_INVALIDO;
	}
}

void AnalizadorLexico::analizarCodigo(){
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
		if (!colaDeTokens.empty())
			return;
	}

	//Cuando termina, ejecutar la última acción semántica con el fin de archivo
	accion = matrizTransiciones[estadoActual][CATEGORIA_FIN_ARCHIVO];
	if (accion.accionSemantica != nullptr)
		accion.accionSemantica(this, c);
	estadoActual = accion.nuevoEstado;


	infile.close();
}

void AnalizadorLexico::retrocederLectura(){ infile.seekg(infile.tellg() - 1); }

void AnalizadorLexico::agregarSiNoExiste(string key, TablaSimbolos::registro r){
	tablaSimbolos->agregarSiNoExiste(key, r);
}

void AnalizadorLexico::guardarToken(registroToken nuevoToken){
	colaDeTokens.push(nuevoToken);
}

AnalizadorLexico::token AnalizadorLexico::getToken(){
	analizarCodigo();
	registroToken resultado = colaDeTokens.front();	
	colaDeTokens.pop();
	if(resultado.warning != ""){
		cout<<resultado.warning;
	}
	return resultado.token;
}