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
class PasoOperadorMultiplicacion : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorMultiplicacion(){
	}

    virtual string generarCodigo(Polaca *polaca){
        operacion op2= GeneracionCodigo::desapilar();
		operacion op1= GeneracionCodigo::desapilar();

		string regOp1; string regOp2;

		string codigo = conversiones(op1, op2);

		regOp2 = variableEnCodigo(op2);

		//Si cayó en el registro DX por conversión, quitarlo de ahí a una variable auxiliar (no hay más registros)
		if (op2.esRegistro){
			if (op2.operador[0] == 'D'){
				codigo += "MOV auxint, "+op2.operador+ "\n";
				op2.esRegistro = false; op2.operador = "auxint";
				regOp2 = op2.operador;
				GeneracionCodigo::desocuparRegistro(op2.operador);
			}
			if (op2.operador[1] == 'D'){
				codigo += "MOV auxulong, "+op2.operador+ "\n";
				op2.esRegistro = false; op2.operador = "auxulong";
				regOp2 = op2.operador;
				GeneracionCodigo::desocuparRegistro(op2.operador);
			}
		}

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

		//Luego para op2, si es una constante, moverla a la variable auxiliar (evita problemas si los registros ya están llenos)
		if (!op2.esRegistro){
			if (tds->get(op2.operador).tipoSimbolo == TablaSimbolos::CONSTANTE){
				if (tds->get(op2.operador).tipo == TablaSimbolos::TIPO_INT){
					codigo += "MOV auxint, "+variableEnCodigo(op2)+ "\n";
					op2.esRegistro = false; op2.operador = "auxint";
				}else{
					codigo += "MOV auxulong, "+variableEnCodigo(op2)+ "\n";
					op2.esRegistro = false; op2.operador = "auxulong";
				}
				regOp2 = op2.operador;
			}
		}

		if (esUlong(op1))
			codigo += "MUL "+regOp2+"\n";
		else
			codigo += "IMUL "+regOp2+"\n";

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
		if (op2.esRegistro)
			GeneracionCodigo::desocuparRegistro(op2.operador);

		return codigo;
    }
    virtual string toString(vector<Paso*>* tira){
			return "*";
		}
};