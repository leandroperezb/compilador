#include "paso.h"
#include <string>
#include "log.h"

using namespace std;
class PasoOperadorSuma : public Paso{
public:
	
	PasoOperadorSuma(){
	}

    virtual void generarCodigo(){
		operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();

		string regOp1; string regOp2;

		string codigo = conversiones(op1, op2);
		
		if( op1.esRegistro){
			regOp1 = op1.operador;
			regOp2 = variableEnCodigo(op2);
		}else{
			if(op2.esRegistro){
				regOp1 = op2.operador;
				regOp2 = variableEnCodigo(op1);
			}
			else{
				regOp1 = GeneracionCodigo::buscarRegistro(false);
				codigo += "MOV "+ regOp1 + " "+ variableEnCodigo(op1) + "\n";
				regOp2 = variableEnCodigo(op2);
			}

		}
		
		codigo += "ADD "+regOp1 +" "+regOp2+"\n";

		if (op2.esRegistro)
			GeneracionCodigo::desocuparRegistro(op2.operador);
		GeneracionCodigo::apilar({true, regOp1}); // Apilo el registro donde quedó el resultado
    }
    virtual string toString(vector<Paso*>* tira){
			return "+";
	}
};