#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorAsignacion : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorAsignacion(){
	}

	virtual void generarCodigo(){
		// Recordando que el lado derecho de la asignacion estará en el tope
        operacion op2 = GeneracionCodigo::desapilar(),
			op1 = GeneracionCodigo::desapilar();
		// Aunque op1 tenga un
		string codigo = "MOV "+op1.operador+" "+op2.operador+'\n';
		if(op2.esRegistro)
			GeneracionCodigo::desocuparRegistro(op2.operador);
    }

    virtual string toString(vector<Paso*>* tira){
			return ":=";
		}
};