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
	static Paso* crearPaso(int operador){
		 Paso* p;
		 switch (operador){
		 case '+':
			 p = new PasoOperadorSuma();
			 break;
		case '-':
			p = new PasoOperadorResta();
			break;
		case '*':
			p = new PasoOperadorMultiplicacion();
			break;
		case '/':
			p = new PasoOperadorDivision();
			break;
		case ASIGNACION:
			p = new PasoOperadorAsignacion();
		 	break;
		 default:
			p = new PasoOperadorComparador(operador);
		 }
		 return p;
	}
};