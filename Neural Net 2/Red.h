#ifndef _RED_H 
#define _RED_H
#include "Neurona.h"
#include <vector>
#include <iostream>

using namespace std;

typedef	vector <Neurona> Capa; 

class Red{
	int nCapas;
	int nNeuronas;
	int *formato;
	
	vector <Capa> Capas;

public:
	//Red();
	Red(int *formato);
	void entradas(double *in);
	void imprime();
};
#endif