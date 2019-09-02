#ifndef LEXICO_H
#define LEXICO_H

#include <iostream>
#include <fstream>
#include "accionessemanticas.h"
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

#define ESTADO_FINAL 9

// CATEGORIAS
#define CATEGORIA_DIGITO 0
#define CATEGORIA_LETRA 1
#define CATEGORIA_DOSPUNTOS 2
#define CATEGORIA_IGUAL 3
#define CATEGORIA_MENOR 4
#define CATEGORIA_MAYOR 5
#define CATEGORIA_OPERADOR 6
#define CATEGORIA_ENDLINE 7
#define CATEGORIA_INVALIDO 8
#define CATEGORIA_FIN_ARCHIVO 9
#define CATEGORIA_ESPACIO 10
#define CATEGORIA_COMENTARIO 11
#define CATEGORIA_PUNTOYCOMA 12
#define CATEGORIA_COMA 13
#define CATEGORIA_PARENTESIS 14
#define CATEGORIA_CADENA 15

// TOKENS
#define TOKEN_IDENTIFICADOR 0
#define TOKEN_CONSTANTE
#define TOKEN_MENOR
#define TOKEN_MENORIGUAL
#define TOKEN_MAYOR
#define TOKEN_MAYORIGUAL
#define TOKEN_
#define TOKEN_
#define TOKEN_
#define TOKEN_
#define TOKEN_
#define TOKEN_FINAL -1


const int cantEstados = 2;
const int cantCategorias = 16;

class AnalizadorLexico{
	public:
		AnalizadorLexico(char* ruta);
		struct token{
			unsigned int id;
			string puntero;
		};
		token getToken();

		struct registroIdentificador{ //**FALTA DEFINIR LA ESTRUCTURA DE LA TABLA DE SÍMBOLOS**
			bool esPalabraReservada;
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

		//Matriz de transiciones (de dimensiones: 'Cantidad de estados' X 'Cantidad de categorias'):
		transicion matrizTransiciones[cantEstados][cantCategorias];
		void inicializarMatrizDeTransiciones();
		void inicializarEstadoInicial();
		void inicializarEstadoLeyendoIdentificador();


		string identificador; //String usado para ir formando las cadenas de identificadores o constantes

		unordered_map<string, registroIdentificador> tablaSimbolosIdentificadores;
		void agregarSiNoExiste(string key, registroIdentificador r);
		queue<token> colaDeTokens;
		void guardarToken(token nuevoToken);
		friend class AccionesSemanticas;

		sem_t semaforo;
		mutex mtx;
};

#endif