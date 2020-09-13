// output test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <fstream>
#include <stdio.h>
#include <omp.h>
#include <windows.h>

using namespace std;

omp_lock_t lock;

int main(int argc, char *argv[])
{
	ofstream myfile("test.txt");
	int n;
	omp_init_lock(&lock);
#pragma omp parallel private (n)
	{
		n = omp_get_thread_num();
		omp_set_lock(&lock);
		myfile << "The beginning of the closed section, flow" << n << "\n";
		Sleep(500);
		myfile << "The end of the closed section, flow" << n << "\n";
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
}