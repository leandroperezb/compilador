#include "paso.h"
#include <string>

#include "y.tab.h"

using namespace std;
class PasoOperadorSuma : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorSuma(int operador){
	}

    void generarCodigo(stack<Paso>& pila){

    }
};