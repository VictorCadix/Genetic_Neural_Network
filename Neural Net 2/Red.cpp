#include "Red.h"

using namespace std;

Red::Red(int *structure_in) {
	this->structure = structure_in;
	this->nLayers = structure[0];
	cout << "Net with " << this->nLayers << " layers" << endl;

	// Creation du reseau

	for (int c = 0; c < this->nLayers; c++) {
		this->layers.push_back(Layer());
		for (int n = 0; n < this->structure[c + 1]; n++) {
			if (c != 0)
				this->layers.back().push_back(Neurona(c, n, structure[c]));
			else //input neuron
				this->layers.back().push_back(Neurona(c, n, 0));
		}

		if (c < this->nLayers - 1) //All layers but the last one
			this->layers.back().push_back(Neurona(c, this->structure[c + 1], -1));
	}

	//Weights initialization
	
	this->genes = new double **[nLayers-1];
	for (int i = 0; i < this->nLayers-1; i++) {
		this->genes[i] = new double*[structure[i+1]+1]; //[]+1 for bias
		for (int j = 0; j < this->structure[i+1]+1; j++) { //same
			this->genes[i][j] = new double[structure[i+2]];
		}
	}


	for (int i = 0; i < this->nLayers-1; i++) {
		for (int j = 0; j < this->structure[i+1]+1; j++) { //[]+1 for bias
			for (int k = 0; k < this->structure[i+2]; k++) {
				this->genes[i][j][k] = i + j + k; // changer i+j par rand ou similaire
			}
		}
	}
}

void Red::inputs(double *in){
	cout<<endl<<"- Inputs -"<<endl;
	
	for( int e=0; e<this->structure[1]; e++){
		this->layers[0][e].setValor(in[e]);
		cout<<"Input "<<e<<" = "<<this->layers[0][e].getValor()<<endl;
	}
	cout<<endl;
}

void Red::print(){
	for (int c=0; c<this->nLayers; c++){
		for (int n=0; n<this->structure[c+1]; n++){
			this->layers[c][n].print();
			//cout<<"Neurona en : capa "<<Capas[c][n].posCapa<<", pos "<<Capas[c][n].posNeurona<<endl;
		}
	}
	//Weights print
	cout << endl << " Weights tensor" << endl;
	for (int i = 0; i < this->nLayers-1; i++) {
		cout <<endl<< "Weight matrix " << i + 1 << endl;
		for (int j = 0; j < this->structure[i+1]+1; j++) { //[]+1 for bias
			for (int k = 0; k < this->structure[i+2]; k++) {
				cout << this->genes[i][j][k] << '\t';
			}
			cout << endl;
		}		
	}

	//Result print
	cout << "Result = " << getResult() << endl;
}

void Red::geneForwardProp() {
	for (int n = 0; n < nLayers - 1; n++) {
		for (int i = 0; i < structure[n + 2]; i++) {
			double result = 0;
			for (int j = 0; j < structure[n + 1]+1; j++) { //[]+1 for bias
				result += layers[n][j].getValor()*genes[n][j][i];
			}
			layers[n + 1][i].setValor(result);
		}
	}
	cout << endl << "Result = " << getResult() << endl;
}

double Red::getResult() {
	return (layers[nLayers-1][0].getValor()); // Only works for 1 output
}

double *** Red::getGenes() {
	return genes;
}

void Red::setGenes(double***genes) {
	this->genes = genes;
}

void Red::setRandomGenes() {
	for (int i = 0; i < this->nLayers - 1; i++) {
		for (int j = 0; j < this->structure[i + 1]+1; j++) { //[]+1 for bias
			for (int k = 0; k < this->structure[i + 2]; k++) {
				this->genes[i][j][k] = (double)(rand() % 200) / 100 - 1;
			}
		}
	}
}
  
void Red::forwardProp()
{
	//We skip the input layer

	for (int i = 1; i < this->nLayers; i++)
	{
		cout << endl << "== NEW LAYER ==" << endl;
		//In a layer
		Layer currentLayer = this->layers[i];

		//Previous layer
		Layer previousLayer = this->layers[i - 1];

		for (int j = 0; j < currentLayer.size(); j++)
		{
			//In a neuron
			cout << "NEURON" << endl;

			Neurona currentNeuron = currentLayer[j];
			double value = 0;
			if (currentNeuron.neuronasCapaAnterior == 0) //Is a bias?
			{
				cout << "Is a bias" << endl;
				break;
			}

			//For that neuron, we calculate it's value with the previous layer's neurons
			for (int k = 0; k < currentNeuron.neuronasCapaAnterior + 1; k++)
			{
				//In a previous neuron
				double previousNeuronValue = previousLayer[k].getValor();
				value = value + (currentNeuron.pesos[k] * previousNeuronValue);
				cout << "Previous neuron value : " << previousNeuronValue << endl;
			}

			//We save the value in the current neuron
			currentNeuron.setValor(value);
			layers[i][j].setValor(value);
			layers[i][j].activate_sigmoid();
			double test = layers[i][j].getValor();
			cout << "Neuron value : " << test << endl;
			cout << endl;
		}
	}
}