#include "Red.h"

using namespace std;

Red::Red(int *structure_in) {
	structure = structure_in;
	nLayers = structure[0];
	cout << "Net with " << nLayers << " layers" << endl;

	/*	for (int c=0; c<nCapas; c++){
			for (int n=0; n<formato[c+1]; n++){
				neuronas = new Neurona(c,n);
			}
		}*/

	for (int c = 0; c < nLayers; c++) {
		Layers.push_back(Layer());
		for (int n = 0; n < structure[c + 1]; n++) {
			if (c != 0)
				Layers.back().push_back(Neurona(c, n, structure[c]));
			else //input neuron
				Layers.back().push_back(Neurona(c, n, 0));
		}
	}

	//Weights initialization
	/*
	weights = new double *[structure[1]];
	for (int i=0; i<structure[1]; i++)
		weights[i] = new double[structure[2]];

	for (int i = 0; i < structure[1]; i++) {
		for (int j = 0; j < structure[2]; j++)
			weights[i][j] = i + j; // changer i+j par rand ou similaire
	}
	*/
	weights = new double **[nLayers-1];
	for (int i = 0; i < nLayers-1; i++) {
		weights[i] = new double*[structure[i+1]];
		for (int j = 0; j < structure[1]; j++) {
			weights[i][j] = new double[structure[i+2]];
		}
	}

	for (int i = 0; i < nLayers-1; i++) {
		for (int j = 0; j < structure[i+1]; j++) {
			for (int k = 0; k < structure[i+2]; k++) {
				weights[i][j][k] = i + j + k; // changer i+j par rand ou similaire
			}
		}
	}
}

void Red::inputs(double *in){
	cout<<endl;
	for( int e=0; e<structure[1]; e++){
		Layers[0][e].setValor(in[e]);
		cout<<"Entrada "<<e<<"="<<Layers[0][e].getValor()<<endl;
	}
	cout<<endl;
}

void Red::print(){
	for (int c=0; c<nLayers; c++){
		for (int n=0; n<structure[c+1]; n++){
			Layers[c][n].print();
			//cout<<"Neurona en : capa "<<Capas[c][n].posCapa<<", pos "<<Capas[c][n].posNeurona<<endl;
		}
	}
	//Weights print
	cout << endl << " Weights tensor" << endl;
	for (int i = 0; i < nLayers-1; i++) {
		cout <<endl<< "Weight matrix " << i + 1 << endl;
		for (int j = 0; j < structure[i+1]; j++) {
			for (int k = 0; k < structure[i+2]; k++) {
				cout << weights[i][j][k] << '\t';
			}
			cout << endl;
		}		
	}
}