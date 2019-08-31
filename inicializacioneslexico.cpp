#include "lexico.h"
//Inicializar las transiciones con: {nuevoEstado, funcionAEjecutar}

void AnalizadorLexico::inicializarEstadoInicial(){
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DIGITO] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_LETRA] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::iniciarIdentificador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DOSPUNTOS] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_IGUAL] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MENOR] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MAYOR] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_OPERADOR] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::nuevaLinea};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinal};
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
}