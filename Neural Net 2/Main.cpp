#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Red.h"

using namespace std;

void main(int argc, char* argv[]){
	srand ((unsigned int) time(NULL));

	int structure[]={3,2,3,1};
	double input[]={1,3};

	Red red(structure);
	red.setRandomGenes();
	red.inputs(input);
	red.print();
	
	red.geneForwardProp();
	red.forwardProp();

	if (argv[1] == NULL)
	{
		getch();
	}
	
}