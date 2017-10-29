#include "stdafx.h"

#include "Population.h"

Population::Population(int *structure, int size)
{
	this->population_size = size;
	this->individus = new Red[size];
	this->mutation_rate = 0.1; //(min 0.001)
	this->networkErrors = new double[size];
	this->fitness = new double[size];
	this->probability = new double[size];
	this->child = new Red[population_size];
	this->mapedNetErrors = new double[size];

	for (int i = 0; i < this->population_size; i++)
	{
		this->individus[i] = Red(structure);
		this->individus[i].setRandomGenes();
		this->individus[i].genes2weights();

		this->child[i] = Red(structure);
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
		//mapErrors();
		//fitness[i] = (1 - mapedNetErrors[i])*(1 - mapedNetErrors[i]);
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

int Population::get_parent() {
	double target = (double)(rand() % 10000);
	target = target/100;
	double accum_prob = 0;
	for (int i = 0; i < population_size; i++) {
		accum_prob += probability[i];
		if (accum_prob >= target) {
			return i;
		}
	}
}

void Population::new_generation() {

	int elite = getBestNetwork();
	child[0].setGenes(individus[elite].getGenes());

	for (int i = 1; i < population_size; i++) {

		int parent1 = get_parent();
		int parent2 = get_parent();
		do {
			parent1 = get_parent();
			parent2 = get_parent();
		} while (parent1 == parent2);

		child[i] = reproduce(parent1, parent2);
	}
	for (int i = 0; i < population_size; i++) {
		individus[i].setGenes(child[i].getGenes());
	}
}

Red Population::reproduce(int parent1, int parent2) {
	
	Red child(individus[parent1].structure);

	int nLayers = individus[parent1].structure[0];

	for (int i = 0; i < nLayers - 1; i++) {
		for (int j = 0; j < individus[parent1].structure[i + 1] + 1; j++) {
			for (int k = 0; k < individus[parent1].structure[i + 2]; k++) {
				float random = rand() % 100000;
				random = random / 1000;
				if (mutation_rate > random) {
					child.genes[i][j][k] = (double)(rand() % 200) / 100 - 1;
				}
				else if ((i + j + k) % 2 == 0) {
					child.genes[i][j][k] = individus[parent1].genes[i][j][k];
				}
				else
					child.genes[i][j][k] = individus[parent2].genes[i][j][k];
			}
		}
	}
	return child;
}

double Population::average_error() {
	double sum = 0;
	for (int i = 0; i < population_size; i++) {
		sum += networkErrors[i];
	}
	sum = sum / population_size;
	return sum;
}

int Population::getBestNetwork() {
	int bestNetwork = 0;

	for (int i = 0; i < population_size; i++) {
		if (networkErrors[i] < networkErrors[bestNetwork])
			bestNetwork = i;
	}
 	return bestNetwork;
}

void Population::mapErrors() {
	int best = getBestNetwork();
	double min = networkErrors[best];
	for (int i = 0; i < population_size; i++) {
		mapedNetErrors[i] = networkErrors[i] - min;
	}

	//Worst network
	int worst = 0;
	for (int i = 0; i < population_size; i++) {
		if (networkErrors[i] > networkErrors[worst])
			worst = i;
	}
	double max = 1 / mapedNetErrors[worst];
	for (int i = 0; i < population_size; i++) {
		mapedNetErrors[i] = mapedNetErrors[i]*max;
	}
}