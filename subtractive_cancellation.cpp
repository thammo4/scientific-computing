#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	double x = 3.14159265358979323846;
	double y = 3.14160;

	double directDifference = y-x;
	double computedDifference = 1 - x/y;

	cout << fixed << setprecision(16);
	cout << "Direct Difference: " << directDifference << endl;
	cout << "Computed Difference: " << computedDifference << endl;

	return 0;
}