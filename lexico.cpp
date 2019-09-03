#include "lexico.h"

AnalizadorLexico::AnalizadorLexico(char* ruta){
	rutaCodigoFuente = ruta; contadorLineas = 1; estadoActual = ESTADO_INICIAL;
	sem_init(&semaforo, 0, 0);

	//Precarga de palabras reservadas
	string arr[12] = {"if","else","end_if","print","int","begin","end","for","class","public","private","ulong"};
	for (int i= 0 ; i< 12; i++){
		registroIdentificador registro;
		registro.esPalabraReservada = true;
		registro.id = i;
		tablaSimbolosIdentificadores.insert({arr[i], registro});
	}

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
		case '%':
			return CATEGORIA_CADENA;
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

void AnalizadorLexico::guardarTablasDeSimbolos(){
	ofstream ofs;
	ofs.open ("tablas.txt", std::ofstream::out);
	if(ofs.fail()){
		return;
	}

	ofs << "Tabla de símbolos de identificadores:\n(Clave)\t\t(Palabra_Reservada)\t\t(ID)\n";
	unordered_map<string , registroIdentificador>::iterator it;
	for (it = tablaSimbolosIdentificadores.begin(); it != tablaSimbolosIdentificadores.end(); ++it){
		ofs << it->first << "\t\t" << it->second.esPalabraReservada << "\t\t\t" << it->second.id << '\n';
	}

	ofs << "\n\nTabla de símbolos de constantes:\n(Clave)\t\t(Es_Ulong)\t\t(Valor)\n";
	unordered_map<string , registroConstante>::iterator itConstantes;
	for (itConstantes = tablaSimbolosConstantes.begin(); itConstantes != tablaSimbolosConstantes.end(); ++itConstantes){
		ofs << itConstantes->first << "\t\t" << itConstantes->second.esUlong << "\t\t\t" << itConstantes->second.valor << '\n';
	}

	ofs.close();
}

void AnalizadorLexico::retrocederLectura(){ infile.seekg(infile.tellg() - 1); }

void AnalizadorLexico::agregarSiNoExiste(string key, registroIdentificador r){
	auto search = tablaSimbolosIdentificadores.find(key);
	if (search == tablaSimbolosIdentificadores.end()) {
		//Si no existe 'key' en la tabla de símbolos:
		tablaSimbolosIdentificadores.insert({key, r});
	}
}

void AnalizadorLexico::agregarSiNoExiste(string key, registroConstante r){
	auto search = tablaSimbolosConstantes.find(key);
	if (search == tablaSimbolosConstantes.end()) {
		//Si no existe 'key' en la tabla de símbolos:
		tablaSimbolosConstantes.insert({key, r});
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