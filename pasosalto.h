#include "paso.h"
#include <string>

using namespace std;

class PasoSalto : public Paso
{
private:
	int destino;
public:
	PasoSalto(){}
	void setDestino(int destino){this->destino = destino;}
	int getDestino(){return destino;}
	virtual void generarCodigo(stack<int>& pila){
        
    }
};

