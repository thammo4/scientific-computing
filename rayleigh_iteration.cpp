#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

void rayleighQuotientIteration (const MatrixXd& A, VectorXd& x, int max_iter, double tolerance) {
	// double lambda = x.transpose() * A * x / (x.transpose()*x);
	double lambda = (x.transpose()*A*x).value() / (x.transpose()*x).value();
	int iter = 0;

	while (iter < max_iter) {
		//
		// Solve the linear system: (A - λI)x = b
		//

		VectorXd b = A*x;
		MatrixXd M = A - lambda * MatrixXd::Identity(A.rows(), A.cols());
		VectorXd y = M.colPivHouseholderQr().solve(b);

		//
		// Normalize vector y
		//

		// y /= y.norm();

		//
		// Update eigenvalue λ
		//

		// double lambda_new = y.transpose() * A * y / (y.transpose()*y);
		double lambda_new = (y.transpose()*A*y).value() / (y.transpose()*y).value();

		//
		// Convergence check
		//

		if (abs(lambda_new - lambda) < tolerance) {
			lambda = lambda_new;
			x = y;
			break;
		}

		lambda = lambda_new;
		x = y;
		iter++;
	}
}





int main () {
	//
	// Define example matrix
	//

	MatrixXd A(3,3);

	A << 4,1,1,1,3,2,1,2,4;


	//
	// Take a stab at the eigenvector value
	//

	VectorXd x(3);
	x << 4, 5, 6;

	//
	// Rayleigh quotient hyperparameters
	//

	int max_iter = 500;
	double tolerance = 1e-2;

	// 
	// Apply Rayeligh quotient iteration to determine eigenvalues
	//

	rayleighQuotientIteration(A, x, max_iter, tolerance);

	//
	// Print results
	//

	// cout << "Eigenvalue: " << x.transpose() * A * x / (x.transpose()*x) << endl;
	cout << "Eigenvalue: " << (x.transpose()*A*x).value() / (x.transpose()*x).value() << endl;
	cout << "Eigenvector:\n" << x << endl;

	return 0;
}