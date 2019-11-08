#include "paso.h"
#include <string>

using namespace std;

class PasoSalto : public Paso
{
private:
	int destino;
	bool condicional;
	bool porVerdadero;
public:
	PasoSalto(bool condicional, bool b = false){this->condicional = condicional; porVerdadero = b;}
	void setDestino(int destino){this->destino = destino;}
	int getDestino(){return destino;}
	virtual void generarCodigo(stack<int>& pila){
        
    }
    virtual string toString(vector<Paso*>* tira){
    	string salida = "Salto";
    	if (condicional){
    		salida = salida + " condicional por ";
    		if (porVerdadero)
    			salida = salida + "verdadero ";
    		else
    			salida = salida + "falso ";
    	}else{
    		salida = salida + " incondicional ";
    	}
    	salida = salida + "a " + (*tira)[destino]->toString();
		return salida;
	}
};

