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

	int structure[] = { 3,2,3,1 };

	//Files
	ofstream training_output;
	training_output.open("training_output.txt");
	//ifstream training_data;
	//training_output.open("training_data.txt");
	
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

	int generations = 10000;
	for (int i = 0; i < generations; i++) {
		population.evaluate(3, input, expected_result);

		training_output << population.average_error() << ",";
		training_output << population.networkErrors[population.getBestNetwork()] << endl;

		population.new_generation();
	}

	training_output.close();


	if (argv[1] == NULL)
	{
		getch();
	}
	
}