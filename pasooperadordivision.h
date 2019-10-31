#include "paso.h"
#include <string>

#include "y.tab.h"

using namespace std;
class PasoOperadorDivision : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorDivision(){
	}

    void generarCodigo(stack<Paso>& pila){
        
    }
};