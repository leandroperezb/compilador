#include "generacionCodigo.h"
void GeneracionCodigo::generarCodigo(Polaca *polaca){
	for(int i = 0; i < polaca->size(); i++){
		Paso* p = polaca->get(i);
		p->generarCodigo();
	}
}