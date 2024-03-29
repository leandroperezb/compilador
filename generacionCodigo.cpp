#include "generacionCodigo.h"
#include "paso.h"
#include "tablasimbolos.h"
#include <algorithm>

std::string GeneracionCodigo::replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

string GeneracionCodigo::generarCodigo(Polaca *polaca){
	string include = ".386\n.model flat, stdcall\noption casemap :none\ninclude \\masm32\\include\\windows.inc\ninclude \\masm32\\include\\kernel32.inc\ninclude \\masm32\\include\\user32.inc\nincludelib \\masm32\\lib\\kernel32.lib\nincludelib \\masm32\\lib\\user32.lib\n";
	string data = include+".data\nerr1 db \"¡Error de conversion!\", 0\nerr2 db \"¡Division por 0!\", 0\nOUTPUT db \"Print\", 0\nauxint DW ?\nauxulong DD ?\n";

	string metodos = "";
	unordered_map<string, TablaSimbolos::registro> tabla = Paso::tds->getCopyTabla();
	unordered_map<string , TablaSimbolos::registro>::iterator it;
	for (it = tabla.begin(); it != tabla.end(); ++it){
		string simbolo = it->first;
		std::replace( simbolo.begin(), simbolo.end(), '.', '@');
		if (it->second.tipoSimbolo == TablaSimbolos::VARIABLE && it->second.tipo < 0 )
			if ( it->second.tipo == TablaSimbolos::TIPO_ULONG )
				data += "_"+simbolo+" DD ?\n";
			else
				data += "_"+simbolo+" DW ?\n";
		if (it->second.tipoSimbolo == TablaSimbolos::CADENA)
			data += "cadena"+to_string(it->second.valor) + " db \""+
		replaceAll(it->first.substr(1, it->first.length()-2), "\"", "")
		//replaceAll(replaceAll(replaceAll(it->first.substr(1, it->first.length()-2), "\\", "\\\\"), "\'", "\\\'"), "\"", "\\\"")
		+"\", 0\n";
		if (it->second.tipoSimbolo == TablaSimbolos::METODO){
			metodos += "_"+simbolo+":\n"+it->second.polaca->generarCodigo()+"RET\n";
		}
	}

	string resultado = "";
	resultado += metodos;
	resultado += Paso::labelsError();
	for(int i = 0; i < polaca->size(); i++){
			Paso* p = polaca->get(i);
			resultado += p->generarCodigo(polaca);
	}
	resultado +="invoke ExitProcess, 0\nend start\n";
	std::replace( resultado.begin(), resultado.end(), '.', '@');

	resultado = data + ".code\n" + resultado;
	return resultado;
}