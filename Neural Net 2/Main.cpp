#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Red.h"
#include "Population.h"

using namespace std;

void main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));

	//Files
	ofstream training_output;
	training_output.open("training_output.txt");

	int structure[] = { 3,2,2,1 };

	//Inputs
	double** input;

	input = new double *[3];
	for (int i = 0; i < 3; i++) {
		input[i] = new double[2];
	}
	input[0][0] = 0.1;
	input[0][1] = 0.3;
	input[1][0] = 0.2;
	input[1][1] = 0.4;
	input[2][0] = 0.3;
	input[2][1] = 0.5;

	//Outputs
	double** expected_result;

	expected_result = new double*[3];
	for (int i = 0; i < 3; i++) {
		expected_result[i] = new double[1];
	}
	expected_result[0][0] = 0.2;
	expected_result[1][0] = 0.3;
	expected_result[2][0] = 0.4;


	Population population(structure, 10);

	int generations = 100;
	for (int i = 0; i < generations; i++) {
		population.evaluate(3, input, expected_result);

		training_output << population.average_error() << ",";
		training_output << population.networkErrors[population.getBestNetwork()] << endl;
		
		if (i == 0 || i == generations-1)
			population.print_results();
		if (generations>100){
			if (i % (generations / 100) == 0)
				cout << i / (generations / 100) << "% completado" << endl;
		}

		population.new_generation();
	}

	cout << endl << "The end" << endl;

	double input_test[] = { 1,3 };
	int best = population.getBestNetwork();
	population.individus[best].inputs(input_test);
	population.individus[best].geneForwardProp();
	cout << "Estimation for inputs 0.1 and 0.3 " << population.individus[best].getResult();

	training_output.close();

	if (argv[1] == NULL)
	{
		getch();
	}

}