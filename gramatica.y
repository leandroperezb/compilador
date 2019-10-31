%token ID CTE MAYORIGUAL MENORIGUAL IGUAL DISTINTO ASIGNACION STRING IF ELSE END_IF PRINT INT BEGIN END FOR CLASS EXTENDS PUBLIC PRIVATE VOID ULONG ERROR
%%
programa: bloque_declarativo bloque_sentencias
;

/* PARTE DE SENTENCIAS DECLARATIVAS */
bloque_declarativo: sentencia_declarativa | bloque_declarativo sentencia_declarativa
;
sentencia_declarativa: 
		tipo lista_de_variables ';' {AccionesSintactico::declararVariable(laTabla, $1, lista_variables); cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": declaración de variables" << endl;}
	|	declaracion_clase
	|   error ';' {cout<<"Linea "<<elLexico->contadorLineas<<": En este punto se esperaba una declaración."<<endl; abortarCompilacion = true;}
;
tipo_basico: INT {$$ = -1;}
			| ULONG {$$ = -2;}
;
tipo: tipo_basico | ID
;
lista_de_variables: ID {lista_variables.push_back(punteros[$1]);}
					| lista_de_variables ',' ID {lista_variables.push_back(punteros[$3]);}
;

	/* CLASES */
	declaracion_clase : encabezado BEGIN sentencias_clase END
	;
	encabezado : CLASS ID EXTENDS ID {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": declaración de clase" << endl;
	AccionesSintactico::cargarClase(laTabla, punteros[$2], punteros[$4]);}
				| CLASS ID {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": declaración de clase" << endl;
				AccionesSintactico::cargarClase(laTabla, punteros[$2]);}
	;
	sentencias_clase : sentencias_clase sentencia_clase | sentencia_clase
	;
	sentencia_clase : modificador VOID ID '('')' bloque_sentencias {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": declaración de método de clase" << endl;}
					| modificador tipo_basico lista_de_variables ';' {AccionesSintactico::declararVariable(laTabla, $2, lista_variables, $1); cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": declaración de variables adentro de una clase" << endl;}
	;
	modificador : PUBLIC {$$ = TablaSimbolos::PUBLI;}
	 | PRIVATE {$$ = TablaSimbolos::PRIVAT;}
	;

/* PARTE DE SENTENCIAS EJECUTABLES */
sentencias_ejecutables: bloque_sentencias | sentencia
;
bloque_sentencias: BEGIN sentencias END
;
sentencias: sentencia | sentencias sentencia
;
sentencia: seleccion
		| identificador ASIGNACION expr ';' {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": asignación" << endl; polaca.cargarFactor(punteros[$1]); polaca.cargarOperador(ASIGNACION);}
		| ID '.' ID '(' ')' ';' {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": invocación a método de clase" << endl;}
		| PRINT '(' STRING ')' ';' {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": print" << endl;}
		| PRINT '('expr')'';' {AccionesSintactico::informarError("print", "un string" ,"una expresion", elLexico);}
		| for
		| error ';' {cout<<"No se pudo reconocer la sentencia en la línea "<<elLexico->contadorLineas<<endl; abortarCompilacion = true;}
;

/* RELACIONADO AL IF */
seleccion: 	IF '(' condicion ')' cuerpo_if END_IF {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": bloque if" << endl;}
			| IF '(' condicion ')' cuerpo_if ELSE cuerpo_if END_IF {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": bloque if" << endl;}
			| IF condicion {AccionesSintactico::informarError("if","(","condición sin paréntesis", elLexico); abortarCompilacion = true;}
;

cuerpo_if: sentencias_ejecutables {}

comparador:
		MAYORIGUAL
	|	'<'
	|	'>'
	|	IGUAL
	|	DISTINTO
	|	MENORIGUAL
;
condicion: expr comparador expr {polaca.cargarOperador($2);}
	|	expr ASIGNACION expr {AccionesSintactico::informarError("condicion", "un comparador", "una asginación", elLexico); abortarCompilacion = true;}
	|	expr {AccionesSintactico::informarError("condicion", "un comparador", "una expresion", elLexico); abortarCompilacion = true;}
;

/* EXPRESIÓN TÉRMINO FACTOR */
expr: termino
	| expr '+' termino {polaca.cargarOperador('+');}
	| expr '-' termino {polaca.cargarOperador('-');}
	| '-' termino {AccionesSintactico::negativizarConstante(laTabla, punteros, $2); $$ = $2;}
;
termino:
	factor
|	termino '*' factor {polaca.cargarOperador('*');}
|	termino '/' factor {polaca.cargarOperador('/');}
;
factor: CTE {$$=polaca.cargarFactor(punteros[$1]);}
	|	identificador
;

 /* soporte para variables de objetos */
 identificador: ID {AccionesSintactico::nuevoFactor(punteros[$1]);}
			|	ID '.' ID {AccionesSintactico::nuevoFactorDeClase(punteros[$1], punteros[$3]);}
;
/* BUCLE FOR */
for : FOR '(' identificador ASIGNACION factor ';' factor ';' factor ')' sentencias_ejecutables {cout << "Estructura sintáctica detectada en línea " << elLexico->contadorLineas << ": bucle for" << endl;}
	  | FOR '(' error ')' sentencias_ejecutables {AccionesSintactico::informarError("for", "asignación; factor; factor", "una expresión inesperada", elLexico); abortarCompilacion = true;}
%%
