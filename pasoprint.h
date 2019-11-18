#include "paso.h"

class PasoPrint : public Paso{
public:
	PasoPrint(){}
	virtual string generarCodigo(){
		string msj = GeneracionCodigo::desapilar().operador;

		string codigo = "invoke MessageBox, NULL, addr OUTPUT, addr "+msj+", MB_OK\n";
 
		return codigo;
	}
	virtual string toString(vector<Paso*>* tira){
			return "print";
		}
};