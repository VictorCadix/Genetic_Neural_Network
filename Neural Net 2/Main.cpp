#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Red.h"
#include "Population.h"

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
	int nInputs;
	int nOutputs;
	int cont = 0;

	while (!feof(training_data)) {
		char line[100];
		char token;
		fgets(line, 100, training_data);
		sscanf(line, "%c", &token);
		
		if (token == '%') {
			//Its a comment
		}
		else if (token == '#') {
			sscanf(line, "%c %d %*c %d %*c %d", &token, &total_data, &nInputs, &nOutputs);
			
			//Allocating memory for the input
			input = new double *[total_data];
			for (int i = 0; i < total_data; i++) {
				input[i] = new double[nInputs];
			}
			//Allocating memory for the output
			expected_result = new double*[total_data];
			for (int i = 0; i < total_data; i++) {
				expected_result[i] = new double[nOutputs];
			}
		}
		else {
			sscanf(line, "%lf %lf %*c %lf", &input[cont][0], &input[cont][1], &expected_result[cont][0]);
			cont++;
		}
	}
	

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

	ofstream best_network;
	best_network.open("best_network.txt");
	
	int individu = population.getBestNetwork();
	
	best_network << "% Structure:" << endl;
	best_network << "S";
	for (int i = 0; i <= structure[0]; i++) {
		best_network << " " << structure[i];
	}

	//Weights print
	best_network << endl << "% Weights of the best network" << endl;

	for (int i = 0; i < structure[0] - 1; i++) {
		best_network << "% Weight matrix " << i + 1 << endl;
		for (int j = 0; j < structure[i + 1] + 1; j++) { //[]+1 for bias
			for (int k = 0; k < structure[i + 2]; k++) {
				best_network << population.individus[individu].genes[i][j][k] << '\t';
			}
			best_network << endl;
		}
	}


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