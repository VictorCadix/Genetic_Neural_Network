#ifndef _NEURONA_H 
#define _NEURONA_H

#include <iostream>

class Neurona{
private:
	double valor;
public:
	double *pesos;
	int neuronasCapaAnterior;
	int posCapa;
	int posNeurona;


	//Neurona();
	Neurona();
	Neurona(int Capa, int Neurona, int nNeuronasCapaAnterior);
	void print();
	void actualizaPesos();
	void activate_sigmoid();
	void activate_tanh();
	void setValor(double val){this->valor=val;}
	double getValor(){return this->valor;}
};
#endif