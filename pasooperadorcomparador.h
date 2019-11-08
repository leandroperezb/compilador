#include "paso.h"
#include <string>

#include "y.tab.h"

using namespace std;
class PasoOperadorComparador : public Paso{
private:
	int op;
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorComparador(int operador){
		op = operador;
	}

	virtual void generarCodigo(stack<int>& pila){
        
    }
    virtual string toString(vector<Paso*>* tira){
    	if (op < 256){
    		char a[] = {(char) op};
			return string(a);
		}
		return "Operador nro: " + to_string(op);
	}
};