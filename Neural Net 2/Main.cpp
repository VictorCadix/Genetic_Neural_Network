#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Red.h"
#include "Population.h"

using namespace std;

void main(int argc, char* argv[]){
	srand ((unsigned int) time(NULL));

	int structure[]={3,2,3,1};
	double input[]={1,3};
	double expected_result[] = { 0.2 };

	Population population(structure, 10);
	population.inputs(input);
	population.solve(expected_result);

	if (argv[1] == NULL)
	{
		getch();
	}
	
}