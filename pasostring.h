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
	virtual void generarCodigo(){
		GeneracionCodigo::apilar({false, str});
	}
	virtual string toString(vector<Paso*>* tira){
			return str;
		}
};