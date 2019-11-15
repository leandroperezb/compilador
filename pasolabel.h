#include "paso.h"
#include <string>

using namespace std;
class PasoLabel : public Paso{
private:
	static int numLabel;
	int pos;
public:
	PasoLabel(){
		pos = numLabel++;
	}

	virtual void generarCodigo(){
        string codigo = "label"+pos;
    }

    virtual string toString(vector<Paso*>* tira){
			return "label " + to_string(pos);
		}
};