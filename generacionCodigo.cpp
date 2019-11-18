#include "generacionCodigo.h"
#include "paso.h"
#include "tablasimbolos.h"
string GeneracionCodigo::generarCodigo(Polaca *polaca){
	string include = ".386\n.model flat, stdcall\noption casemap :none\ninclude \\masm32\\include\\windows.inc\ninclude \\masm32\\include\\kernel32.inc\ninclude \\masm32\\include\\user32.inc\nincludelib \\masm32\\lib\\kernel32.lib\nincludelib \\masm32\\lib\\user32.lib\n";
	string data = include+".data\nerr1 db \"Error de conversion!\", 0\nerr2 db \"Division por 0!\", 0\n";

	unordered_map<string, TablaSimbolos::registro> tabla = Paso::tds->getCopyTabla();
	unordered_map<string , TablaSimbolos::registro>::iterator it;
	for (it = tabla.begin(); it != tabla.end(); ++it){
		if (it->second.tipoSimbolo == TablaSimbolos::VARIABLE && it->second.tipo < 0 )
			if ( it->second.tipo == TablaSimbolos::TIPO_ULONG )
				data += "_"+it->first+" DD ?\n";
			else
				data += "_"+it->first+" DW ?\n";
	}

	string resultado = data+".code\n";
	resultado += Paso::labelsError();
	for(int i = 0; i < polaca->size(); i++){
			Paso* p = polaca->get(i);
			resultado += p->generarCodigo();
	}
	resultado +="invoke ExitProcess, 0\nEND START\n";
	return resultado;
}