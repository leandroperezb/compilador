#include "paso.h"
#include <string>
#include "polaca.h"
#include "accionessintactico.h"

using namespace std;
class PasoInvocacion : public Paso{
private:
	Polaca* punteroPolaca;
	string objeto;
	string metodo;
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoInvocacion(Polaca* polaca, string objeto, string metodo){
		punteroPolaca = polaca;
		this->objeto = objeto;
		this->metodo = metodo;
	}
	Polaca* getPunteroPolaca(){
		return punteroPolaca;
	}
	virtual string generarCodigo(Polaca *polaca){
		string codigo = "";

		//Mover todas las variables del objeto a las variables de clase:
		vector<string>* variables = &AccionesSintactico::variablesDeClase[tds->get(metodo).clasePadre];
		for (int i = 0; i < variables->size(); i++){
			string regAux = GeneracionCodigo::buscarRegistro(tds->get((*variables)[i]).tipo == TablaSimbolos::TIPO_ULONG);
			codigo += "MOV "+regAux+", _"+objeto+"@"+(*variables)[i]+"\n";
			codigo += "MOV _"+(*variables)[i]+", "+regAux+"\n";
			GeneracionCodigo::desocuparRegistro(regAux);
		}

		codigo += "CALL _"+metodo+"\n";

		//Mover las variables de clase a las variables del objeto:
		for (int i = 0; i < variables->size(); i++){
			string regAux = GeneracionCodigo::buscarRegistro(tds->get((*variables)[i]).tipo == TablaSimbolos::TIPO_ULONG);
			codigo += "MOV "+regAux+", _"+(*variables)[i]+"\n";
			codigo += "MOV _"+objeto+"@"+(*variables)[i]+", "+regAux+"\n";
			GeneracionCodigo::desocuparRegistro(regAux);
		}
		return codigo;
	}
	virtual string toString(vector<Paso*>* tira){
		return "Invocación de " + metodo + "() en " + objeto;
	}
};