#include "Neurona.h"

using namespace std;

Neurona::Neurona(){
	cout<<"Neurona creada (por defecto)"<<endl;
	this->valor = 0;
	this->posCapa = 0;
	this->posNeurona = 0;
	this->neuronasCapaAnterior = 0;
	this->pesos = NULL;
}

Neurona::Neurona(int capa, int neurona,int nNeuronasCapaAnterior){
	this->posCapa = capa;
	this->posNeurona = neurona;
	this->neuronasCapaAnterior = nNeuronasCapaAnterior;

	if (this->neuronasCapaAnterior < 0) { // -1 for bias neuron
		this->valor = 1;
		this->neuronasCapaAnterior = 0;
		cout << "Bias create: layer " << this->posCapa << ", pos " << this->posNeurona << endl;
	}
	else
	{
		this->valor = 0;
		cout << "Neurona creada: capa " << this->posCapa << ", pos " << this->posNeurona << endl;
	}

	if (this->posCapa == 0)
		this->pesos = NULL;
	else
		this->pesos =  new double [neuronasCapaAnterior];

	//Inicializa los pesos
	for (int p=0; p<this->neuronasCapaAnterior; p++){
		this->pesos[p] = (double)(rand() % 200)/10-10;
	}
}

void Neurona::print(){
	cout<<"Neurona: capa "<<this->posCapa<<" pos "<<this->posNeurona<<endl;
	cout<<"Neuronas Capa anterior: "<<this->neuronasCapaAnterior<<endl;
	cout<<"Pesos: ";
	for (int a=0; a<this->neuronasCapaAnterior; a++){
		cout<<this->pesos[a]<<"/";
	}
	cout<<endl;
}

void Neurona::actualizaPesos(){
	for (int a=0; a<this->neuronasCapaAnterior; a++){
		this->pesos[a];
	}
}

void Neurona::activate_sigmoid()
{
	double value = this->getValor();
	double activatedValue = 1 / (1 + exp(-1 * value));
	this->setValor(activatedValue);
}

void Neurona::activate_tanh() {
	double value = this->getValor();
	double activatedValue = (1 - exp(2 * value)) /( 1 + exp(2 * value));
	this->setValor(activatedValue);
}