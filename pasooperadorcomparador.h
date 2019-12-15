#include "paso.h"
#include <string>
#include <unordered_map>

#include "y.tab.h"

using namespace std;
class PasoOperadorComparador : public Paso{
private:
	int op;
	inline static const unordered_map<int, string> comparadores = {
		{MAYORIGUAL, ">="}, {MENORIGUAL, "<="}, {IGUAL, "=="}, {DISTINTO, "<>"}
	};
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorComparador(int operador){
		op = operador;
	}

	virtual string generarCodigo(Polaca *polaca){
		// Tomo los dos operandos
		operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();

		string regOp1; string regOp2;
		// Veo si se necesitan conversiones
		string codigo = conversiones(op1, op2);
		
		if( op1.esRegistro){ // Si ya es registro caso R+R o  R+V
			regOp1 = op1.operador; // Uso el mismo nombre
			regOp2 = variableEnCodigo(op2); // renombro la variable
		}else{ // Si no es un registro
			if(op2.esRegistro){ // Caso V+R
				regOp1 = variableEnCodigo(op1);
				regOp2 = op2.operador; // Opero entre ellos comunmente
			}
			else{ // Caso V+V
				regOp1 = GeneracionCodigo::buscarRegistro(tds->get(op1.operador).tipo == TablaSimbolos::TIPO_ULONG);
				codigo += "MOV "+ regOp1 + ", "+ variableEnCodigo(op1) + "\n";
				op1.operador = regOp1; op1.esRegistro = true;
				regOp2 = variableEnCodigo(op2);
			}
		}
		codigo+= "CMP "+regOp1+", "+regOp2+'\n';
		if (op1.esRegistro) // Si el segundo era un registro lo tengo que desocupar
			GeneracionCodigo::desocuparRegistro(op1.operador);
		if (op2.esRegistro) // Si el segundo era un registro lo tengo que desocupar
			GeneracionCodigo::desocuparRegistro(op2.operador);

		GeneracionCodigo::apilar({!(regOp1[0] == 'E'), this->toString(nullptr)}); //Apilar el comparador, para decidir luego por qué condición saltar

		return codigo;
    }
    virtual string toString(vector<Paso*>* tira){
    	if (op < 256){
    		char a = (char) op;
			return string(1, a);
		}
		auto operador = PasoOperadorComparador::comparadores.find(op);
		return operador->second;
	}
};