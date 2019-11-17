#include "paso.h"
#include <string>

#define TRAEROP1 if (esUlong(op1)) \
				regOp1 = "EAX"; \
			else \
				regOp1 = "AX"; \
			codigo += "MOV "+regOp1+", "+variableEnCodigo(op1)+"\n"; \
			if (op1.esRegistro) \
				GeneracionCodigo::desocuparRegistro(op1.operador);

using namespace std;
class PasoOperadorDivision : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorDivision(){
	}

    virtual string generarCodigo(){
        operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();

		string regOp1; string regOp2;

		string codigo = conversiones(op1, op2);

		string registroOperadorExterno = "";

		if (GeneracionCodigo::ocupadoAX()){
			if (op1.esRegistro && (op1.operador[0] == 'A' || op1.operador[1] == 'A')){
				//AX está ocupado, pero por el operador 1, por tanto dejo op1 donde está
				regOp1 = op1.operador;
			}else{
				//AX está ocupado por un operador que no participa de momento. Se lo mueve a otro registro mientras dure esta operacion
				registroOperadorExterno = GeneracionCodigo::buscarRegistro(true);
				codigo += "MOV "+registroOperadorExterno+", EAX\n"; //Muevo todo EAX a otro lado
				TRAEROP1
			}
		}else{
			//Si AX no está ocupado, muevo op1 ahí (liberando lo que tuviera previamente)
			TRAEROP1
		}

		//Luego para op2 que no puede ser un registro, moverlo a uno (por gramática)
		string nuevoRegistro = GeneracionCodigo::buscarRegistro(esUlong(op2));
		codigo += "MOV "+nuevoRegistro+", "+variableEnCodigo(op2)+"\n";
		regOp2 = nuevoRegistro;
		op2.esRegistro = true; op2.operador = nuevoRegistro;

		//control de division por cero
		codigo+= "CMP "+regOp2+", 0\nJE "+Paso::L_ERROR_DIV_CERO+"\n";

		codigo += "MOV EDX, 0\n"; //Necesario, para que el número a dividir sólo sea EAX
		if (esUlong(op1))
			codigo += "DIV "+regOp2+"\n";
		else
			codigo += "IDIV "+regOp2+"\n";

		if (registroOperadorExterno != ""){
			//Si hubo que quitar al operador que estaba en AX de su lugar, volver a ponerlo (uso EDX como auxiliar para intercambiar)
			codigo += "MOV EDX, EAX\nMOV EAX, "+registroOperadorExterno+"\n";
			if (esUlong(op1)){
				codigo += "MOV "+registroOperadorExterno+", EDX\n";
			}else{
				registroOperadorExterno = string(&registroOperadorExterno[1]);
				codigo += "MOV "+registroOperadorExterno+", DX\n";
			}
			regOp1 = registroOperadorExterno;
		}

		GeneracionCodigo::apilar({true, regOp1});
		GeneracionCodigo::ocuparAX();
		GeneracionCodigo::desocuparRegistro(op2.operador);

		return codigo;
    }
    virtual string toString(vector<Paso*>* tira){
			return "/";
		}
};