#include "paso.h"
#include <string>

using namespace std;
class PasoString : public Paso{
private:
	string str;
public:
	PasoString(string str){
		this->str = str;
	}
	virtual string generarCodigo(Polaca *polaca){
		GeneracionCodigo::apilar({false, "cadena"+to_string(tds->get("\""+str+"\"").valor)});
		return "";
	}
	virtual string toString(vector<Paso*>* tira){
			return str;
		}
};