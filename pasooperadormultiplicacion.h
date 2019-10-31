#include "paso.h"
#include <string>

#include "y.tab.h"

using namespace std;
class PasoOperadorMultiplicacion : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorMultiplicacion(){
	}

    void generarCodigo(stack<Paso>& pila){
        
    }
};