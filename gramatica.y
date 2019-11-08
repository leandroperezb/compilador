%token ID CTE MAYORIGUAL MENORIGUAL IGUAL DISTINTO ASIGNACION STRING IF ELSE END_IF PRINT INT BEGIN END FOR CLASS EXTENDS PUBLIC PRIVATE VOID ULONG ERROR
%%
programa: bloque_declarativo bloque_sentencias
;

/* PARTE DE SENTENCIAS DECLARATIVAS */
bloque_declarativo: sentencia_declarativa | bloque_declarativo sentencia_declarativa
;
sentencia_declarativa: 
		tipo lista_de_variables ';' {AccionesSintactico::declararVariable(laTabla, $1, lista_variables); Log::estructuraDetectada("declaración de variables");}
	|	declaracion_clase
	|   error ';' {Log::errorSintactico("En este punto se esperaba una declaración");}
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
	encabezado : CLASS ID EXTENDS ID {Log::estructuraDetectada("declaración de clase");
	AccionesSintactico::cargarClase(laTabla, punteros[$2], punteros[$4]);}
				| CLASS ID {Log::estructuraDetectada("declaración de clase");
				AccionesSintactico::cargarClase(laTabla, punteros[$2]);}
	;
	sentencias_clase : sentencias_clase sentencia_clase | sentencia_clase
	;
	sentencia_clase : signatura bloque_sentencias_metodo {Log::estructuraDetectada("declaración de método de clase"); AccionesSintactico::finalizarMetodo();}
					| modificador tipo_basico lista_de_variables ';' {AccionesSintactico::declararVariable(laTabla, $2, lista_variables, $1); Log::estructuraDetectada("declaración de variables adentro de una clase");}
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
sentencia_metodo: ID '(' ')' ';' {Log::estructuraDetectada("invocación a método de la misma clase"); AccionesSintactico::llamadoAMetodo(laTabla, punteros[$1]);}
		| sentencia
;

sentencias_ejecutables: bloque_sentencias | sentencia
;
bloque_sentencias: BEGIN sentencias END
;
sentencias: sentencia | sentencias sentencia
;
sentencia: seleccion
		| identificador ASIGNACION expr ';' {Log::estructuraDetectada("asignación"); Polaca::polacaEnEdicion->cargarOperador(ASIGNACION);}
		| ID '.' ID '(' ')' ';' {Log::estructuraDetectada("invocación a método de clase"); AccionesSintactico::llamadoAMetodo(laTabla, punteros[$1], punteros[$3]);}
		| PRINT '(' STRING ')' ';' {Log::estructuraDetectada("print"); Polaca::polacaEnEdicion->cargarString(punteros[$3]); Polaca::polacaEnEdicion->cargarPrint(); }
		| PRINT '('expr')'';' {Log::informarError("print", "un string" ,"una expresion");}
		| for
		| error ';' {Log::errorSintactico("No se pudo reconocer la sentencia"); }
;

/* RELACIONADO AL IF */
seleccion: 	IF '(' condicion ')' cuerpo_if END_IF {Log::estructuraDetectada("bloque if"); Polaca::polacaEnEdicion->terminoIf();}
			| IF '(' condicion ')' cuerpo_if ELSE cuerpo_if END_IF {Log::estructuraDetectada("bloque if"); Polaca::polacaEnEdicion->terminoIf();}
			| IF condicion {Log::informarError("if","(","condición sin paréntesis");}
;

cuerpo_if: sentencias_ejecutables {Polaca::polacaEnEdicion->terminoRamaIf();}

comparador:
		MAYORIGUAL {$$ = MAYORIGUAL;}
	|	'<' {$$ = (int) '<';}
	|	'>' {$$ = (int) '>';}
	|	IGUAL {$$ = IGUAL;}
	|	DISTINTO {$$ = DISTINTO;}
	|	MENORIGUAL {$$ = MENORIGUAL;}
;
condicion: expr comparador expr {Polaca::polacaEnEdicion->terminoCondicion($2);}
	|	expr ASIGNACION expr {Log::informarError("condicion", "un comparador", "una asginación");}
	|	expr {Log::informarError("condicion", "un comparador", "una expresion");}
;

/* EXPRESIÓN TÉRMINO FACTOR */
expr: termino
	| expr '+' termino {Polaca::polacaEnEdicion->cargarOperador('+');}
	| expr '-' termino {Polaca::polacaEnEdicion->cargarOperador('-');}
	| '-' termino {AccionesSintactico::negativizarConstante(laTabla, punteros, $2); $$ = $2;}
;
termino:
	factor
|	termino '*' factor {Polaca::polacaEnEdicion->cargarOperador('*');$$=-1;}
|	termino '/' factor {Polaca::polacaEnEdicion->cargarOperador('/');$$=-1;}
;
factor: CTE {$$=Polaca::polacaEnEdicion->cargarFactor(punteros[$1]);}
	|	identificador {$$=-1;}
;

 /* soporte para variables de objetos */
 identificador: ID {AccionesSintactico::nuevoFactor(laTabla,punteros[$1]);}
			|	ID '.' ID {AccionesSintactico::nuevoFactorDeClase(laTabla, punteros[$1], punteros[$3]);}
;
/* BUCLE FOR */
for : FOR '(' identificador ASIGNACION factor ';' factor ';' factor ')' sentencias_ejecutables {Log::estructuraDetectada("bucle for");}
	  | FOR '(' error ')' sentencias_ejecutables {Log::informarError("for", "asignación; factor; factor", "una expresión inesperada");}
%%
