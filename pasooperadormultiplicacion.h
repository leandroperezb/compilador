#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorMultiplicacion : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorMultiplicacion(){
	}

    virtual string generarCodigo(){
        operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();
		string regOp1; string regOp2;
		string codigo = conversiones(op1, op2, true);
		
		if( op1.esRegistro){ //Caso R+V o R+R
			regOp1 = op1.operador;
		}else{ // Caso V+V
			//regOp1 = GeneracionCodigo::buscarRegistroEspecial(false);
			codigo += "MOV "+ regOp1 + " "+ variableEnCodigo(op1) + "\n";
		}
		regOp2 = variableEnCodigo(op2);
		codigo += "MUL "+regOp1 +" "+regOp2+"\n";
		if (op2.esRegistro)
			GeneracionCodigo::desocuparRegistro(op2.operador);
		GeneracionCodigo::apilar({true, regOp1}); // Apilo el registro donde quedó el resultado

		return codigo;
    }
    virtual string toString(vector<Paso*>* tira){
			return "*";
		}
};