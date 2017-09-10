#ifndef _POPULATION_H 
#define _POPULATION_H
#include "Red.h"
#include <iostream>

using namespace std;

class Population
{
	public:
		int population_size;
		Red* individus;
	int mutation_rate; //in %

		Population(int* structure, int size);
};
#endif
