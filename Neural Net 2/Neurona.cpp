#include "stdafx.h"

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

	//Bias neuron
	if (this->neuronasCapaAnterior < 0) { // -1 for bias neuron
		this->valor = 1;
		this->pesos = NULL;
		this->neuronasCapaAnterior = 0;
		cout << "Bias created: layer " << this->posCapa << ", pos " << this->posNeurona << endl;
	}

	//Input neuron
	else if (this->posCapa == 0) {
		this->valor = 0;
		this->pesos = NULL;
		cout << "Input neuron created: layer " << this->posCapa << ", pos " << this->posNeurona << endl;
	}

	//Normal neuron
	else
	{
		this->valor = 0;
		this->pesos = new double[neuronasCapaAnterior + 1]; //+1 bias
		cout << "Neuron created: layer " << this->posCapa << ", pos " << this->posNeurona << endl;
		
		//Inicializa los pesos
		for (int p = 0; p<this->neuronasCapaAnterior + 1; p++) {  //+1 bias
			this->pesos[p] = p;
		}
	}
}

void Neurona::print(){
	cout<<"Neurona: capa "<<this->posCapa<<" pos "<<this->posNeurona<<endl;
	cout<<"Neuronas Capa anterior: "<<this->neuronasCapaAnterior<<endl;
	if (neuronasCapaAnterior > 0) {
		cout << "Pesos: ";
		for (int a = 0; a < this->neuronasCapaAnterior + 1; a++) {
			cout << this->pesos[a] << "/";
		}
		cout << endl << endl;
	}
	else
		cout << "No weights" << endl << endl;
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