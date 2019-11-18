#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorAsignacion : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorAsignacion(){
	}

	virtual string generarCodigo(Polaca *polaca){
		// Recordando que el lado derecho de la asignacion estará en el tope
        operacion op2 = GeneracionCodigo::desapilar();
		operacion op1 = GeneracionCodigo::desapilar();


		if (tds->get(op1.operador).tipo == TablaSimbolos::TIPO_INT && 
		(op2.esRegistro && op2.operador[0] == 'E' || !op2.esRegistro && tds->get(op2.operador).tipo == TablaSimbolos::TIPO_ULONG)){
			//Si el tipo de la derecha es más abarcativo que el de la izquierda, no se puede convertir. Se aborta
			cout << "Incompatibilidad de tipos en asignación" << endl; //Hay que llevarlo a un Log
			exit(1);
		}

		string codigo = conversiones(op1, op2); //Con la verificación anterior, se sabe que sólo se puede llegar a convertir op2

		if (!op2.esRegistro && tds->get(op2.operador).tipoSimbolo != TablaSimbolos::CONSTANTE){
			//Si es una variable, moverla a un registro para operar
			string registro = GeneracionCodigo::buscarRegistro(tds->get(op2.operador).tipo == TablaSimbolos::TIPO_ULONG);
			codigo += "MOV "+registro+", "+variableEnCodigo(op2)+"\n";
			op2.esRegistro = true; op2.operador = registro;
		}

		codigo += "MOV _"+op1.operador+", "+variableEnCodigo(op2)+'\n';
		
		if (op2.esRegistro)
			GeneracionCodigo::desocuparRegistro(op2.operador);

		return codigo;
    }

    virtual string toString(vector<Paso*>* tira){
			return ":=";
		}
};