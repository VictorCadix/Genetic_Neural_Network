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


	if (argv[1] == NULL)
	{
		getch();
	}
	
}