#include "lexico.h"
//Inicializar las transiciones con: {nuevoEstado, funcionAEjecutar}

void AnalizadorLexico::inicializarEstadoInicial(){
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_CONSTANTE, &AccionesSemanticas::iniciarIdentificador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_LETRA] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::iniciarIdentificador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DOSPUNTOS] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_IGUAL] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MENOR] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MAYOR] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_OPERADOR] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::nuevaLinea};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinal};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_ESPACIO] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_COMENTARIO] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_PUNTOYCOMA] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_COMA] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_PARENTESIS] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_CADENA] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_GUIONBAJO] = {ESTADO_INICIAL, nullptr};
}


void AnalizadorLexico::inicializarEstadoLeyendoIdentificador(){
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_LETRA] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_DOSPUNTOS] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_IGUAL] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_MENOR] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_MAYOR] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_OPERADOR] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinalIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_ESPACIO] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_COMENTARIO] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_PUNTOYCOMA] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_COMA] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_PARENTESIS] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_CADENA] = {ESTADO_INICIAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_GUIONBAJO] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
}

void AnalizadorLexico::inicializarEstadoLeyendoConstante(){
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_CONSTANTE, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_LETRA] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_DOSPUNTOS] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_IGUAL] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_MENOR] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_MAYOR] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_OPERADOR] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinalConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_ESPACIO] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_COMENTARIO] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_PUNTOYCOMA] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_COMA] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_PARENTESIS] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_CADENA] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_GUIONBAJO] = {ESTADO_INICIAL, &AccionesSemanticas::terminarConstante};
}