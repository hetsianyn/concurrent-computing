#include "pch.h"

#include <iostream>
#include <math.h>
using namespace std;
	
int main()
{
	int n;
	cout << "Input n" << endl;
	cin >> n;

	int a = n;
	int b = n * 2;
	double k = n / 2;
	double h = n / k;
	
	for (double x = 1; x <= n + 1; x += h)
	{
		double param = -(fabs(x - a)) / b;
		double y = exp(param) / 2 * b;
		cout << " x= " << x << " y= " << y << endl;
	}

	return 0;
}
