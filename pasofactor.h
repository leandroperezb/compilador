#include "paso.h"
#include <string>

using namespace std;
class PasoFactor : public Paso{
	private:
		string factor;
	public:
		PasoFactor(string factor){
			this->factor = factor;
		}
		void setFactor(string factor){
			this->factor = factor;
		}
		string getFactor(){
			return factor;
		}
		virtual void generarCodigo(stack<int> &pila){}
};