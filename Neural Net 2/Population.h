#ifndef _POPULATION_H 
#define _POPULATION_H
#include "Red.h"
#include <iostream>

using namespace std;

class Population
{
	int mutation_rate; //in %
public:
	int population_size;
	Red* individus;
	double* networkErrors;
	double* fitness;
	double* probability;

	Population(int* structure, int size);
	void inputs (double *in);
	void evaluate(int nSamples, double** in, double** expected_result);
	void print_results();
	void new_generation();

private:
	void calculate_probability();
	int get_parent();
	void reproduce(int parent1, int parent2);
};
#endif
