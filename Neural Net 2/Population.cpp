#include "stdafx.h"

#include "Population.h"

Population::Population(int *structure, int size)
{
	this->population_size = size;
	this->individus = new Red[size];
	this->mutation_rate = 1;
	this->av_error = new double[size];

	for (int i = 0; i < this->population_size; i++)
	{
		this->individus[i] = Red(structure);
		this->individus[i].setRandomGenes();
	}
}

void Population::inputs(double *in) {
	for (int i = 0; i < population_size; i++) {
		this->individus[i].inputs(in);
	}
}

void Population::evaluate(int nSamples,double** in, double** expected_result) {

	//For each sample data test
	for (int sample = 0; sample < nSamples; sample++) {

		#ifdef PRINTDEBUG 
			cout <<endl<< "   Sample " << sample << endl;
		#endif

		//setting the inputs, propagate and calculate errors
		for (int i = 0; i < population_size; i++) {
			this->individus[i].inputs(in[sample]);
			this->individus[i].geneForwardProp();
			individus[i].error.push_back(abs(individus[i].getResult() - *expected_result[sample]));

			#ifdef PRINTDEBUG 
					cout << "error indiv "<< i << " = " << individus[i].error.back() << endl;
			#endif
		}
	}

	//Average error
	for (int indiv = 0; indiv < population_size; indiv++) {
		av_error[indiv] = individus[indiv].getAverage_error();
		#ifdef PRINTDEBUG 
			cout << "average error " << av_error[indiv] << endl;
		#endif
	}

}