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
		std::cout.setstate(std::ios_base::failbit);
		Neurona neuroneTest = Neurona(1, 1, 1);
		std::cout.clear();

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
		std::cout.setstate(std::ios_base::failbit);
		Neurona neuroneTest = Neurona(3, 3, 3);
		std::cout.clear();

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
		std::cout.setstate(std::ios_base::failbit);
		Neurona neuroneTest = Neurona();
		std::cout.clear();

		CHECK(neuroneTest.getValor() == 0);
		CHECK(neuroneTest.posNeurona == 0);
		CHECK(neuroneTest.posCapa == 0);
		CHECK(neuroneTest.neuronasCapaAnterior == 0);
		CHECK(neuroneTest.pesos == NULL);
	}

	SECTION("Creation bias neuron")
	{
		std::cout.setstate(std::ios_base::failbit);
		Neurona testNeuron = Neurona(2, 2, -1);
		std::cout.clear();

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
	// A COMPLETER
	{
		std::cout.setstate(std::ios_base::failbit);
		Neurona testNeuron = Neurona(0, 2, 0);
		std::cout.clear();

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
		std::cout.setstate(std::ios_base::failbit);
		Neurona test = Neurona(1, 1, 1);
		std::cout.clear();

		test.setValor(3);
		test.activate_sigmoid();
		CHECK(test.getValor() == Approx(0.95257));
	}
	
	SECTION("Fonction tanh")
	{
		std::cout.setstate(std::ios_base::failbit);
		Neurona test = Neurona(1, 1, 1);
		std::cout.clear();

		test.setValor(3);
		test.activate_tanh();
		CHECK(test.getValor() == Approx(-0.99505));
	}
}

TEST_CASE("Constructeur de Red")
{
	std::cout.setstate(std::ios_base::failbit);

	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);

	std::cout.clear();

	SECTION("Attribut structure correct")
	{
		CHECK(structure[0] == 3);
		CHECK(structure[1] == 2);
		CHECK(structure[2] == 3);
		CHECK(structure[3] == 1);
	}

	SECTION("Attrbiut nombre de couches")
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
			//===TEST DEPLACE EN FIN DE FICHIER===
			//CHECK(neuron.pesos == NULL);
		}
	}

	SECTION("Poids correctement initialises")
	{
		//===TEST DEPLACE EN FIN DE FICHIER===
		/*
		for (int i = 0; i < structure[2]+1; i++) {
			for (int k = 0; k < red.layers[1][i].neuronasCapaAnterior + 1 ; k++ ){
				CHECK (red.layers[1][i].pesos[k] == k);
			}
		}
		*/
	}
}

TEST_CASE("Reglage des inputs du reseau")
{
	std::cout.setstate(std::ios_base::failbit);

	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	double input[] = { 1,3 };
	red.inputs(input);

	std::cout.clear();

	SECTION("Input neurons ont les valeurs attendues")
	{
		CHECK(red.layers[0][0].getValor() == 1);
		CHECK(red.layers[0][1].getValor() == 3);
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

	SECTION("Les deux fonctions forwardProp doivent avoir le même resultat")
	{
		//A completer
	}
}

TEST_CASE("La fonction getResult renvoie le bon resultat")
{
	std::cout.setstate(std::ios_base::failbit);

	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	red.layers[red.nLayers - 1][0].setValor(6);

	std::cout.clear();

	CHECK(red.getResult() == 6);
}

TEST_CASE("La fonction getGenes renvoie la valeur correcte")
{
	//A completer
	std::cout.setstate(std::ios_base::failbit);

	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);
	double*** ADN = red.getGenes();

	std::cout.clear();

	CHECK(ADN[0][2][2] == 4);
}

TEST_CASE("La fonction setGenes definit correctement l'attribut genes")
{
	//A completer
}

TEST_CASE("La fonction setRandomGenes initialise correctement les genes")
{
	//A completer
}

/*
	Ces derniers tests echouent pour l'instant, ils ont ete mis a part pour autoriser
	leur echec. Lorsque le probleme sera resolu, les tests echoueront pour rappeler que
	ces tests etaient censes echouer. On pourra alors les remettre dans leur section
	correspodantes.
*/

TEST_CASE("Poids des neurones correctement initialisés", "[!shouldfail]")
{
	std::cout.setstate(std::ios_base::failbit);

	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);

	std::cout.clear();

	for (int i = 0; i < structure[2] + 1; i++) {
		for (int k = 0; k < red.layers[1][i].neuronasCapaAnterior + 1; k++) {
			CHECK(red.layers[1][i].pesos[k] == k);
		}
	}
}

TEST_CASE("Poids des neurones bias ok", "[!shouldfail]")
{
	std::cout.setstate(std::ios_base::failbit);

	int structure[] = { 3,2,3,1 };
	Red red = Red(structure);

	std::cout.clear();

	for (int i = 0; i < red.nLayers - 1; i++)
	{
		Layer couche = red.layers[i];
		Neurona neuron = couche[couche.size() - 1];
		CHECK(neuron.pesos == NULL);
	}
}