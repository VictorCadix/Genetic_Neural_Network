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
	
	vector <Layer> Layers;

public:
	//Red();
	Red(int *formato);
	void inputs(double *in);
	void print();
};
#endif