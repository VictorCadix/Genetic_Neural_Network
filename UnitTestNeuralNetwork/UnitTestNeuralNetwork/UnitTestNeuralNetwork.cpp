#include "stdafx.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iostream>
#include <vector>

/* Include files of Neural Network project */
#include "../../Neural Net 2/Neurona.h"
#include "../../Neural Net 2/Red.h"
#include "../../Neural Net 2/Population.h"

TEST_CASE("Creation d'un objet Neurona")
{
	SECTION("Neurone simple")
	{
		Neurona neuroneTest = Neurona(1, 1, 1);

		CHECK(neuroneTest.getValor() == 0);
		CHECK(neuroneTest.posNeurona == 1);
		CHECK(neuroneTest.posCapa == 1);
		CHECK(neuroneTest.neuronasCapaAnterior == 1);

		for (int p = 0; p < neuroneTest.neuronasCapaAnterior; p++) {
			CHECK(neuroneTest.pesos[p] <= 10);
			CHECK(neuroneTest.pesos[p] >= -10);
		}
	}

	SECTION("Neurone plus complexe")
	{
		Neurona neuroneTest = Neurona(3, 3, 3);

		CHECK(neuroneTest.getValor() == 0);
		CHECK(neuroneTest.posNeurona == 3);
		CHECK(neuroneTest.posCapa == 3);
		CHECK(neuroneTest.neuronasCapaAnterior == 3);

		for (int p = 0; p < neuroneTest.neuronasCapaAnterior; p++) {
			CHECK(neuroneTest.pesos[p] <= 10);
			CHECK(neuroneTest.pesos[p] >= -10);
		}
	}

	SECTION("Test creation neurone par defaut")
	{
		Neurona neuroneTest = Neurona();
		
		CHECK(neuroneTest.getValor() == 0);
		CHECK(neuroneTest.posNeurona == 0);
		CHECK(neuroneTest.posCapa == 0);
		CHECK(neuroneTest.neuronasCapaAnterior == 0);
		CHECK(neuroneTest.pesos == NULL);
	}

	SECTION("Creation bias neuron")
	{		
		Neurona testNeuron = Neurona(2, 2, -1);
		
		CHECK(testNeuron.getValor() == 1);
		CHECK(testNeuron.posNeurona == 2);
		CHECK(testNeuron.posCapa == 2);
		CHECK(testNeuron.neuronasCapaAnterior == 0);
		for (int p = 0; p < testNeuron.neuronasCapaAnterior; p++) {
			CHECK(testNeuron.pesos[p] <= 10);
			CHECK(testNeuron.pesos[p] >= -10);
		}
	}

	SECTION("Creation input neuron")
	{		
		Neurona testNeuron = Neurona(0, 2, 0);
		
		CHECK(testNeuron.getValor() == 0);
		CHECK(testNeuron.posNeurona == 2);
		CHECK(testNeuron.posCapa == 0);
		CHECK(testNeuron.neuronasCapaAnterior == 0);
		CHECK(testNeuron.pesos == NULL);
	}
}

TEST_CASE("Fonction d'activation")
{
	SECTION("Fonction sigmoid")
	{
		Neurona test = Neurona(1, 1, 1);
		
		test.setValor(3);
		test.activate_sigmoid();
		CHECK(test.getValor() == Approx(0.95257));
	}
	
	SECTION("Fonction tanh")
	{		
		Neurona test = Neurona(1, 1, 1);
		
		test.setValor(3);
		test.activate_tanh();
		CHECK(test.getValor() == Approx(-0.99505));
	}
}

TEST_CASE("Constructeur par defaut de Red")
{
	Red red = Red();

	CHECK(red.nLayers == 0);
	CHECK(red.nNeuronas == 0);
	CHECK(red.structure == NULL);
	CHECK(red.genes == NULL);
}

TEST_CASE("Constructeur de Red")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
		
	SECTION("Attribut structure correct")
	{
		CHECK(structure[0] == 3);
		CHECK(structure[1] == 2);
		CHECK(structure[2] == 3);
		CHECK(structure[3] == 1);
	}

	SECTION("Attrbut nombre de couches")
	{
		CHECK(red.nLayers == 3);
	}

	SECTION("Nombre de couches crees")
	{
		CHECK(red.layers.size() == 3);
	}

	SECTION("Nombre de neurones dans chaque couche")
	{
		//One more neuron (the bias) on all layers but the last one
		CHECK(red.layers[0].size() == 3);
		CHECK(red.layers[1].size() == 4);
		CHECK(red.layers[2].size() == 1);
	}

	SECTION("Premiere couche d'input neurons")
	{
		Layer couche = red.layers[0];
		for (int i = 0; i < couche.size(); i++)
		{
			CHECK(couche[i].neuronasCapaAnterior == 0);
			CHECK(couche[i].posNeurona == i);
			CHECK(couche[i].posCapa == 0);
			CHECK(couche[i].pesos == NULL);
		}
	}

	SECTION("Bias neurons correctement crees")
	{
		for (int i = 0; i < red.nLayers - 1; i++)
		{
			Layer couche = red.layers[i];
			Neurona neuron = couche[couche.size()-1];
			CHECK(neuron.getValor() == 1);
			CHECK(neuron.posCapa == i);
			CHECK(neuron.neuronasCapaAnterior == 0);
			CHECK(neuron.pesos == NULL);
		}
	}

	SECTION("Poids correctement initialises")
	{
		for (int i = 0; i < structure[2]+1; i++) {
			for (int k = 0; k < red.layers[1][i].neuronasCapaAnterior; k++ ){
				CHECK (red.layers[1][i].pesos[k] == k);
			}
		}
	}

	SECTION("Attribut genes initialises")
	{
		for (int i = 0; i < red.nLayers - 1; i++) {
			for (int j = 0; j < red.structure[i + 1] + 1; j++) {
				for (int k = 0; k < red.structure[i + 2]; k++) {
					CHECK(red.genes[i][j][k] == i + j + k);
				}
			}
		}
	}
}

TEST_CASE("Reglage des inputs du reseau")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	double input[] = { 2,3 };
	red.inputs(input);
		
	SECTION("Input neurons ont les valeurs attendues")
	{
		CHECK(red.layers[0][0].getValor() == 2);
		CHECK(red.layers[0][1].getValor() == 3);
	}

	SECTION("Bias neuron non affecte par les inputs")
	{
		CHECK(red.layers[0][2].getValor() == 1);
	}
}

TEST_CASE("Propagation correcte")
{
	SECTION("geneForwardPropagation donne un resultat plausible")
	{
		int structure[] = { 3,2,3,1 };
		Red red = Red(structure);
		double input[] = { 2,3 };
		red.inputs(input);
		red.geneForwardProp();
		double result = red.getResult();
		
		CHECK(result > -100);
		CHECK(result < 100);
	}
	
	SECTION("forwardProp donne un resultat plausible")
	{
		int structure[] = { 3,2,3,1 };
		Red red = Red(structure);
		double input[] = { 2,3 };
		red.inputs(input);
		red.forwardProp();
		double result = red.getResult();
		
		CHECK(result > -100);
		CHECK(result < 100);
	}

	SECTION("geneForwardProp donne un resultat constant pour des entrees identiques")
	{
		int structure[] = { 3,2,3,1 };
		double input[] = { 2,3 };

		Red red1 = Red(structure);
		Red red2 = Red(structure);
		
		red1.inputs(input);
		red2.inputs(input);

		red1.geneForwardProp();
		red2.geneForwardProp();

		double result1 = red1.getResult();
		double result2 = red2.getResult();
		
		CHECK(result1 == result2);
	}

	SECTION("forwardProp donne un resultat constant pour des entrees identiques")
	{
		int structure[] = { 3,2,3,1 };
		double input[] = { 2,3 };

		Red red1 = Red(structure);
		Red red2 = Red(structure);

		red1.inputs(input);
		red2.inputs(input);

		red1.forwardProp();
		red2.forwardProp();

		double result1 = red1.getResult();
		double result2 = red2.getResult();
		
		CHECK(result1 == result2);
	}

	SECTION("Les deux fonctions forwardProp doivent avoir le meme resultat")
	{
		int structure[] = { 4,4,3,3,1 };
		double input[] = { 2,3,1,10 };

		Red red = Red(structure);
		red.inputs(input);
		red.genes2weights();

		red.forwardProp();
		double result1 = red.getResult();

		red.geneForwardProp();
		double result2 = red.getResult();

		CHECK(result1 == result2);
	}
}

TEST_CASE("La fonction getResult renvoie le bon resultat")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	red.layers[red.nLayers - 1][0].setValor(6);
	
	CHECK(red.getResult() == 6);
}

TEST_CASE("La fonction getGenes renvoie la valeur correcte")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	double*** ADN = red.getGenes();
	
	for (int i = 0; i < structure[1]; i++)
	{
		for (int j = 0; j < structure[2]; j++)
		{
			for (int k = 0; k < structure[3]; k++)
			{
				CHECK(ADN[i][j][k] == i + j + k);
			}
		}
	}
}

TEST_CASE("La fonction setGenes definit correctement l'attribut genes")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	
	double ***myGenes = new double **[red.nLayers - 1];;
	for (int i = 0; i < red.nLayers - 1; i++) {
		myGenes[i] = new double*[structure[i + 1] + 1]; //[]+1 for bias
		for (int j = 0; j < red.structure[i + 1] + 1; j++) { //same
			myGenes[i][j] = new double[structure[i + 2]];
		}
	}

	for (int i = 0; i < red.nLayers - 1; i++) {
		for (int j = 0; j < red.structure[i + 1] + 1; j++) { //[]+1 for bias
			for (int k = 0; k < red.structure[i + 2]; k++) {
				myGenes[i][j][k] = 0.5;
			}
		}
	}

	red.setGenes(myGenes);
	
	for (int i = 0; i < red.nLayers - 1; i++) {
		for (int j = 0; j < red.structure[i + 1] + 1; j++) {
			for (int k = 0; k < red.structure[i + 2]; k++) {
				CHECK(red.genes[i][j][k] == 0.5);
			}
		}
	}
}

TEST_CASE("La fonction setRandomGenes initialise correctement les genes")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	red.setRandomGenes();
	
	for (int i = 0; i < red.nLayers - 1; i++) {
		for (int j = 0; j < red.structure[i + 1] + 1; j++) {
			for (int k = 0; k < red.structure[i + 2]; k++) {
				CHECK(red.genes[i][j][k] <= 1);
				CHECK(red.genes[i][j][k] >= -1);
			}
		}
	}
}

TEST_CASE("La fonction genes2weights fonctionne correctement")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);

	double ***myGenes = new double **[red.nLayers - 1];;
	for (int i = 0; i < red.nLayers - 1; i++) {
		myGenes[i] = new double*[structure[i + 1] + 1]; //[]+1 for bias
		for (int j = 0; j < red.structure[i + 1] + 1; j++) { //same
			myGenes[i][j] = new double[structure[i + 2]];
		}
	}

	for (int i = 0; i < red.nLayers - 1; i++) {
		for (int j = 0; j < red.structure[i + 1] + 1; j++) { //[]+1 for bias
			for (int k = 0; k < red.structure[i + 2]; k++) {
				myGenes[i][j][k] = i + j + k + 7;
			}
		}
	}

	red.setGenes(myGenes);
	red.genes2weights();
	
	for (int i = 0; i < structure[2] + 1; i++) {
		for (int k = 0; k < red.layers[1][i].neuronasCapaAnterior; k++) {
			CHECK(red.layers[1][i].pesos[k] == i + k + 7);
		}
	}
}

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

TEST_CASE("Population solve donne des resultats plausibles")
{
	int structure[] = { 3,2,3,1 };
	Population maPop = Population(structure, 10);
	double inputs[] = { 2,3 };
	maPop.inputs(inputs);
	maPop.solve();

	for (int i = 0; i < maPop.population_size; i++)
	{
		CHECK(maPop.individus[i].getResult() <= 1);
		CHECK(maPop.individus[i].getResult() >= 0);
	}
}