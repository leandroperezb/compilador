%token ID CTE MAYORIGUAL MENORIGUAL IGUAL DISTINTO ASIGNACION STRING IF ELSE END_IF PRINT INT BEGIN END FOR CLASS EXTENDS PUBLIC PRIVATE VOID ULONG ERROR
%%
programa: bloque_declarativo bloque_sentencias
;

/* PARTE DE SENTENCIAS DECLARATIVAS */
bloque_declarativo: sentencia_declarativa | bloque_declarativo sentencia_declarativa
;
sentencia_declarativa: 
		tipo lista_de_variables ';' {AccionesSintactico::asignarTipos(laTabla, $1, listas_variables[$2]);}
	|	declaracion_clase
;
tipo_basico: INT {$$ = -1;}
			| ULONG {$$ = -2;}
;
tipo: tipo_basico | ID
;
lista_de_variables: ID {$$ = listas_variables.size(); vector<string> vec; vec.push_back(punteros[$1]); listas_variables.push_back(vec);}
					| lista_de_variables ',' ID {listas_variables[$1].push_back(punteros[$3]);}
;

	/* CLASES */
	declaracion_clase : encabezado BEGIN sentencias_clase END
	;
	encabezado : CLASS ID EXTENDS ID | CLASS ID
	;
	sentencias_clase : sentencias_clase sentencia_clase | sentencia_clase
	;
	sentencia_clase : modificador VOID ID '('')' bloque_sentencias
					| modificador tipo_basico lista_de_variables ';' {AccionesSintactico::asignarTipos(laTabla, $2, listas_variables[$3]);}
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
for : FOR '(' identificador ASIGNACION factor ';' factor ';' factor ')' sentencias_ejecutables ';'
%%