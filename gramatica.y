%token ID CTE MAYORIGUAL MENORIGUAL IGUAL DISTINTO ASIGNACION STRING IF ELSE END_IF PRINT INT BEGIN END FOR CLASS EXTENDS PUBLIC PRIVATE VOID ULONG ERROR
%%
programa: bloque_declarativo bloque_sentencias
;

/* PARTE DE SENTENCIAS DECLARATIVAS */
bloque_declarativo: sentencia_declarativa | bloque_declarativo sentencia_declarativa
;
sentencia_declarativa: 
		tipo lista_de_variables ';' {AccionesSintactico::declararVariable(laTabla, $1, lista_variables); Log::estructuraDetectada(elLexico->contadorLineas, "declaración de variables");}
	|	declaracion_clase
	|   error ';' {Log::errorSintactico(elLexico->contadorLineas,"En este punto se esperaba una declaración");  abortarCompilacion = true;}
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
	declaracion_clase : encabezado BEGIN sentencias_clase END {AccionesSintactico::finalizarClase();}
	;
	encabezado : CLASS ID EXTENDS ID {Log::estructuraDetectada(elLexico->contadorLineas, "declaración de clase");
	AccionesSintactico::cargarClase(laTabla, punteros[$2], punteros[$4]);}
				| CLASS ID {Log::estructuraDetectada(elLexico->contadorLineas, "declaración de clase");
				AccionesSintactico::cargarClase(laTabla, punteros[$2]);}
	;
	sentencias_clase : sentencias_clase sentencia_clase | sentencia_clase
	;
	sentencia_clase : signatura bloque_sentencias_metodo {Log::estructuraDetectada(elLexico->contadorLineas, "declaración de método de clase"); AccionesSintactico::finalizarMetodo();}
					| modificador tipo_basico lista_de_variables ';' {AccionesSintactico::declararVariable(laTabla, $2, lista_variables, $1); Log::estructuraDetectada(elLexico->contadorLineas, "declaración de variables adentro de una clase");}
	;
	signatura : modificador VOID ID '('')' {AccionesSintactico::nuevoMetodo(laTabla, punteros[$3], $1);}
	;
	modificador : PUBLIC {$$ = TablaSimbolos::PUBLI;}
	 | PRIVATE {$$ = TablaSimbolos::PRIVAT;}
	;

/* PARTE DE SENTENCIAS EJECUTABLES */
bloque_sentencias_metodo : BEGIN sentencias_metodo END
;
sentencias_metodo: sentencia_metodo | sentencias_metodo sentencia_metodo
;
sentencia_metodo: ID '(' ')' ';' {Log::estructuraDetectada(elLexico->contadorLineas, "invocación a método de la misma clase"); AccionesSintactico::llamadoAMetodo(laTabla, punteros[$1]);}
		| sentencia
;

sentencias_ejecutables: bloque_sentencias | sentencia
;
bloque_sentencias: BEGIN sentencias END
;
sentencias: sentencia | sentencias sentencia
;
sentencia: seleccion
		| identificador ASIGNACION expr ';' {Log::estructuraDetectada(elLexico->contadorLineas, "asignación"); Polaca::polacaEnEdicion->cargarFactor(punteros[$1]); Polaca::polacaEnEdicion->cargarOperador(ASIGNACION);}
		| ID '.' ID '(' ')' ';' {Log::estructuraDetectada(elLexico->contadorLineas, "invocación a método de clase"); AccionesSintactico::llamadoAMetodo(laTabla, punteros[$1], punteros[$3]);}
		| PRINT '(' STRING ')' ';' {Log::estructuraDetectada(elLexico->contadorLineas, "print"); Polaca::polacaEnEdicion->cargarString(punteros[$3]); Polaca::polacaEnEdicion->cargarPrint(); }
		| PRINT '('expr')'';' {AccionesSintactico::informarError("print", "un string" ,"una expresion", elLexico);}
		| for
		| error ';' {Log::errorSintactico(elLexico->contadorLineas, "No se pudo reconocer la sentencia"); abortarCompilacion = true;}
;

/* RELACIONADO AL IF */
seleccion: 	IF '(' condicion ')' cuerpo_if END_IF {Log::estructuraDetectada(elLexico->contadorLineas, "bloque if");}
			| IF '(' condicion ')' cuerpo_if ELSE cuerpo_if END_IF {Log::estructuraDetectada(elLexico->contadorLineas, "bloque if");}
			| IF condicion {AccionesSintactico::informarError("if","(","condición sin paréntesis", elLexico); abortarCompilacion = true;}
;

cuerpo_if: sentencias_ejecutables {}

comparador:
		MAYORIGUAL {$$ = MAYORIGUAL;}
	|	'<' {$$ = (int) '<';}
	|	'>' {$$ = (int) '>';}
	|	IGUAL {$$ = IGUAL;}
	|	DISTINTO {$$ = DISTINTO;}
	|	MENORIGUAL {$$ = MENORIGUAL;}
;
condicion: expr comparador expr {Polaca::polacaEnEdicion->cargarOperador($2);}
	|	expr ASIGNACION expr {AccionesSintactico::informarError("condicion", "un comparador", "una asginación", elLexico); abortarCompilacion = true;}
	|	expr {AccionesSintactico::informarError("condicion", "un comparador", "una expresion", elLexico); abortarCompilacion = true;}
;

/* EXPRESIÓN TÉRMINO FACTOR */
expr: termino
	| expr '+' termino {Polaca::polacaEnEdicion->cargarOperador('+');}
	| expr '-' termino {Polaca::polacaEnEdicion->cargarOperador('-');}
	| '-' termino {AccionesSintactico::negativizarConstante(laTabla, punteros, $2); $$ = $2;}
;
termino:
	factor
|	termino '*' factor {Polaca::polacaEnEdicion->cargarOperador('*');}
|	termino '/' factor {Polaca::polacaEnEdicion->cargarOperador('/');}
;
factor: CTE {$$=Polaca::polacaEnEdicion->cargarFactor(punteros[$1]);}
	|	identificador
;

 /* soporte para variables de objetos */
 identificador: ID {AccionesSintactico::nuevoFactor(laTabla,punteros[$1]);}
			|	ID '.' ID {AccionesSintactico::nuevoFactorDeClase(laTabla, punteros[$1], punteros[$3]);}
;
/* BUCLE FOR */
for : FOR '(' identificador ASIGNACION factor ';' factor ';' factor ')' sentencias_ejecutables {Log::estructuraDetectada(elLexico->contadorLineas, "bucle for");}
	  | FOR '(' error ')' sentencias_ejecutables {AccionesSintactico::informarError("for", "asignación; factor; factor", "una expresión inesperada", elLexico); abortarCompilacion = true;}
%%
