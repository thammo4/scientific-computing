#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	std::cout << std::setprecision(15);

	double x = 1.000000001;
	double y = 1.0;

	double direct_difference = pow(x,2)-pow(y,2);

	double factor_difference = (x-y)*(x+y);

	std::cout << "Difference of Squares: " << direct_difference << std::endl;
	std::cout << "Factor Difference: " << factor_difference << std::endl;

	return 0;
}