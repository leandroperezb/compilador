#include "paso.h"

class PasoPrint : public Paso{
public:
	virtual void generarCodigo(stack<int>& pila){}
	PasoPrint(){

	}
	virtual string toString(vector<Paso*>* tira){
			return "print";
		}
};