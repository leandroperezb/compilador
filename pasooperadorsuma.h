#include "paso.h"
#include <string>
#include "log.h"

using namespace std;
class PasoOperadorSuma : public Paso{
public:
	
	PasoOperadorSuma(){
	}

    virtual string generarCodigo(Polaca *polaca){
		operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();

		string regOp1; string regOp2;

		string codigo = conversiones(op1, op2);
		
		if( op1.esRegistro){
			//Si está el primero en un registro, sumar sobre ése
			regOp1 = op1.operador;
			regOp2 = variableEnCodigo(op2);
		}else{
			if(op2.esRegistro){
				//Si el segundo es un registro y el primer no, sumar sobre el segundo
				regOp1 = op2.operador;
				regOp2 = variableEnCodigo(op1);
			}
			else{
				//Si ningún operador está en un registro, mover uno y luego sumar ahí
				regOp1 = GeneracionCodigo::buscarRegistro(esUlong(op1));
				codigo += "MOV "+ regOp1 + ", "+ variableEnCodigo(op1) + "\n";
				regOp2 = variableEnCodigo(op2);
			}

		}
		
		codigo += "ADD "+regOp1 +", "+regOp2+"\n";

		if (op2.esRegistro)
			GeneracionCodigo::desocuparRegistro(op2.operador);
		GeneracionCodigo::apilar({true, regOp1}); // Apilo el registro donde quedó el resultado

		return codigo;
    }
    virtual string toString(vector<Paso*>* tira){
			return "+";
	}
};