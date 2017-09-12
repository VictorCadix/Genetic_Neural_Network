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

void Population::solve(double *expected_result) {
	for (int i = 0; i < population_size; i++) {
		this->individus[i].geneForwardProp();
		individus[i].error.push_back(individus[i].getResult() - *expected_result);
#ifdef PRINTDEBUG 
		cout << "error = " << individus[i].error.back() << endl;
#endif
	}
}