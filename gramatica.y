%union {
	const char* cadena;
}
%token ID CTE MAYORIGUAL MENORIGUAL IGUAL DISTINTO ASIGNACION STRING IF ELSE END_IF PRINT INT BEGIN END FOR CLASS PUBLIC PRIVATE ULONG ERROR
%%
programa:expr
;
expr: factor | expr '+' termino | expr '-' termino
;
termino: factor | termino '*' factor | termino '/' factor
;
factor: CTE | ID
;
%%