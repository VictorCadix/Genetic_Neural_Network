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