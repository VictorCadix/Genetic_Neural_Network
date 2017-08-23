#include "Red.h"

using namespace std;

Red::Red(int *formato_in){
	formato=formato_in;
	nCapas=formato[0];
	cout<<"Red con "<<nCapas<<" capas"<<endl;
	
	/*for (int c=0; c<nCapas; c++){
		for (int n=0; n<formato[c+1]; n++){
			neuronas = new Neurona(c,n);
		}
	}*/

	for (int c=0; c<nCapas; c++){
		Capas.push_back(Capa());
		for (int n=0; n<formato[c+1]; n++){
			if (c!=0)
				Capas.back().push_back(Neurona(c,n,formato[c]));
			else 
				Capas.back().push_back(Neurona(c,n,0));
		}
	}


}

void Red::entradas(double *in){
	cout<<endl;
	for( int e=0; e<formato[1]; e++){
		Capas[0][e].setValor(in[e]);
		cout<<"Entrada "<<e<<"="<<Capas[0][e].getValor()<<endl;
	}
	cout<<endl;
}

void Red::imprime(){
	for (int c=0; c<nCapas; c++){
		for (int n=0; n<formato[c+1]; n++){
			Capas[c][n].print();
			//cout<<"Neurona en : capa "<<Capas[c][n].posCapa<<", pos "<<Capas[c][n].posNeurona<<endl;
		}
	}
}