#include "paso.h"
#include <string>

using namespace std;
class PasoOperadorResta : public Paso{

public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperadorResta(){
	}

	virtual void generarCodigo(){
        
    }
    virtual string toString(vector<Paso*>* tira){
			return "-";
		}
};