#include "paso.h"
#include <string>

#include "y.tab.h"

using namespace std;
class PasoOperador : public Paso{
private:
	int op;
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoOperador(int operador){
		op = operador;
	}
};