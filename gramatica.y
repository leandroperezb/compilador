%token ID CTE MAYORIGUAL MENORIGUAL IGUAL DISTINTO ASIGNACION STRING IF ELSE END_IF PRINT INT BEGIN END FOR CLASS EXTENDS PUBLIC PRIVATE VOID ULONG ERROR
%%
programa: bloque_declarativo bloque_sentencias
;

/* PARTE DE SENTENCIAS DECLARATIVAS */
bloque_declarativo: sentencia_declarativa | bloque_declarativo sentencia_declarativa
;
sentencia_declarativa: 
		sentencia_declarativa_simple
	|	declaracion_clase
;
sentencia_declarativa_simple:
		tipo lista_de_variables ';'
;
tipo: INT | ULONG | ID
;
lista_de_variables: ID | lista_de_variables ',' ID
;

	/* CLASES */
	declaracion_clase : encabezado BEGIN sentencias_clase END
	;
	encabezado : CLASS ID EXTENDS ID | CLASS ID
	;
	sentencias_clase : sentencias_clase sentencia_clase | sentencia_clase
	;
	sentencia_clase : modificador VOID ID '('')' bloque_sentencias
					| modificador sentencia_declarativa_simple
	;
	modificador : PUBLIC | PRIVATE
	;

/* PARTE DE SENTENCIAS EJECUTABLES */
sentencias_ejecutables: bloque_sentencias | sentencia
;
bloque_sentencias: BEGIN sentencias END
;
sentencias: sentencia | sentencias sentencia
;
sentencia: seleccion
		| identificador ASIGNACION expr ';'
		| PRINT '(' STRING ')' ';'
		| for
;

/* RELACIONADO AL IF */
seleccion: 	IF '(' condicion ')' sentencias_ejecutables END_IF
			| IF '(' condicion ')' sentencias_ejecutables ELSE sentencias_ejecutables END_IF
;
comparador:
		MAYORIGUAL
	|	'<'
	|	'>'
	|	IGUAL
	|	DISTINTO
	|	MENORIGUAL
;
condicion: expr comparador expr
;

/* EXPRESIÓN TÉRMINO FACTOR */
expr: termino
	| expr '+' termino
	| expr '-' termino
	| '-' termino {AccionesSintactico::negativizarConstante(laTabla, punteros[$2]);}
;
termino:
	factor
|	termino '*' factor
|	termino '/' factor
;
factor: CTE
	|	identificador
;

 /* soporte para variables de objetos */
 identificador: ID
			|	ID'.'identificador
;
/* BUCLE FOR */
for : FOR '(' identificador ASIGNACION expr ';' expr ';' expr ')' sentencias_ejecutables ';'
%%