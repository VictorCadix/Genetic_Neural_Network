#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Red.h"

using namespace std;

void main(){
	srand (time(NULL));

	int formato[5]={3,2,2,1};
	double entradas[]={1,3};

	Red red(formato);
	red.entradas(entradas);

	red.imprime();
	getch();
}