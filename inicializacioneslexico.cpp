#include "lexico.h"
//Inicializar las transiciones con: {nuevoEstado, funcionAEjecutar}

void AnalizadorLexico::inicializarMatrizDeTransiciones(){
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_CONSTANTE, &AccionesSemanticas::iniciarIdentificador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_LETRA] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::iniciarIdentificador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_DOSPUNTOS] = {ESTADO_LEYENDO_ASIGNACION, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_IGUAL] = {ESTADO_LEYENDO_IGUAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MENOR] = {ESTADO_LEYENDO_MENOR, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_MAYOR] = {ESTADO_LEYENDO_MAYOR, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::entregarOperador};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::nuevaLinea};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinal};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_ESPACIO] = {ESTADO_INICIAL, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_COMENTARIO] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_INICIOCADENA] = {ESTADO_LEYENDO_STRING, nullptr};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_GUIONBAJO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_INICIAL][CATEGORIA_FINCADENA] = {ESTADO_INICIAL, &AccionesSemanticas::warning};




	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_LETRA] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_MENOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_MAYOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_INVALIDO] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, &AccionesSemanticas::tokenFinalIdentificador}; //si llega al final del archivo con una asignacion va a representar un error
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_ESPACIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_INICIOCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_GUIONBAJO] = {ESTADO_LEYENDO_IDENTIFICADOR, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_IDENTIFICADOR][CATEGORIA_FINCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarIdentificador};



	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_CONSTANTE, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_LETRA] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_MENOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_MAYOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_INVALIDO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, &AccionesSemanticas::tokenFinalConstante}; // si llega al final del archivo con una asignacion va a representar un error o warning
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_ESPACIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_INICIOCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_GUIONBAJO] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};
	matrizTransiciones[ESTADO_LEYENDO_CONSTANTE][CATEGORIA_FINCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarConstante};



	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_DIGITO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_LETRA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_MENOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_MAYOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_INVALIDO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, &AccionesSemanticas::terminarFinalMayor}; //si llega al final del archivo con una asignacion va a representar un error
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_ESPACIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_INICIOCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_GUIONBAJO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};
	matrizTransiciones[ESTADO_LEYENDO_MAYOR][CATEGORIA_FINCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMayor};



	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_DIGITO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_LETRA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_DOSPUNTOS] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_MENOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_MAYOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_OPERADOR] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_INVALIDO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_ENDLINE] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_FIN_ARCHIVO] = {ESTADO_FINAL, &AccionesSemanticas::terminarFinalMenor}; ///si llega al final del archivo con una asignacion va a representar un error
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_ESPACIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_COMENTARIO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_INICIOCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_GUIONBAJO] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};
	matrizTransiciones[ESTADO_LEYENDO_MENOR][CATEGORIA_FINCADENA] = {ESTADO_FINAL, &AccionesSemanticas::terminarMenor};




	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_DIGITO] = {ESTADO_INICIAL,&AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_LETRA] = {ESTADO_INICIAL,&AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_DOSPUNTOS] = {ESTADO_INICIAL,&AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::entregarIgual};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_MENOR] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_MAYOR] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_OPERADOR] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, nullptr}; /// si llega al final del archivo con un == va a representar un error
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_ESPACIO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_COMENTARIO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_INICIOCADENA] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_GUIONBAJO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_IGUAL][CATEGORIA_FINCADENA] = {ESTADO_INICIAL, &AccionesSemanticas::warning};




	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_DIGITO] = {ESTADO_INICIAL,&AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_LETRA] = {ESTADO_INICIAL,&AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_DOSPUNTOS] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_IGUAL] = {ESTADO_FINAL, &AccionesSemanticas::entregarAsignacion};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_MENOR] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_MAYOR] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_OPERADOR] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_INVALIDO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinal}; ///PORQUE ?, si llega al final del archivo con una asignacion va a representar un error
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_ESPACIO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_COMENTARIO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_INICIOCADENA] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_GUIONBAJO] = {ESTADO_INICIAL, &AccionesSemanticas::warning};
	matrizTransiciones[ESTADO_LEYENDO_ASIGNACION][CATEGORIA_FINCADENA] = {ESTADO_INICIAL, &AccionesSemanticas::warning};




	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_LETRA] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_DOSPUNTOS] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_IGUAL] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_MENOR] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_MAYOR] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_OPERADOR] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_INVALIDO] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_ENDLINE] = {ESTADO_INICIAL, &AccionesSemanticas::nuevaLinea};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::tokenFinal};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_ESPACIO] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_COMENTARIO] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_INICIOCADENA] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_GUIONBAJO] = {ESTADO_LEYENDO_COMENTARIO, nullptr};
	matrizTransiciones[ESTADO_LEYENDO_COMENTARIO][CATEGORIA_FINCADENA] = {ESTADO_LEYENDO_COMENTARIO, nullptr};




	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_DIGITO] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_LETRA] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_DOSPUNTOS] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_IGUAL] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_MENOR] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_MAYOR] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_OPERADOR] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_INVALIDO] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_ENDLINE] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::nuevaLinea};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_FIN_ARCHIVO] = {ESTADO_INICIAL, &AccionesSemanticas::entregarFinalCadena};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_ESPACIO] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_COMENTARIO] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_INICIOCADENA] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_GUIONBAJO] = {ESTADO_LEYENDO_STRING, &AccionesSemanticas::agregarCaracter};
	matrizTransiciones[ESTADO_LEYENDO_STRING][CATEGORIA_FINCADENA] = {ESTADO_FINAL, &AccionesSemanticas::entregarCadena};///MANDAR WARNING de aviso por no cerrar string ?
}