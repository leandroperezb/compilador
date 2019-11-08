#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorSuma : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorSuma(){
	}

    virtual void generarCodigo(stack<int>& pila){

    }
    virtual string toString(vector<Paso*>* tira){
			return "+";
		}
};