#include "stdafx.h"

#include "Population.h"

Population::Population(int *structure, int size)
{
	this->population_size = size;
	this->individus = new Red[size];
	this->mutation_rate = 1;
	this->networkErrors = new double[size];
	this->fitness = new double[size];
	this->probability = new double[size];

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
		fitness[i] = (1 - networkErrors[i])*(1 - networkErrors[i])*(1 - networkErrors[i]);
		calculate_probability();

		#ifdef PRINTDEBUG 
				cout << "average error " << networkErrors[i] << endl;
		#endif

	}
}

void Population::print_results() {
	cout << endl << " - Errors - " << endl << endl;
	for (int i = 0; i < population_size; i++) {
		cout << "Pop[" << i << "] = " << networkErrors[i] << endl;
	}
	cout << endl << " - Fitness - " << endl << endl;
	for (int i = 0; i < population_size; i++) {
		cout << "Pop[" << i << "] = " << fitness[i] << endl;
	}
	cout << endl << " - Probability - " << endl << endl;
	for (int i = 0; i < population_size; i++) {
		cout << "Pop[" << i << "] = " << probability[i] << endl;
	}
}

void Population::calculate_probability() {
	double sum = 0;
	for (int i = 0; i < this->population_size; i++) {
		sum += fitness[i];
	}
	for (int i = 0; i < this->population_size; i++) {
		probability[i] = fitness[i] / sum * 100;
	}
}