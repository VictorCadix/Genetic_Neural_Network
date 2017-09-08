#include "stdafx.h"

#include "Population.h"

Population::Population(int *structure, int size)
{
	this->population_size = size;
	this->individus = new Red[size];

	for (int i = 0; i < this->population_size; i++)
	{
		Red red = Red(structure);
		red.setRandomGenes();
		red.genes2weights();

		this->individus[i] = red;
	}
}