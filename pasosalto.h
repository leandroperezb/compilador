#include "paso.h"
#include <string>

using namespace std;

class PasoSalto : public Paso
{
private:
	int destino;
	bool condicional;
	bool porVerdadero;
public:
	PasoSalto(bool condicional, bool b = false){this->condicional = condicional; porVerdadero = b;}
	void setDestino(int destino){this->destino = destino;}
	int getDestino(){return destino;}
	virtual string generarCodigo(Polaca *polaca){
		string label = polaca->get(destino)->toString(nullptr);
		string dest = "";
		for (int i = 0; i < label.length(); i++){
			if (label[i] != ' ')
				dest = dest + label[i];
		}


		if (!condicional)
			return "JMP "+dest+"\n";

		operacion comparador = GeneracionCodigo::desapilar();
		string op = comparador.operador;
		bool comparacionSignada = comparador.esRegistro; //Aprovecho el booleano para mandar el dato de si comparó ints o ulongs
		if (comparacionSignada)
			if (op == ">")
				if (porVerdadero)
					return "JG "+dest+"\n";
				else
					return "JLE "+dest+"\n";
			if (op == "<")
				if (porVerdadero)
					return "JL "+dest+"\n";
				else
					return "JGE "+dest+"\n";
			if (op == "==")
				if (porVerdadero)
					return "JE "+dest+"\n";
				else
					return "JNE "+dest+"\n";
			if (op == "<>")
				if (porVerdadero)
					return "JNE "+dest+"\n";
				else
					return "JE "+dest+"\n";
			if (op == "<=")
				if (porVerdadero)
					return "JLE "+dest+"\n";
				else
					return "JG "+dest+"\n";
			if (op == ">=")
				if (porVerdadero)
					return "JGE "+dest+"\n";
				else
					return "JL "+dest+"\n";
		else
			if (op == ">")
				if (porVerdadero)
					return "JA "+dest+"\n";
				else
					return "JBE "+dest+"\n";
			if (op == "<")
				if (porVerdadero)
					return "JB "+dest+"\n";
				else
					return "JAE "+dest+"\n";
			if (op == "==")
				if (porVerdadero)
					return "JE "+dest+"\n";
				else
					return "JNE "+dest+"\n";
			if (op == "<>")
				if (porVerdadero)
					return "JNE "+dest+"\n";
				else
					return "JE "+dest+"\n";
			if (op == "<=")
				if (porVerdadero)
					return "JBE "+dest+"\n";
				else
					return "JA "+dest+"\n";
			if (op == ">=")
				if (porVerdadero)
					return "JAE "+dest+"\n";
				else
					return "JB "+dest+"\n";
	}
	virtual string toString(vector<Paso*>* tira){
		string salida = "Salto";
		if (condicional){
			salida = salida + " condicional por ";
			if (porVerdadero)
				salida = salida + "verdadero ";
			else
				salida = salida + "falso ";
		}else{
			salida = salida + " incondicional ";
		}
		salida = salida + "a " + (*tira)[destino]->toString();
		return salida;
	}
};

