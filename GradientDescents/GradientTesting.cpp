#include "GradientsTesting.h"
#include "grad.h"


double test_func(double x) {

	return (pow(3, -x) + pow(3, x - 2) + 2);

}


double test_deriv(double x) {

	return (pow(3, -x - 2) * (pow(9, x) - 9) * log(3));

}


double test_func_n_dim(std::vector<double> x) {

	return (x[0] - 2) * (x[0] - 2) / 9 + (x[1] + 3) * (x[1] + 3) / 4 + 5;

}


std::vector<double> test_deriv_n_dim(std::vector<double> x) {

	std::vector<double> t(2);
	t[0] = 2 * (x[0] - 2) / 9;
	t[1] = (x[1] + 3) / 2;
	return t;

}


void TestsGradientDescents::test_simple_gradient_descent_1d() {

	config config;
	config.number_of_variables = 1;

	std::cout << "Finding minimum for expression:" << std::endl;

	std::string s = "3^(~x) + 3^(x-2) + 2";
	std::cout << "F(x) = " << s << std::endl;

	RealFunction f;
	f.set_formul(s);

	std::vector<double> min = grad_descent(f, config);
	std::string chars = f.get_variables();

	for (int i = 0; i < min.size(); i++) {

		std::cout << chars[i] << " = " << min[i] << std::endl;

	}

	std::cout << "F(x_min) = " << f(min) << std::endl;
	std::cout << "Real x_min = 1" << std::endl << "Real F(x_min) = 2.666667" << std::endl << std::endl;

}


void TestsGradientDescents::test_simple_gradient_descent_2d() {

	config config;
	config.number_of_variables = 1;

	std::cout << "Finding minimum for expression:" << std::endl;
	std::cout << "By using built in C++ function for derivative, same as function" << std::endl;
	std::cout << "F(x, y) = " << "(x-2)^2/9 + (y+3)^2/4 + 5" << std::endl;
	config.number_of_variables = 2;

	std::vector<double> min = grad_descent(test_func_n_dim, test_deriv_n_dim, config);
	for (int i = 0; i < min.size(); i++) {

		std::cout << "x_" << i << " = " << min[i] << std::endl;

	}
	std::cout << "F(<min>) = " << test_func_n_dim(min);

	std::cout << std::endl;
	std::cout << "By using autogradient, which aproximates values of derivatives" << std::endl;
	std::cout << "F(x, y) = " << "(x-2)^2/9 + (y+3)^2/4 + 5" << std::endl;

	min = grad_descent(test_func_n_dim, config);
	for (int i = 0; i < min.size(); i++) {

		std::cout << "x_" << i << " = " << min[i] << std::endl;

	}
	std::cout << "F(<min>) = " << test_func_n_dim(min) << std::endl;

	std::cout << "Real x_min = 2, y_min = -3" << std::endl << "Real F(<min>) = 5" << std::endl << std::endl;

}