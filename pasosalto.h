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
};

