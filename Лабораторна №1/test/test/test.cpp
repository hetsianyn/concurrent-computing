// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <omp.h>
#include <thread>
#include <time.h>
#include <cmath>

int main() {

	long m, n;
	long** matrix;
	long* array_;
	long* result;


	n = 10000;
	m = n;

	matrix = new long*[n];
	array_ = new long[m];
	result = new long[m];

	for (int i = 0; i < n; ++i) {
		matrix[i] = new long[m];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			matrix[i][j] = rand() % 10;
		}
	}
	//show(matrix, n, m);


	for (int i = 0; i < m; ++i) {
		array_[i] = rand() % 10;
	}
	//show(array_, m);

	clock_t timeBegin = clock();

#pragma omp parallel shared(matrix, array_, result)
	{
#pragma omp for schedule (dynamic)
		for (int i = 0; i < n; ++i) {
			result[i] = 0;
			for (int j = 0; j < m; ++j)
			{
				result[i] += matrix[i][j] * array_[j];
			}
		}
	}

	std::cout << "Total ticks 1 = " << clock() - timeBegin << '\n';

	

	for (int i = 0; i < n; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] array_;
	delete[] result;

	system("pause");
	return 0;
}



/* output
enter n = 1000
enter m = 2000

Total ticks 1 = 12
Total ticks 2 = 8

*/