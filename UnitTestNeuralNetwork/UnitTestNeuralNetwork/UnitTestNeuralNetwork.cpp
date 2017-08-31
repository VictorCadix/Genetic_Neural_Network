#include "stdafx.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iostream>
#include <vector>

/* Include files of Neural Network project */
#include "../../Neural Net 2/Neurona.h"
#include "../../Neural Net 2/Red.h"

TEST_CASE("Creation d'un objet Neurona classique bien forme")
{
	SECTION("Neurone simple")
	{
		Neurona neuroneTest = Neurona(1, 1, 1);

		REQUIRE(neuroneTest.getValor() == 0);
		REQUIRE(neuroneTest.posNeurona == 1);
		REQUIRE(neuroneTest.posCapa == 1);
		REQUIRE(neuroneTest.neuronasCapaAnterior == 1);

		for (int p = 0; p<neuroneTest.neuronasCapaAnterior; p++) {
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

		for (int p = 0; p<neuroneTest.neuronasCapaAnterior; p++) {
			REQUIRE(neuroneTest.pesos[p] <= 10);
			REQUIRE(neuroneTest.pesos[p] >= -10);
		}
	}
	
}

TEST_CASE("Test creation neurone par defaut")
{
	Neurona neuroneTest = Neurona();

	REQUIRE(neuroneTest.getValor() == 0);
	REQUIRE(neuroneTest.posNeurona == 0);
	REQUIRE(neuroneTest.posCapa == 0);
	REQUIRE(neuroneTest.neuronasCapaAnterior == 0);
	REQUIRE(neuroneTest.pesos == NULL);
}