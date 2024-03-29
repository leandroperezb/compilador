#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorResta : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorResta(){
	}

	virtual string generarCodigo(Polaca *polaca){
        operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();

		string regOp1; string regOp2;
		// Veo si se necesitan conversiones
		string codigo = conversiones(op1, op2);

		if( op1.esRegistro){ // Si ya es registro caso R+R o  R+V
			regOp1 = op1.operador; // Uso el mismo nombre
			regOp2 = variableEnCodigo(op2); // renombro la variable
		}else{ // Si no es un registro
			// Busco un registro para el primero, ya que no es una op conmutativa.
			regOp1 = GeneracionCodigo::buscarRegistro(esUlong(op1));
			codigo += "MOV "+ regOp1 + ", "+ variableEnCodigo(op1) + "\n";
			regOp2 = variableEnCodigo(op2);
		}
		codigo+= "SUB "+regOp1+", "+regOp2+'\n';
		if (op2.esRegistro) // Si el segundo era un registro lo tengo que desocupar
			GeneracionCodigo::desocuparRegistro(op2.operador);
		GeneracionCodigo::apilar({true, regOp1}); // Apilo el registro donde quedó el resultado

		return codigo;
    }
    virtual string toString(vector<Paso*>* tira){
			return "-";
		}
};