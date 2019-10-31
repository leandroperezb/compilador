#include "paso.h"
#include <string>

#include "y.tab.h"

using namespace std;
class PasoOperadorResta : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorResta(){
	}

	void generarCodigo(stack<Paso>& pila){
        
    }
};