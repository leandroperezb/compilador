#include "paso.h"

class PasoPrint : public Paso{
public:
	PasoPrint(){}
	virtual void generarCodigo(){
		string msj = GeneracionCodigo::desapilar().operador;

		string codigo = "invoke MessageBox, NULL, addr OUTPUT, addr "+msj+", MB_OK"
	}
	virtual string toString(vector<Paso*>* tira){
			return "print";
		}
};