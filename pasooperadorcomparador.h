#include "paso.h"
#include <string>
#include <unordered_map>

#include "y.tab.h"

using namespace std;
class PasoOperadorComparador : public Paso{
private:
	int op;
	inline static const unordered_map<int, string> comparadores = {{MAYORIGUAL, ">="}, {MENORIGUAL, "<="}, {IGUAL, "=="}, {DISTINTO, "<>"}};
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
		auto operador = PasoOperadorComparador::comparadores.find(op);
		return operador->second;
	}
};