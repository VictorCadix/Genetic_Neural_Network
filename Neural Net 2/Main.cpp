#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Red.h"
#include "Population.h"

using namespace std;

void main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));

	int structure[] = { 3,2,3,1 };
	
	//Inputs
	double** input;

	input = new double *[2];
	for (int i = 0; i < 2; i++) {
		input[i] = new double[2];
	}
	input[0][0] = 0.1;
	input[0][1] = 0.3;
	input[1][0] = 0.2;
	input[1][1] = 0.6;

	//Outputs
	double** expected_result;
	
	expected_result = new double*[2];
	for (int i = 0; i < 2; i++) {
		expected_result[i] = new double[1];
	}
	expected_result[0][0] = 0.2;
	expected_result[1][0] = 0.4;
	

	Population population(structure, 10);
	int generations = 10000;

	for (int i = 0; i < generations; i++) {
		population.evaluate(2, input, expected_result);
		cout << population.average_error() << endl;
		population.new_generation();
	}


	if (argv[1] == NULL)
	{
		getch();
	}
	
}