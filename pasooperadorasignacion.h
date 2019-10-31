#include "paso.h"
#include <string>

#include "y.tab.h"

using namespace std;
class PasoOperadorAsignacion : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorAsignacion(){
	}

	void generarCodigo(stack<Paso>& pila){
        
    }
};