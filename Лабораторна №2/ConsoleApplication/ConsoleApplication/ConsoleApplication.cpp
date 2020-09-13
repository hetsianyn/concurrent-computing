#include "pch.h"

#include <iostream>
#include <thread>
#include <time.h>
#include <omp.h>

using namespace std;

//to show matrix
void show(int **mat, int n, int m) {

	cout << "\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << mat[i][j] << " ";
		}
		cout << '\n';
	}
	cout << "\n";
}

//to show array
void show(int* arr, int size) {
	cout << "\n";
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << "\n";
}

//count the positive numbers in the matrix in each row
int count_a(int **matrix, int *result, int size) {

	int i, j;
#pragma omp parallel shared(matrix,result) private(i,j)
	{
#pragma omp for schedule(static, 2)
		for (i = 0; i < size; i++) {
			int count = 0;
			for (j = 0; j < size; j++) {
				if (matrix[i][j] < 0)
					count++;
			}
			result[i] = count;
			printf("Iteration %d Thread %d\n", i, omp_get_thread_num());			
		}
	}
	return 0;
}

int count_b(int **matrix, int *result, int size) {

	int i;
	int j;
#pragma omp parallel shared(matrix,result) private(i,j)
	{
#pragma omp for schedule(guided, 6)
		for (i = 0; i < size; i++) {
			int count = 0;
			for (j = 0; j < size; j++) {
				if (matrix[i][j] < 0)
					count++;
			}
			result[i] = count;
			printf("Iteration %d Thread %d\n", i, omp_get_thread_num());
		}
	}
	return 0;
}


int main()
{
	int size_n;
	int** matrix_a;
	int** matrix_b;
	int* result_c;
	int* result_d;

	cout << "Input n:\n n = ";
	cin >> size_n;
	
	matrix_a = new int*[size_n];
	matrix_b = new int*[size_n];
	result_c = new int[size_n];
	result_d = new int[size_n];

	for (int i = 0; i < size_n; ++i) {
		matrix_a[i] = new int[size_n];
		matrix_b[i] = new int[size_n];
	}

	//fills the matrix A with random numbers in range (-100; 100) 
	for (int i = 0; i < size_n; ++i) {
		for (int j = 0; j < size_n; ++j) {
			matrix_a[i][j] = (rand() % 200) - 100;
		}
	}
	show(matrix_a, size_n, size_n);

	//fills the matrix B with random numbers in range (-100; 100)
	for (int i = 0; i < size_n; ++i) {
		for (int j = 0; j < size_n; ++j) {
			matrix_b[i][j] = (rand() % 200) - 100;
		}
	}
	show(matrix_b, size_n, size_n);

	omp_set_num_threads(4);
	count_a(matrix_a, result_c, size_n);
	show(result_c, size_n);
	//omp_set_num_threads(4);
	//count_b(matrix_b, result_d, size_n);
	//show(result_d, size_n);

	//free up memory
	for (int i = 0; i < size_n; ++i) {
		delete[] matrix_a[i];
		delete[] matrix_b[i];
	}
	delete[] matrix_a;
	delete[] matrix_b;
	delete[] result_c;
	delete[] result_d;

	return 0;
}