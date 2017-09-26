#include "stdafx.h"

#include "Population.h"

Population::Population(int *structure, int size)
{
	this->population_size = size;
	this->individus = new Red[size];
	this->mutation_rate = 1;
	this->networkErrors = new double[size];

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

void Population::evaluate(int nSamples,double** in, double** expected_result) {

	//For each individual
	for (int i = 0; i < this->population_size; i++)
	{
		
		//For each sample
		for (int s = 0; s < nSamples; s++)
		{
			this->individus[i].inputs(in[s]);
			this->individus[i].geneForwardProp();

			this->individus[i].calculate_error(expected_result[s]);
		}

		networkErrors[i] = individus[i].getAverage_error();

		#ifdef PRINTDEBUG 
				cout << "average error " << networkErrors[i] << endl;
		#endif

	}
}