#ifndef _RED_H 
#define _RED_H
#include "Neurona.h"
#include <vector>
#include <iostream>

using namespace std;

typedef	vector <Neurona> Layer; 

class Red{
public:
	int nLayers;
	int nNeuronas;
	int *structure;
	double ***genes;
	
	vector <Layer> layers;

	//Red();
	Red(int *structure_in);
	void inputs(double *in);
	void print();
	void geneForwardProp();
	double *** getGenes();
	void setGenes(double***genes);
	void setRandomGenes();
	void forwardProp();
	double getResult();
};
#endif