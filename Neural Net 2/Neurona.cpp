#include "Neurona.h"

using namespace std;

Neurona::Neurona(){
	cout<<"Neurona creada (por defecto)"<<endl;
}

Neurona::Neurona(int Capa, int Neurona,int nNeuronasCapaAnterior){
	posCapa=Capa;
	posNeurona=Neurona;
	NeuronasCapaAnterior=nNeuronasCapaAnterior;
	cout<<"Neurona creada: capa "<<posCapa<<", pos "<<posNeurona<<endl;
	if (posCapa == 0)
		pesos = new double[1];
	else
		pesos =  new double [NeuronasCapaAnterior];

	//Inicializa los pesos
	for (int p=0; p<NeuronasCapaAnterior; p++){
		pesos[p] = (double)(rand() % 200)/10-10;
	}
}

void Neurona::print(){
	cout<<"Neurona: capa "<<posCapa<<" pos "<<posNeurona<<endl;
	cout<<"Neuronas Capa anterior: "<<NeuronasCapaAnterior<<endl;
	cout<<"Pesos: ";
	for (int a=0; a<NeuronasCapaAnterior; a++){
		cout<<pesos[a]<<"/";
	}
	cout<<endl;
}

void Neurona::actualizaPesos(){
	for (int a=0; a<NeuronasCapaAnterior; a++){
		pesos[a];
	}
}