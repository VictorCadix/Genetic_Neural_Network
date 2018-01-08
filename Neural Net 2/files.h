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