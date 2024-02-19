#include <iostream>
#include <Eigen/Dense>

int main() {
	// Eigen::Matrix3d matrix;
	// matrix << 1,2,3,4,5,6,7,8,9;
	Eigen::Matrix2d A;
	// A << 1,2,3,4;
	A << 4,1,1,3;

	//
	// Compute eigenvalues of matrix
	//

	// Eigen::EigenSolver<Eigen::Matrix3d> solver(matrix);
	Eigen::EigenSolver<Eigen::Matrix2d> solver(A);
	Eigen::VectorXcd eigenvalues = solver.eigenvalues();
	// Eigen::VectorXcd eigenvalues = solver.eigenvalues();

	// std::cout << "Matrix:\n" << matrix << std::endl;
	std::cout << "Matrix:\n" << A << std::endl;
	std::cout << "Eigenvalues:\n" << eigenvalues << std::endl;

	return 0;
}