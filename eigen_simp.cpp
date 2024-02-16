#include <iostream>
#include <Eigen/Core>

int main() {
	int size = 50;

	//
	// Vector of floats with dynamic size
	//

	Eigen::VectorXf u(size), v(size), w(size);

	u = v + w;
}