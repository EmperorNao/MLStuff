#include <iostream>
#include "grad.h"
#include <cmath>


double test_func(double x) {

	return (pow(3, -x) + pow(3, x - 2) + 2);
	//return x * x + 3 * x - 4;

}

double test_deriv(double x) {

	return (pow(3, -x - 2) * (pow(9, x) - 9) * log(3));

}

double autog(double x) {

	double eps = 0.00001;
	return (test_func(x + eps) - test_func(x)) / eps;

}

double test_func_n_dim(std::vector<double> x) {

	return (x[0] - 2) * (x[0] - 2) / 9 + (x[1] + 3) * (x[1] + 3)/ 4 + 5;

}

std::vector<double> test_deriv_n_dim(std::vector<double> x) {

	std::vector<double> t(2);
	t[0] = 2 * (x[0] - 2) / 9; 
	t[1] = (x[1] + 3) / 2;
	return t;

}

int main() {

	std::cout << "F(x)=" << " 3^(-x) + 3^(x-2) + 2"<< std::endl;
	double x_min = grad_descent_1d(test_func, autog, 0, 0.01, 0.00001, true);
	std::cout << "x_min = " << x_min << std::endl;
	std::cout << "F(x_min) = " << test_func(x_min) << std::endl << std::endl;
	auto min = grad_descent(test_func_n_dim, test_deriv_n_dim, std::vector<double>(2, 0) , true);
	for (int i = 0; i < min.size(); i++) {

		std::cout << "x_" << i << " = " << min[i] << std::endl;

	}

	std::cout << "F(x_min) = " << test_func_n_dim(min) << std::endl;
	std::string s;
	std::cout << "F(x) = ";
	std::getline(std::cin, s);
	ArithmeticalExpression expression;
	expression.set_formula(s); 
	min = grad_descent_arithm(expression, std::vector<double>(2, 0), true);
	for (int i = 0; i < min.size(); i++) {

		std::cout << "x_m"<< i <<" = " << min[i] << std::endl;

	}

	std::cout << "F(x_min) = " << expression.count(min) << std::endl;

}
