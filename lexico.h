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

#define ESTADO_INICIAL 0
#define ESTADO_LEYENDO_IDENTIFICADOR 1


#define CATEGORIA_DIGITO 0
#define CATEGORIA_LETRA 1
#define CATEGORIA_DOSPUNTOS 2
#define CATEGORIA_IGUAL 3
#define CATEGORIA_MENOR 4
#define CATEGORIA_MAYOR 5
#define CATEGORIA_OPERADOR 6
#define CATEGORIA_INVALIDO 7
#define CATEGORIA_FIN_ARCHIVO 8


#define TOKEN_IDENTIFICADOR 0
#define TOKEN_FINAL -1

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
		transicion matrizTransiciones[2][9];
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