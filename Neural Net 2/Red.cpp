#include "Red.h"

using namespace std;

Red::Red(int *structure_in) {
	this->structure = structure_in;
	this->nLayers = structure[0];
	cout << "Net with " << this->nLayers << " layers" << endl;

	// Creation du reséau

	for (int c = 0; c < this->nLayers; c++) {
		this->layers.push_back(Layer());
		for (int n = 0; n < this->structure[c + 1]; n++) {
			if (c != 0)
				this->layers.back().push_back(Neurona(c, n, structure[c]));
			else //input neuron
				this->layers.back().push_back(Neurona(c, n, 0));
		}
	}

	//Weights initialization
	
	this->genes = new double **[nLayers-1];
	for (int i = 0; i < this->nLayers-1; i++) {
		this->genes[i] = new double*[structure[i+1]];
		for (int j = 0; j < this->structure[i+1]; j++) {
			this->genes[i][j] = new double[structure[i+2]];
		}
	}

	for (int i = 0; i < this->nLayers-1; i++) {
		for (int j = 0; j < this->structure[i+1]; j++) {
			for (int k = 0; k < this->structure[i+2]; k++) {
				this->genes[i][j][k] = i + j + k; // changer i+j par rand ou similaire
			}
		}
	}
}

void Red::inputs(double *in){
	cout<<endl;
	for( int e=0; e<this->structure[1]; e++){
		this->layers[0][e].setValor(in[e]);
		cout<<"Entrada "<<e<<"="<<this->layers[0][e].getValor()<<endl;
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
		for (int j = 0; j < this->structure[i+1]; j++) {
			for (int k = 0; k < this->structure[i+2]; k++) {
				cout << this->genes[i][j][k] << '\t';
			}
			cout << endl;
		}		
	}
}

void Red::forwardProp()
{
	//We skip the input layer

	for (int i = 1; i < this->nLayers; i++)
	{
		//In a layer
		Layer currentLayer = this->layers[i];

		//Previous layer
		Layer previousLayer = this->layers[i - 1];

		for (int j = 0; j < currentLayer.size(); j++)
		{
			//In a neuron
			Neurona currentNeuron = currentLayer[j];
			double value = 0;

			//For that neuron, we calculate it's value with the previous layer's neurons
			for (int k = 0; k < currentNeuron.neuronasCapaAnterior; k++)
			{
				//In a previous neuron
				value = value + currentNeuron.pesos[k] * previousLayer[k].getValor();
			}

			//We save the value in the current neuron
			currentNeuron.setValor(value);
		}
	}
}