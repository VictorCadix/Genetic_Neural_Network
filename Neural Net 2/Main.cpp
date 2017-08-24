#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Red.h"

using namespace std;

void main(){
	srand (time(NULL));

	int structure[]={3,2,3,1};
	double input[]={1,3};

	Red red(structure);
	red.inputs(input);

	red.print();
	getch();
}