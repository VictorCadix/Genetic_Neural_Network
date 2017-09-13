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
	double input[2][2] = { { 0.1,0.3 }, { 0.2, 0.6 } };

	double expected_result[2][1] = { { 0.2 }, { 0.4 } };

	Population population(structure, 10);
	population.inputs(input[0]);
	population.evaluate(expected_result[0]);
	population.inputs(input[1]);
	population.evaluate(expected_result[1]);

	if (argv[1] == NULL)
	{
		getch();
	}
	
}