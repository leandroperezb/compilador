#include "paso.h"
#include "pasooperadorsuma.h"
#include "pasooperadorresta.h"
#include "pasooperadormultiplicacion.h"
#include "pasooperadordivision.h"
#include "pasooperadorcomparador.h"
#include "pasooperadorasignacion.h"
#include <string>

#include "y.tab.h"

using namespace std;
class FactoryOperador{
public:
	//Usamos para cada operador el int que le asignó yacc
	static Paso crearPaso(int operador){
		 Paso p;
		 switch (operador){
		 case '+':
			 p = PasoOperadorSuma();
			 break;
		case '-':
			p = PasoOperadorResta();
			break;
		case '*':
			p = PasoOperadorMultiplicacion();
			break;
		case '/':
			p = PasoOperadorDivision();
			break;
		case ASIGNACION:
			p = PasoOperadorAsignacion();
		 	break;
		 default:
			p = PasoOperadorComparador(operador);
		 }
		 return p;
	}
};