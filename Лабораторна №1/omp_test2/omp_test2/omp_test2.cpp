// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <thread>
#include <time.h>
#include <omp.h>

using namespace std;

int serial(float **matrix, float *vector, float *result, int size_i, int size_j) {

	int i;
	int j;
	for (i = 0; i < size_i; i++) {
		result[i] = 0;
		for (j = 0; j < size_j; j++) {
			matrix[i][j] = j * sin(i);
			vector[i] = i * sin(i);
			result[i] += matrix[i][j] * vector[j];
		}
	}
	return 0;
}

int parallel(float** matrix, float* vector, float* result, int size_i, int size_j)
{
	int i, j;

#pragma omp parallel shared(matrix,result,vector) private(i,j) 
	{
#pragma omp for  schedule(static)
		for (i = 0; i < size_i; i++) {
			result[i] = 0.;
			for (j = 0; j < size_j; j++) {
				matrix[i][j] = j * sin(i);
				vector[i] = i * sin(i);
				result[i] += matrix[i][j] * vector[j];
			}
		}
	}
	return 0;
}


int main() {

	int size_i;
	int size_j;
	float** matrix;
	float* vector;
	float* result;
	
	//int num_threads;
	//cout << "Input amount of threads: ";
	//cin >> num_threads;
	cout << "Input n:\n n = ";
	cin >> size_i;
	size_j = size_i;

	matrix = new float*[size_i];
	vector = new float[size_j];
	result = new float[size_j];

	for (int i = 0; i < size_i; ++i) {
		matrix[i] = new float[size_j];
	}

	for (int i = 0; i < size_i; ++i) {
		for (int j = 0; j < size_j; ++j) {
			matrix[i][j] = rand() % 10;
		}
	}


	for (int i = 0; i < size_j; ++i) {
		vector[i] = rand() % 10;
	}


	clock_t time1 = clock();
	serial(matrix, vector, result, size_i, size_j);
	cout << "Serial = " << ((float)(clock() - time1)) / CLK_TCK << " seconds \n";
	
	omp_set_num_threads(1);
	clock_t time2 = clock();
	parallel(matrix, vector, result, size_i, size_j);
	cout << "Parallel(1 threads) = " << ((float)(clock() - time2))/CLK_TCK << " seconds \n";


	omp_set_num_threads(2);
	clock_t time3 = clock();
	parallel(matrix, vector, result, size_i, size_j);
	cout << "Parallel(2 threads) = " << ((float)(clock() - time3)) / CLK_TCK << " seconds \n";


	omp_set_num_threads(4);
	clock_t time4 = clock();
	parallel(matrix, vector, result, size_i, size_j);
	cout << "Parallel(4 threads) = " << ((float)(clock() - time4)) / CLK_TCK << " seconds \n";

	for (int i = 0; i < size_i; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] vector;
	delete[] result;

	system("pause");
	return 0;
}

