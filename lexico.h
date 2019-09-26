#ifndef LEXICO_H
#define LEXICO_H

#include <iostream>
#include <fstream>
#include "accionessemanticas.h"
#include "tablasimbolos.h"
#include <queue>
#include <unordered_map>
#include <mutex>
#include <semaphore.h>


using namespace std;

// ESTADOS
#define ESTADO_INICIAL 0

#define ESTADO_LEYENDO_IDENTIFICADOR 1
#define ESTADO_LEYENDO_CONSTANTE 2
#define ESTADO_LEYENDO_MAYOR 3
#define ESTADO_LEYENDO_MENOR 4
#define ESTADO_LEYENDO_IGUAL 5
#define ESTADO_LEYENDO_ASIGNACION 6
#define ESTADO_LEYENDO_COMENTARIO 7
#define ESTADO_LEYENDO_STRING 8
// Al finalizar volvemos al principio
#define ESTADO_FINAL 0

// CATEGORIAS
#define CATEGORIA_DIGITO 0
#define CATEGORIA_LETRA 1
#define CATEGORIA_DOSPUNTOS 2
#define CATEGORIA_IGUAL 3
#define CATEGORIA_MENOR 4
#define CATEGORIA_MAYOR 5
//Acá van los parentesis, coma y punto y coma tambien.
#define CATEGORIA_OPERADOR 6
#define CATEGORIA_ENDLINE 7
#define CATEGORIA_INVALIDO 8
#define CATEGORIA_FIN_ARCHIVO 9
#define CATEGORIA_ESPACIO 10
#define CATEGORIA_COMENTARIO 11
#define CATEGORIA_INICIOCADENA 12
#define CATEGORIA_GUIONBAJO 13
#define CATEGORIA_FINCADENA 14

// TOKENS
#include "y.tab.h"
#define FINAL -1


const int cantEstados = 9;
const int cantCategorias = 15;

class AnalizadorLexico{
	public:
		AnalizadorLexico(char* ruta, TablaSimbolos* tabla);
		struct token{
			int id;
			string puntero;
		};
		token getToken();

		struct registroToken{
			AnalizadorLexico::token token;
			string warning;
		};

		void analizarCodigo();
		void retrocederLectura();

	private:
		char* rutaCodigoFuente;
		unsigned int contadorLineas;
		int estadoActual;
		ifstream infile;
		struct transicion{
			int nuevoEstado;
			void (*accionSemantica)(AnalizadorLexico*, char&);
		};
		int categorizarCaracter(char& c);

		//Mensajes de accionessemanticas
		string wrnng = "";

		//Matriz de transiciones (de dimensiones: 'Cantidad de estados' X 'Cantidad de categorias'):
		transicion matrizTransiciones[cantEstados][cantCategorias];
		void inicializarMatrizDeTransiciones();

		string identificador; //String usado para ir formando las cadenas de identificadores o constantes

		TablaSimbolos* tablaSimbolos;
		void agregarEnTabla(string key, TablaSimbolos::registro r);

		queue<registroToken> colaDeTokens;
		void guardarToken(registroToken nuevoToken);
		friend class AccionesSemanticas;

		unordered_map<string, int> palabrasReservadas;

		sem_t semaforo;
		mutex mtx;
};

#endif