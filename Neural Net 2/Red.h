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
	double avgError;
	double *result;
	vector <double> error;
	
	vector <Layer> layers;

	Red();
	Red(int *structure_in);
	void inputs(double *in);
	void print();
	void geneForwardProp();
	double *** getGenes();
	void setGenes(double***genes);
	void setRandomGenes();
	void genes2weights();
	void forwardProp();
	double getResult();
	void calculate_error(double* exp_result);
	double getAverage_error();
};
#endif