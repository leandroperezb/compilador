#include "paso.h"

class PasoPrint : public Paso{
public:
	PasoPrint(){}
	virtual string generarCodigo(Polaca *polaca){
		string msj = GeneracionCodigo::desapilar().operador;

		string codigo = "invoke MessageBox, NULL, addr "+msj+", addr OUTPUT, MB_OK\n";
 
		return codigo;
	}
	virtual string toString(vector<Paso*>* tira){
			return "print";
		}
};