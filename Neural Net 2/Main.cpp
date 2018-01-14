#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Red.h"
#include "Population.h"
#include "files.h"

using namespace std;

void main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));

	//Files
	ofstream training_output;
	training_output.open("training_output.txt");

	FILE *training_data = fopen("training_data.txt", "r");

	int structure[] = { 3,2,3,1 };
	
	//Inputs
	double** input;
	double** expected_result;
	int total_data;
	total_data = getTrainingData(training_data, input, expected_result);


	Population population(structure, 10);
	int generations = 10000;

	for (int i = 0; i < generations; i++) {
		population.evaluate(2, input, expected_result);

		training_output << population.average_error() << ",";
		training_output << population.networkErrors[population.getBestNetwork()] << endl;

		if (i == 0 || i == generations - 1)
			population.print_results();
		if (generations>100) {
			if (i % (generations / 100) == 0)
				cout << i / (generations / 100) << "% completed" << endl;
		}

		population.new_generation();
	}

	training_output.close();
	
	int best = population.getBestNetwork();
	save_Network("best_network.txt", population.individus[best], structure);

	Red* red;
	red = load_network("best_network.txt");

	for (int i = 0; i < total_data; i++) {
		delete[] input[i];
	}
	delete[] input;
	for (int i = 0; i < total_data; i++) {
		delete[] expected_result[i];
	}
	delete[] expected_result;

	if (argv[1] == NULL)
	{
		getch();
	}
	
}