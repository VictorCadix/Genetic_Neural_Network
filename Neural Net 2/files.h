#pragma once

#include <iostream>

int getTrainingData(FILE* sourceFile, double** &input, double** &output) {
	int total_data;
	int nInputs;
	int nOutputs;
	int cont = 0;

	while (!feof(sourceFile)) {
		char line[100];
		char token;
		fgets(line, 100, sourceFile);
		sscanf(line, "%c", &token);

		if (token == '%') {
			//Its a comment
		}
		else if (token == '#') {
			sscanf(line, "%c %d %*c %d %*c %d", &token, &total_data, &nInputs, &nOutputs);

			//Allocating memory for the input
			input = new double *[total_data];
			for (int i = 0; i < total_data; i++) {
				input[i] = new double[nInputs];
			}
			//Allocating memory for the output
			output = new double*[total_data];
			for (int i = 0; i < total_data; i++) {
				output[i] = new double[nOutputs];
			}
		}
		else {
			sscanf(line, "%lf %lf %*c %lf", &input[cont][0], &input[cont][1], &output[cont][0]);
			cont++;
		}
	}
	return (total_data);
}

void save_Network(string file_name, Red &red, int *structure) {
	ofstream file;
	file.open(file_name);
	file << "% Structure:" << endl;
	file << "S";
	for (int i = 0; i <= structure[0]; i++) {
		file << " " << structure[i];
	}

	//Weights print
	file << endl << "% Weights of the best network" << endl;

	for (int i = 0; i < structure[0] - 1; i++) {
		file << "% Weight matrix " << i << endl;
		file << "M " << i << endl;
		for (int j = 0; j < structure[i + 1] + 1; j++) { //[]+1 for bias
			for (int k = 0; k < structure[i + 2]; k++) {
				file << red.genes[i][j][k] << '\t';
			}
			file << endl;
		}
	}
	file << "END";
	file.close();
}

Red* load_network(string file_name) {
	ifstream file;
	file.open(file_name);

	Red red;
	int* structure;

	//Variables for weights
	int i = 0;
	int j = 0;

	while (!file.eof()) {
		char line[100];
		string strLine;
		char token;
		int position = file.tellg(); //Start of line
		file.getline(line, 100);
		int nextPosition = file.tellg();

		strLine = line;
		
		sscanf(line, "%c", &token);
		if (token == '%') {
			//Its a comment
		}
		else if (token == 'S') {
			int nLayers;
			char word[10];
			sscanf(line, "%*c %d", &nLayers);
			structure = new int[nLayers];
			file.seekg(position);
			for (int i = -1; i < nLayers + 1; i++) {
				if (i != -1)
					file >> structure[i];
				else if (i == -1)
					file >> word;
			}
			red = Red(structure);
			file.seekg(nextPosition);
		}
		else if (token == 'M') {
			sscanf(line, "%*c %d", &i);
			j = 0;
		}
		else if (token == 'E') {
			//End of file
			break;
		}
		else {
			file.seekg(position);
			for (int k = 0; k < structure[i + 2]; k++) {
				file >> red.genes[i][j][k];
			}
			j++;
			file.seekg(nextPosition);
		}
	}
	file.close();
	return &red;
}