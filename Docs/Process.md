# How it works

## What we want

The program will be used through a `Population` object, which contains a collection of neural networks with various weights.
The better neural network (_ie with the best results_) will be found thanks to a Darwinian algorithm.

## How it works

1. First, the population is generated with `Population` constructor, with a given network structure and a population size. Each neural network contained in this population has different weights.
2. We call `Population::evaluate` that takes a collection of inputs and the corresponding expected values. This method will calculate the networks outputs and calculate the average error for each network.
3. After that, we call `Population::nextGeneration` that will generate a new population based on the darwinian algorithm given the networks errors.
4. We repeat steps _2_ and _3_ certain number of times until we reach a network that gives correct results
5. We get the best network out of the population with `Population::getBestNetwork`

All this process will be encapsulated in `Population::train(inputs, expected_results)`, called in `main()`, which does the following :

``` cpp
Population::train(inputs, expected_results) {
    this.evaluate(inputs, expectedResults);
    while(this.bestError() < precision)
    {
        this->nextGeneration(); //Darwinian algorithm
        this->evaluate(); //Update bestError and bestNetwork with new generation
    }
}
```

`Population::nextGeneration()` will do something like :
``` cpp
Population::nextGeneration() {
    Red *bestNetworks = this.selectBestNetworks();
    this.individus = this.reproduce(bestNetworks);
    this.mutate();
}
```

Which results in `main` :
``` cpp
Population myPop = Population(structure, size);
myPop.train(inputs, expectedResults);
Red myNetwork = myPop.getBestNetwork();
// Use myNetwork for calculations
```