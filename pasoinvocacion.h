#include "paso.h"
#include <string>
#include "polaca.h"

using namespace std;
class PasoInvocacion : public Paso{
private:
	Polaca* punteroPolaca;
	string objeto;
public:
	//Usamos para cada operador el int que le asignó yacc
	PasoInvocacion(Polaca* polaca, string objeto){
		punteroPolaca = polaca;
		this->objeto = objeto;
	}
	Polaca* getPunteroPolaca(){
		return punteroPolaca;
	}
	virtual string generarCodigo(){return "";}
	virtual string toString(vector<Paso*>* tira){
		return "Invocación en " + objeto;
	}
};