#include "stdafx.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iostream>
#include <vector>

/* Include files of Neural Network project */
#include "../../Neural Net 2/Neurona.h"
#include "../../Neural Net 2/Red.h"

TEST_CASE("Création d'un objet Neurone bien formé")
{
	Neurona neuroneTest = Neurona(1, 1, 1);
	REQUIRE(neuroneTest.getValor() == 0);
}