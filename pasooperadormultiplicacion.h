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

		bool esAuxiliar = false;

		//Si cayó en el registro CX o DX por conversión, quitarlo de ahí a una variable auxiliar (hay riesgos de que EDX quede ocupado al operar)
		if (op2.esRegistro){
			if (op2.operador[0] == 'D' || op2.operador[0] == 'C'){
				GeneracionCodigo::desocuparRegistro(op2.operador);
				codigo += "MOV auxint, "+op2.operador+ "\n";
				op2.esRegistro = false; op2.operador = "auxint";
				regOp2 = op2.operador;
				esAuxiliar = true;
			}
			if (op2.operador[1] == 'D' || op2.operador[1] == 'C'){
				GeneracionCodigo::desocuparRegistro(op2.operador);
				codigo += "MOV auxulong, "+op2.operador+ "\n";
				op2.esRegistro = false; op2.operador = "auxulong";
				regOp2 = op2.operador;
				esAuxiliar = true;
			}
		}

		string registroOperadorExterno = "";

		if (GeneracionCodigo::ocupadoAX()){
			if (op1.esRegistro && (op1.operador[0] == 'A' || op1.operador[1] == 'A')){
				//AX está ocupado, pero por el operador 1, por tanto dejo op1 donde está
				regOp1 = op1.operador;
			}else{
				//AX está ocupado por un operador que no participa de momento. Se lo mueve a otro registro mientras dure esta operacion
				if (op1.esRegistro){
					if (esUlong(op1)){
						registroOperadorExterno = op1.operador;
					}else{
						registroOperadorExterno = "E"+op1.operador;
					}
					//Intercambio lo actual con EAX
					codigo += "XOR EAX, "+registroOperadorExterno+"\n";
					codigo += "XOR "+registroOperadorExterno+", EAX\n";
					codigo += "XOR EAX, "+registroOperadorExterno+"\n";
				}else{
					registroOperadorExterno = GeneracionCodigo::buscarRegistro(true);
					codigo += "MOV "+registroOperadorExterno+", EAX\n"; //Muevo todo EAX a otro lado
					TRAEROP1
				}
			}
		}else{
			//Si AX no está ocupado, muevo op1 ahí (liberando lo que tuviera previamente)
			TRAEROP1
		}

		//Luego para op2, si es una constante, moverla a la variable auxiliar (evita problemas si los registros ya están llenos)
		if (!op2.esRegistro && !esAuxiliar){
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
			//Si hubo que quitar al operador que estaba en AX de su lugar, volver a ponerlo (mediante el SWAP de los XOR)
			codigo += "XOR EAX, "+registroOperadorExterno+"\n";
			codigo += "XOR "+registroOperadorExterno+", EAX\n";
			codigo += "XOR EAX, "+registroOperadorExterno+"\n";

			if (!esUlong(op1)){
				registroOperadorExterno = string(&registroOperadorExterno[1]);
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