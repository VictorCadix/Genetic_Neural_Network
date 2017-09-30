#include "stdafx.h"

#include "catch.hpp"

#include <iostream>
#include <vector>

/* Include files of Neural Network project */
#include "../../Neural Net 2/Neurona.h"
#include "../../Neural Net 2/Red.h"
#include "../../Neural Net 2/Population.h"

TEST_CASE("Constructeur de Population correct")
{
	int structure[] = { 3,2,3,1 };
	Population maPop = Population(structure, 10);

	SECTION("Population taille correcte")
	{
		CHECK(maPop.population_size == 10);
	}

	SECTION("Structure red correct")
	{
		for (int i = 0; i < maPop.population_size; i++)
		{
			CHECK(maPop.individus[i].structure[0] == 3);
			CHECK(maPop.individus[i].structure[1] == 2);
			CHECK(maPop.individus[i].structure[2] == 3);
			CHECK(maPop.individus[i].structure[3] == 1);
		}
	}

	SECTION("La population contient bien des Red bien formees")
	{
		for (int r = 0; r < 10; r++)
		{
			Red red = maPop.individus[r];

			for (int i = 0; i < red.nLayers - 1; i++) {
				for (int j = 0; j < red.structure[i + 1] + 1; j++) {
					for (int k = 0; k < red.structure[i + 2]; k++) {
						CHECK(red.genes[i][j][k] <= 1);
						CHECK(red.genes[i][j][k] >= -1);
					}
				}
			}
		}
	}

	SECTION("La population contient des Red differents")
	{
		for (int r = 1; r < 10; r++)
		{
			Red red = maPop.individus[r];
			Red redPrecedente = maPop.individus[r - 1];

			for (int i = 0; i < red.nLayers - 1; i++) {
				for (int j = 0; j < red.structure[i + 1] + 1; j++) {
					for (int k = 0; k < red.structure[i + 2]; k++) {
						CHECK(red.genes[i][j][k] != redPrecedente.genes[i][j][k]);
					}
				}
			}
		}
	}
}

TEST_CASE("Reglage des inputs de la population")
{
	int structure[] = { 3,2,3,1 };
	Population maPop = Population(structure, 10);
	double input[] = { 2,3 };
	maPop.inputs(input);

	SECTION("Input neurons ont les valeurs attendues")
	{
		for (int i = 0; i < maPop.population_size; i++) {
			CHECK(maPop.individus[i].layers[0][0].getValor() == 2);
			CHECK(maPop.individus[i].layers[0][1].getValor() == 3);
		}
	}

	SECTION("Bias neuron non affecte par les inputs")
	{
		for (int i = 0; i < maPop.population_size; i++) {
			CHECK(maPop.individus[i].layers[0][2].getValor() == 1);
		}
	}
}

TEST_CASE("Population evaluate donne des resultats plausibles")
{
	int structure[] = { 3,2,3,1 };
	Population maPop = Population(structure, 10);

	//Inputs
	double** input;
	input = new double *[1];
	for (int i = 0; i < 1; i++) {
		input[i] = new double[2];
	}
	input[0][0] = 0.2;
	input[0][1] = 0.3;

	//Result
	double** expected_result;

	expected_result = new double*[1];
	for (int i = 0; i < 1; i++) {
		expected_result[i] = new double[1];
	}
	expected_result[0][0] = 0.2;

	//Evaluate
	maPop.evaluate(1,input,expected_result);

	for (int i = 0; i < maPop.population_size; i++)
	{
		CHECK(maPop.individus[i].getResult() <= 1);
		CHECK(maPop.individus[i].getResult() >= 0);
	}
}

TEST_CASE("fitness") {
	
	int structure[] = { 3,10,1,2 };
	Population pop(structure, 3);
	pop.networkErrors[0] = 0.18;
	pop.networkErrors[1] = 0.66;
	pop.networkErrors[2] = 0.34;

	for (int i = 0; i < 3; i++) {
		pop.fitness[i] = (1 - pop.networkErrors[i])*(1 - pop.networkErrors[i])*(1 - pop.networkErrors[i]);
	}
	CHECK(pop.fitness[0] == Approx(0.551368));
	CHECK(pop.fitness[1] == Approx(0.039304));
	CHECK(pop.fitness[2] == Approx(0.287496));
}

TEST_CASE("probability") {

	int structure[] = { 3,2,3,1 };
	Population maPop(structure, 50);

	//Inputs
	double** input;
	input = new double *[1];
	for (int i = 0; i < 1; i++) {
		input[i] = new double[2];
	}
	input[0][0] = 0.2;
	input[0][1] = 0.6;

	//Result
	double** expected_result;

	expected_result = new double*[1];
	for (int i = 0; i < 1; i++) {
		expected_result[i] = new double[1];
	}
	expected_result[0][0] = 0.2;

	//Evaluate
	maPop.evaluate(1, input, expected_result);
	double total_probability = 0;
	for (int i = 0; i < maPop.population_size; i++) {
		total_probability += maPop.probability[i];
	}
	CHECK(total_probability == Approx(100));
}