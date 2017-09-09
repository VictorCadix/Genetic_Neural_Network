#include "Population.h"

Population::Population(int size, int* structure) {
	Red red (structure);

	population = new Red[size];

	double input[] = { 1,5 };
	for (int pop = 0; pop < size; pop++) {
		population[pop] = Red(structure);
	}
}