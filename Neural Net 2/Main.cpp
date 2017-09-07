#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Red.h"

using namespace std;

void main(int argc, char* argv[]){
	srand ((unsigned int) time(NULL));

	bool print = true;
	bool stop = true;
	
	if(argc == 2)
	{
		if (argv[1][0] == 'p')
		{
			print = false;
		}
		if (argv[1][0] == 's')
		{
			stop = false;
		}
	}

	if (argc == 3)
	{
		if (argv[1][0] == 'p' || argv[2][0] == 'p')
		{
			print = false;
		}
		if (argv[1][0] == 's' || argv[2][0] == 's')
		{
			stop = false;
		}
	}

	//Remember 'p' as performance, as it disables print statements
	if ((argc > 1 && argv[1][0] == 'p') || (argc > 2 && (argv[1][0] == 'p' || argv[2][0] == 'p')))
	{
		bool print = false;
		cout << "false" << endl;
	}
	else 
	{
		bool print = true;
		cout << "true" << endl;
	}

	int structure[]={3,2,3,1};
	double input[]={1,3};

	Red red(structure);
	red.setRandomGenes();
	red.genes2weights();
	red.inputs(input);
	red.print();
	
	red.geneForwardProp();
	red.forwardProp();

	if (stop)
	{
		getch();
	}
	
}