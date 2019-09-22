#define ID 257
#define CTE 258
#define MAYORIGUAL 259
#define MENORIGUAL 260
#define IGUAL 261
#define DISTINTO 262
#define ASIGNACION 263
#define STRING 264
#define IF 265
#define ELSE 266
#define END_IF 267
#define PRINT 268
#define INT 269
#define BEGIN 270
#define END 271
#define FOR 272
#define CLASS 273
#define PUBLIC 274
#define PRIVATE 275
#define ULONG 276
#define ERROR 277
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	const char* cadena;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
