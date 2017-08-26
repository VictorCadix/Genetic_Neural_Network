#ifndef _RED_H 
#define _RED_H
#include "Neurona.h"
#include <vector>
#include <iostream>

using namespace std;

typedef	vector <Neurona> Layer; 

class Red{
	int nLayers;
	int nNeuronas;
	int *structure;
	double ***genes;
	
	vector <Layer> layers;

public:
	//Red();
	Red(int *structure_in);
	void inputs(double *in);
	void print();
	void forwardProp();
	double getResult();
};
#endif