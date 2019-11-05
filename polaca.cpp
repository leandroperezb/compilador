#include "polaca.h"
#include "factoryoperador.h"
#include "pasofactor.h"
#include "pasoprint.h"
#include "pasostring.h"
#include "pasoinvocacion.h"

Polaca Polaca::polacaMadre;
Polaca* Polaca::polacaEnEdicion = nullptr;
void Polaca::cargarOperador(int op){
	tira.push_back(FactoryOperador::crearPaso(op));
}
int Polaca::cargarFactor(string factor){
	tira.push_back(new PasoFactor(factor));
	return tira.size()-1;
}
void Polaca::cargarString(string str){
	tira.push_back(new PasoString(str));
}
void Polaca::cargarPrint(){
	tira.push_back(new PasoPrint());
}

void Polaca::invocacionMetodo(string objeto, Polaca* polaca){
	tira.push_back(new PasoInvocacion(polaca, objeto));
}