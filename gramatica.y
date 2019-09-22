%union {
	const char* cadena;
}
%token ID CTE MAYORIGUAL MENORIGUAL IGUAL DISTINTO ASIGNACION STRING IF ELSE END_IF PRINT INT BEGIN END FOR CLASS PUBLIC PRIVATE ULONG ERROR
%%
programa: bloque_declarativo bloque_sentencias
;

/* PARTE DE SENTENCIAS DECLARATIVAS */
bloque_declarativo: sentencia_declarativa | bloque_declarativo sentencia_declarativa
;
sentencia_declarativa: tipo lista_de_variables ';'
;
tipo: INT | ULONG
;
lista_de_variables: ID | lista_de_variables ',' ID
;


/* PARTE DE SENTENCIAS EJECUTABLES */
bloque_sentencias: BEGIN sentencias END
;
sentencias: sentencia | sentencias sentencia
;
sentencia: bloque_sentencias | seleccion | ID ASIGNACION expr ';'
;

/* RELACIONADO AL IF */
seleccion: IF '(' condicion ')' sentencia END_IF | IF '(' condicion ')' sentencia ELSE sentencia END_IF
;
comparador: MAYORIGUAL | '<' | '>' | IGUAL | DISTINTO | MENORIGUAL
;
condicion: expr comparador expr
;


/* EXPRESIÓN TÉRMINO FACTOR */
expr: termino | expr '+' termino | expr '-' termino
;
termino: factor | termino '*' factor | termino '/' factor
;
factor: CTE | ID
;
%%