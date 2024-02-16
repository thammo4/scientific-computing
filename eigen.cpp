#include <iostream>
#include <Eigen/Dense>


int main() {
	Eigen::MatrixXd A(3,3);
	A << 1,2,3,4,5,6,7,8,9;

	double frobenius_norm = A.norm();
	std::cout << "Frobenius Norm: " << frobenius_norm << std::endl;

	double l1_norm = A.cwiseAbs().colwise().sum().maxCoeff();
	std::cout << "L1 Norm: " << l1_norm << std::endl;

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
	double l2_norm = svd.singularValues()(0);

	std::cout << "L2 Norm (Spectral): " << l2_norm << std::endl;

	return 0;
}

