#include "lexico.h"
//Inicializar las transiciones con: {nuevoEstado, funcionAEjecutar}

void AnalizadorLexico::inicializarEstadoInicial(){
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_CONSTANTE, &AccionesSemanticas::iniciarIdentificador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_LETRA] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::iniciarIdentificador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DOSPUNTOS] = {ESTADO_LEYENDO_ASIGNACION, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_IGUAL] = {ESTADO_LEYENDO_IGUAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MENOR] = {ESTADO_LEYENDO_MENOR, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MAYOR] = {ESTADO_LEYENDO_MAYOR, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::entregarOperador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, nullptr}; ///MANDAR WARNING o ERROR
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::nuevaLinea};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinal};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_ESPACIO] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_COMENTARIO] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_CADENA] = {ESTADO_LEYENDO_STRING, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_GUIONBAJO] = {ESTADO_INICIAL, nullptr};
}


void AnalizadorLexico::inicializarEstadoLeyendoIdentificador(){
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_LETRA] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_MENOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_MAYOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_INVALIDO] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, &AccionesSemanticas::tokenFinalIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_ESPACIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_CADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_GUIONBAJO] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
}

void AnalizadorLexico::inicializarEstadoLeyendoConstante(){
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_CONSTANTE, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_LETRA] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_MENOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_MAYOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_INVALIDO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, &AccionesSemanticas::tokenFinalConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_ESPACIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_CADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_GUIONBAJO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
}

void AnalizadorLexico::inicializarEstadoLeyendoMayor(){
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_DIGITO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_LETRA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_MENOR] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_MAYOR] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_OPERADOR] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_INVALIDO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_ESPACIO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_CADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_GUIONBAJO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
}

void AnalizadorLexico::inicializarEstadoLeyendoMenor(){
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_DIGITO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_LETRA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, nullptr /*No se esperaba el caracter : aqui*/};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_MENOR] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_MAYOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_OPERADOR] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_INVALIDO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_ESPACIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_CADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_GUIONBAJO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
}


void AnalizadorLexico::inicializarEstadoLeyendoComentario(){
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_LETRA] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_DOSPUNTOS] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_IGUAL] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_MENOR] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_MAYOR] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_OPERADOR] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_INVALIDO] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarComentario};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, nullptr /*No se esperaba...*/};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_ESPACIO] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_COMENTARIO] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_CADENA] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_GUIONBAJO] = {ESTADO_LEYENDO_COMENTARIO, &AccionesSemanticas::agregarCaracter};
}
