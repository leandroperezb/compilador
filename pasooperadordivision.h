#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorDivision : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorDivision(){
	}

    virtual void generarCodigo(){
        operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();
		string regOp1; string regOp2;
		string codigo = conversiones(op1, op2, true);
		if( op1.esRegistro){ // caso R+R o  R+V
			regOp1 = op1.operador;
		}else{ // Caso V+V, sabiendo que no puede darse R+R
			regOp1 = GeneracionCodigo::buscarRegistroEspecial(false);
			codigo += "MOV "+ regOp1 + " "+ variableEnCodigo(op1) + "\n";
		}
		regOp2 = variableEnCodigo(op2);
		codigo+= "DIV "+regOp1+" "+regOp2+'\n';
		if (op2.esRegistro) // Si el segundo era un registro lo tengo que desocupar
			GeneracionCodigo::desocuparRegistro(op2.operador);
		GeneracionCodigo::apilar({true, regOp1}); // Apilo el registro donde quedó el resultado
    }
    virtual string toString(vector<Paso*>* tira){
			return "/";
		}
};