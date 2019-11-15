#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorMultiplicacion : public Paso{
    
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorMultiplicacion(){
	}

    virtual void generarCodigo(){
        
    }
    virtual string toString(vector<Paso*>* tira){
			return "*";
		}
};