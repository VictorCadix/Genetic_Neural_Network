#include "stdafx.h"

#include "Population.h"

Population::Population(int *structure, int size)
{
	this->population_size = size;
	this->individus = new Red[size];
	this->mutation_rate = 1;

	for (int i = 0; i < this->population_size; i++)
	{
		Red red = Red(structure);
		red.setRandomGenes();

		this->individus[i] = red;
	}
}

void Population::inputs(double *in) {
	for (int i = 0; i < population_size; i++) {
		this->individus[i].inputs(in);
	}
}

void Population::solve() {
	for (int i = 0; i < population_size; i++) {
		this->individus[i].geneForwardProp();
	}
}