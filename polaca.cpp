#include "polaca.h"
#include "pasooperador.h"
#include "pasofactor.h"

void Polaca::cargarOperador(int op){
	tira.push_back(PasoOperador(op));
}
void Polaca::cargarFactor(string factor){
	tira.push_back(PasoFactor(factor));
}