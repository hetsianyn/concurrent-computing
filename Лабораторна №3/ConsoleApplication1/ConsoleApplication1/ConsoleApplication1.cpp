#include <iostream>
#include "pch.h"
#include <math.h>
#include <omp.h>
#include <stdio.h>

#define N 20 

using namespace std;

double calculate(const int x_max, const int NUM_OF_THREADS) {
	double z = N * N;
	double k = N / 2;
	double h = N / k;
	double x = 1;
	double y;
	int size = (int)(x_max - 1) / h;

	double* res = new double[size];

	omp_set_num_threads(NUM_OF_THREADS);
	omp_set_dynamic(false);

	double start = omp_get_wtime();

#pragma omp parallel for num_threads(NUM_OF_THREADS)
	for (int i = 0; i < size; i++) {
		res[i] = x - 10 * exp(sin(x)) + cos(x - z);
		x += h;
	}
	double end = omp_get_wtime();

	/*
	#pragma omp parallel for num_threads(4)
	for (int i = 0; i < size; i++) {
		cout << "res[" << i << "] = " << res[i] << "\n";
	}
	*/
	return end - start;
}

int main()
{
	double N_1_T_1 = calculate(200, 1);
	double N_1_T_2 = calculate(200, 2);
	double N_1_T_4 = calculate(200, 4);
	double N_2_T_1 = calculate(2000, 1);
	double N_2_T_2 = calculate(2000, 2);
	double N_2_T_4 = calculate(2000, 4);
	double N_3_T_1 = calculate(20000, 1);
	double N_3_T_2 = calculate(20000, 2);
	double N_3_T_4 = calculate(20000, 4);
	double N_4_T_1 = calculate(200000, 1);
	double N_4_T_2 = calculate(200000, 2);
	double N_4_T_4 = calculate(200000, 4);
	double N_5_T_1 = calculate(2000000, 1);
	double N_5_T_2 = calculate(2000000, 2);
	double N_5_T_4 = calculate(2000000, 4);

	cout << "200_1: " << N_1_T_1 << endl;
	cout << "200_2: " << N_1_T_2 << endl;
	cout << "200_4: " << N_1_T_4 << endl;

	cout << "2000_1: " << N_2_T_1 << endl;
	cout << "2000_2: " << N_2_T_2 << endl;
	cout << "2000_4: " << N_2_T_4 << endl;

	cout << "20000_1: " << N_3_T_1 << endl;
	cout << "20000_2: " << N_3_T_2 << endl;
	cout << "20000_4: " << N_3_T_4 << endl;

	cout << "200000_1: " << N_4_T_1 << endl;
	cout << "200000_2: " << N_4_T_2 << endl;
	cout << "200000_4: " << N_4_T_4 << endl;

	cout << "2000000_1: " << N_5_T_1 << endl;
	cout << "2000000_2: " << N_5_T_2 << endl;
	cout << "2000000_4: " << N_5_T_4 << endl;
}
