#include "polaca.h"
#include "factoryoperador.h"
#include "pasofactor.h"

Polaca Polaca::polacaMadre;
Polaca* Polaca::polacaEnEdicion = nullptr;
void Polaca::cargarOperador(int op){
	tira.push_back(FactoryOperador::crearPaso(op));
}
int Polaca::cargarFactor(string factor){
	tira.push_back(new PasoFactor(factor));
	return tira.size() -1;
}