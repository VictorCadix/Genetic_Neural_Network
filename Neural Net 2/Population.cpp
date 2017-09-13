#include "stdafx.h"

#include "Population.h"

Population::Population(int *structure, int size)
{
	this->population_size = size;
	this->individus = new Red[size];
	this->mutation_rate = 1;

	for (int i = 0; i < this->population_size; i++)
	{
		this->individus[i] = Red(structure);
		this->individus[i].setRandomGenes();
	}
}

void Population::inputs(double *in) {
	for (int i = 0; i < population_size; i++) {
		this->individus[i].inputs(in);
	}
}

void Population::evaluate(double** in, double** expected_result) {

	//Calculate the number of samples (Not working!!!)
	int nSamples = 0;
	while (in[nSamples] != NULL) {
		nSamples++;
	}
	//For each sample data test
	for (int sample = 0; sample < nSamples; sample++) {

		//seting the inputs
		for (int i = 0; i < population_size; i++) {
			this->individus[i].inputs(in[sample]);
			this->individus[i].geneForwardProp();
			individus[i].error.push_back(abs(individus[i].getResult() - *expected_result[sample]));

#ifdef PRINTDEBUG 
			cout << "error = " << individus[i].error.back() << endl;
#endif
		}
	}
}