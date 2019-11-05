#include "paso.h"
#include <string>
#include "polaca.h"

using namespace std;
class PasoInvocacion : public Paso{
private:
	Polaca* punteroPolaca;
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoInvocacion(Polaca &polaca){
		punteroPolaca = &polaca;
	}
	Polaca* getPunteroPolaca(){
		return punteroPolaca;
	}
	virtual void generarCodigo(stack<int>& pila){}
};