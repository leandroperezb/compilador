#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorDivision : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorDivision(){
	}

    virtual void generarCodigo(stack<int>& pila){
        
    }
};