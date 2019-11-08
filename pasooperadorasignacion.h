#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorAsignacion : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorAsignacion(){
	}

	virtual void generarCodigo(stack<int>& pila){
        
    }

    virtual string toString(){
			return ":=";
		}
};