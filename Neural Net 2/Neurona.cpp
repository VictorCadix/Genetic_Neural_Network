#include "Neurona.h"

using namespace std;

Neurona::Neurona(){
	cout<<"Neurona creada (por defecto)"<<endl;
}

Neurona::Neurona(int Capa, int Neurona,int nNeuronasCapaAnterior){
	this->posCapa = Capa;
	this->posNeurona = Neurona;
	this->NeuronasCapaAnterior = nNeuronasCapaAnterior;
	cout<<"Neurona creada: capa "<<this->posCapa<<", pos "<<this->posNeurona<<endl;
	if (this->posCapa == 0)
		this->pesos = new double[1];
	else
		this->pesos =  new double [NeuronasCapaAnterior];

	//Inicializa los pesos
	for (int p=0; p<this->NeuronasCapaAnterior; p++){
		this->pesos[p] = (double)(rand() % 200)/10-10;
	}
}

void Neurona::print(){
	cout<<"Neurona: capa "<<this->posCapa<<" pos "<<this->posNeurona<<endl;
	cout<<"Neuronas Capa anterior: "<<this->NeuronasCapaAnterior<<endl;
	cout<<"Pesos: ";
	for (int a=0; a<this->NeuronasCapaAnterior; a++){
		cout<<this->pesos[a]<<"/";
	}
	cout<<endl;
}

void Neurona::actualizaPesos(){
	for (int a=0; a<this->NeuronasCapaAnterior; a++){
		this->pesos[a];
	}
}