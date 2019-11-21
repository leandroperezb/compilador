#include "lexico.h"
#include "log.h"


AnalizadorLexico::AnalizadorLexico(char* ruta, TablaSimbolos* tabla){
	rutaCodigoFuente = ruta; tablaSimbolos = tabla;
	contadorLineas = 1; estadoActual = ESTADO_INICIAL;

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
	palabrasReservadas.insert({"downto", DOWNTO});

	inicializarMatrizDeTransiciones();

	infile.open(this->rutaCodigoFuente, std::ifstream::in);
	if(infile.fail()){
		cout << "Error al abrir el archivo de código fuente" << endl;
		exit(1);
	}
}

int AnalizadorLexico::categorizarCaracter(char& c){
	if( c >= '0' && c <= '9')
		return CATEGORIA_DIGITO;
	if( c >= 'A' && c <= 'Z')
		return CATEGORIA_LETRA;
	if( c >= 'a' && c <= 'z')
		return CATEGORIA_LETRA;
	switch(c) {
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
	char c; transicion accion;
	while((getCaracter(c), infile.eof()) == false){
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

void AnalizadorLexico::getCaracter(char &c){
	if (!retroceder)
		infile.get(c);
	else
		c = ultimoChar;
	ultimoChar = c;
	retroceder = false;
}

void AnalizadorLexico::retrocederLectura(){
	retroceder = true;
}

void AnalizadorLexico::agregarEnTabla(string key, TablaSimbolos::registro r){
	if (r.tipoSimbolo == TablaSimbolos::CONSTANTE && tablaSimbolos->existe(key)){
		TablaSimbolos::registro *r = &tablaSimbolos->get(key);
		(*r).visibilidad++;
	}else{
		tablaSimbolos->agregar(key, r);
	}
}

void AnalizadorLexico::guardarToken(registroToken nuevoToken){
	colaDeTokens.push(nuevoToken);
}

AnalizadorLexico::token AnalizadorLexico::getToken(){
	analizarCodigo();
	registroToken resultado = colaDeTokens.front();	
	colaDeTokens.pop();
	if(resultado.warning != ""){
		Log::warning(resultado.warning);
	}
	return resultado.token;
}