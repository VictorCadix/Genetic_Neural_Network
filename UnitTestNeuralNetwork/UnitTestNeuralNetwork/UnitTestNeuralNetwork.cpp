#include "stdafx.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iostream>
#include <vector>

/* Include files of Neural Network project */
#include "../../Neural Net 2/Neurona.h"
#include "../../Neural Net 2/Red.h"

TEST_CASE("Creation d'un objet Neurona")
{
	SECTION("Neurone simple")
	{
		Neurona neuroneTest = Neurona(1, 1, 1);

		REQUIRE(neuroneTest.getValor() == 0);
		REQUIRE(neuroneTest.posNeurona == 1);
		REQUIRE(neuroneTest.posCapa == 1);
		REQUIRE(neuroneTest.neuronasCapaAnterior == 1);

		for (int p = 0; p < neuroneTest.neuronasCapaAnterior; p++) {
			REQUIRE(neuroneTest.pesos[p] <= 10);
			REQUIRE(neuroneTest.pesos[p] >= -10);
		}
	}

	SECTION("Neurone plus complexe")
	{
		Neurona neuroneTest = Neurona(3, 3, 3);

		REQUIRE(neuroneTest.getValor() == 0);
		REQUIRE(neuroneTest.posNeurona == 3);
		REQUIRE(neuroneTest.posCapa == 3);
		REQUIRE(neuroneTest.neuronasCapaAnterior == 3);

		for (int p = 0; p < neuroneTest.neuronasCapaAnterior; p++) {
			REQUIRE(neuroneTest.pesos[p] <= 10);
			REQUIRE(neuroneTest.pesos[p] >= -10);
		}
	}

	SECTION("Test creation neurone par defaut")
	{
		Neurona neuroneTest = Neurona();

		REQUIRE(neuroneTest.getValor() == 0);
		REQUIRE(neuroneTest.posNeurona == 0);
		REQUIRE(neuroneTest.posCapa == 0);
		REQUIRE(neuroneTest.neuronasCapaAnterior == 0);
		REQUIRE(neuroneTest.pesos == NULL);
	}

	SECTION("Creation bias neuron")
	{
		Neurona testNeuron = Neurona(2, 2, -1);

		REQUIRE(testNeuron.getValor() == 1);
		REQUIRE(testNeuron.posNeurona == 2);
		REQUIRE(testNeuron.posCapa == 2);
		REQUIRE(testNeuron.neuronasCapaAnterior == 0);
		for (int p = 0; p < testNeuron.neuronasCapaAnterior; p++) {
			REQUIRE(testNeuron.pesos[p] <= 10);
			REQUIRE(testNeuron.pesos[p] >= -10);
		}
	}

	SECTION("Creation input neuron")
	// A COMPLETER
	{
		Neurona testNeuron = Neurona(0, 2, 0);

		REQUIRE(testNeuron.getValor() == 0);
		REQUIRE(testNeuron.posNeurona == 2);
		REQUIRE(testNeuron.posCapa == 0);
		REQUIRE(testNeuron.neuronasCapaAnterior == 0);
		REQUIRE(testNeuron.pesos == NULL);
	}
}

TEST_CASE("Fonction d'activation")
{
	SECTION("Fonction sigmoid")
	{
		Neurona test = Neurona(1, 1, 1);
		test.setValor(3);
		test.activate_sigmoid();
		REQUIRE(abs(test.getValor() - 0.95) < 0.01);
	}
	
	SECTION("Fonction tanh")
	{
		Neurona test = Neurona(1, 1, 1);
		test.setValor(3);
		test.activate_tanh();
		REQUIRE(abs(test.getValor() - (-0.99)) < 0.01);
	}
}

TEST_CASE("Constructeur de Red")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);

	SECTION("Attribut structure correct")
	{
		REQUIRE(structure[0] == 3);
		REQUIRE(structure[1] == 2);
		REQUIRE(structure[2] == 3);
		REQUIRE(structure[3] == 1);
	}

	SECTION("Attrbiut nombre de couches")
	{
		REQUIRE(red.nLayers == 3);
	}

	SECTION("Nombre de couches crees")
	{
		REQUIRE(red.layers.size() == 3);
	}

	SECTION("Nombre de neurones dans chaque couche")
	{
		//One more neuron (the bias) on all layers but the last one
		REQUIRE(red.layers[0].size() == 3);
		REQUIRE(red.layers[1].size() == 4);
		REQUIRE(red.layers[2].size() == 1);
	}

	SECTION("Premiere couche d'input neurons")
	{
		Layer couche = red.layers[0];
		for (int i = 0; i < couche.size(); i++)
		{
			REQUIRE(couche[i].neuronasCapaAnterior == 0);
			REQUIRE(couche[i].posNeurona == i);
			REQUIRE(couche[i].posCapa == 0);
			REQUIRE(couche[i].pesos == NULL);
		}
	}

	SECTION("Bias neurons correctement crees")
	{
		for (int i = 0; i < red.nLayers - 1; i++)
		{
			Layer couche = red.layers[i];
			Neurona neuron = couche[couche.size()-1];
			REQUIRE(neuron.getValor() == 1);
			REQUIRE(neuron.posCapa == i);
			REQUIRE(neuron.neuronasCapaAnterior == 0);
			//REQUIRE(neuron.pesos == NULL);
		}
	}

	SECTION("Poids correctement initialises")
	{
		//A completer
	}
}

TEST_CASE("Reglage des inputs du reseau")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	double input[] = { 1,3 };
	red.inputs(input);

	SECTION("Input neurons ont les valeurs attendues")
	{
		REQUIRE(red.layers[0][0].getValor() == 1);
		REQUIRE(red.layers[0][1].getValor() == 3);
	}
}

TEST_CASE("Propagation correcte")
{
	SECTION("Fonction geneForwardPropagation")
	{
		//A completer
	}
	
	SECTION("Fonction forwardProp")
	{
		//A completer
	}
}

TEST_CASE("La fonction getResult renvoie le bon resultat")
{
	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	red.layers[red.nLayers - 1][0].setValor(6);
	REQUIRE(red.getResult() == 6);
}

TEST_CASE("La fonction getGenes renvoie la valeur correcte")
{
	//A completer
}

TEST_CASE("La fonction setGenes definit correctement l'attribut genes")
{
	//A completer
}

TEST_CASE("La fonction setRandomGenes initialise correctement les genes")
{
	//A completer
}