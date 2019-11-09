#include "polaca.h"
#include "factoryoperador.h"
#include "pasofactor.h"
#include "pasoprint.h"
#include "pasostring.h"
#include "pasoinvocacion.h"
#include "pasosalto.h"
#include "pasolabel.h"

Polaca Polaca::polacaMadre;
Polaca* Polaca::polacaEnEdicion = nullptr;
int PasoLabel::numLabel = 0;
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

void Polaca::terminoCondicion(int comparador){
	this->cargarOperador(comparador);
	tira.push_back(new PasoSalto(true, false));
	pila.push(tira.size() - 1);
}

void Polaca::terminoRamaIf(){
	int indice = pila.top(); pila.pop();
	((PasoSalto*) tira[indice])->setDestino(tira.size()+1);

	tira.push_back(new PasoSalto(false));
	pila.push(tira.size() - 1);

	tira.push_back(new PasoLabel());
}


void Polaca::terminoIf(){
	int indice = pila.top(); pila.pop();
	((PasoSalto*) tira[indice])->setDestino(tira.size());
	tira.push_back(new PasoLabel());
}

void Polaca::removeLastPaso(){
	tira.pop_back();
}

void Polaca::empiezaFor(string variable){
	cargarOperador(ASIGNACION);

	tira.push_back(new PasoLabel()); //Pongo label para inicio del for y lo apilo
	pila.push(tira.size() - 1);

	cargarFactor(variable);
}

void Polaca::comparacionFor(){
	cargarOperador(IGUAL);
	tira.push_back(new PasoSalto(true, true));
	pila.push(tira.size() - 1);
}

void Polaca::terminoFor(string variable, string step){
	cargarFactor(variable); cargarFactor(variable);
	cargarFactor(step);
	cargarOperador('+');
	cargarOperador(ASIGNACION);

	int indice = pila.top(); pila.pop(); //Desapilo salto condicional
	((PasoSalto*) tira[indice])->setDestino(tira.size()+1); //Destino al label siguiente

	PasoSalto* nuevoSalto = new PasoSalto(false); //Nuevo salto incondicional al principio del for
	nuevoSalto->setDestino(pila.top()); pila.pop(); //Desapilo label inicial y seteo destino a él
	tira.push_back(nuevoSalto);

	tira.push_back(new PasoLabel());
}


void Polaca::guardar(string nombreArchivo){
	ofstream ofs;
	ofs.open (nombreArchivo + ".txt", std::ofstream::out);
	if(ofs.fail()){
		return;
	}

	for (int i = 0; i < tira.size(); i++){
		ofs << tira[i]->toString(&tira) << "\n";
	}
}

Paso* Polaca::getLastPaso(){
	return tira[tira.size()-1];
}