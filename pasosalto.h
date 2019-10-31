#include "paso.h"
#include <string>

using namespace std;

class PasoSalto
{
private:
	int destino;
public:
	PasoSalto(){}
	void setDestino(int destino){this->destino = destino;}
	int getDestino(){return destino;}
};

