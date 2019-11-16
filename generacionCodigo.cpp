#include "generacionCodigo.h"
string GeneracionCodigo::generarCodigo(Polaca *polaca){
	string resultado = "";
	for(int i = 0; i < polaca->size(); i++){
		Paso* p = polaca->get(i);
		resultado += p->generarCodigo();
	}
	return resultado;
}