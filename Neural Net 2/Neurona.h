#ifndef _NEURONA_H 
#define _NEURONA_H

#include <iostream>

class Neurona{
	double *pesos;
	double valor;
	int neuronasCapaAnterior;
public:
	int posCapa;
	int posNeurona;


	//Neurona();
	Neurona();
	Neurona(int Capa, int Neurona, int nNeuronasCapaAnterior);
	void print();
	void actualizaPesos();
	void setValor(double val){valor=val;}
	double getValor(){return valor;}
};
#endif