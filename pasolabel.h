#include "paso.h"
#include <string>

using namespace std;
class PasoLabel : public Paso{
private:
	int pos;
public:
	PasoLabel(int posicion){
		pos = posicion;
	}

	void generarCodigo(stack<Paso>& pila){
        
    }
};