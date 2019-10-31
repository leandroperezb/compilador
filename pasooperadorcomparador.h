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

	void generarCodigo(stack<Paso>& pila){
        
    }
};