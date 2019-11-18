#include "generacionCodigo.h"
#include "paso.h"
string GeneracionCodigo::generarCodigo(Polaca *polaca){
	string resultado = "";
	resultado += Paso::labelsError();
	for(int i = 0; i < polaca->size(); i++){
			Paso* p = polaca->get(i);
			resultado += p->generarCodigo();
	}
	resultado +="END START\n";
	return resultado;
}