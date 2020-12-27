#include "grad.h"


// First version of gradient descent for one-dimensional function - needes buint in C++ function and derivative
/*
double grad_descent_1d(std::function<double(double)> func, std::function<double(double)> deriv,
	double start = NULL, double lr = 0.01, double eps = 0.00001, bool logs = false) {


	std::random_device rd{};
	std::mt19937 gen{ rd() };

	// values near the mean are the most likely
	// standard deviation affects the dispersion of generated values from the mean
	std::normal_distribution<> d;

	if (start != NULL) {

		start = d(gen);

	}

	double estimate = start;
	int steps = 0;
	double functional = func(start);
	double current_functional = 0;

	while (true) {

		estimate = estimate - lr * deriv(estimate);
		if ((logs) and (steps % 500 == 0)) {

			//std::cout << "Deriv = " << abs(deriv(estimate)) << " | " ;
			//std::cout << "Value of function = " << func(estimate) << std::endl;

		}

		if ((abs(deriv(estimate)) < eps) or (abs(functional - func(estimate)) < eps)) {

			break;

		}
		functional = func(estimate);

		steps++;

	}

	return estimate;

}
*/


// Auto gradient functions
// by using aproximation for derivative by dy/dx = lim eps->0 ( f(x + eps) - f(x) ) / eps
// they can count and return value for derrivatives from all variables
// for n-dimensional function it will be as :
// dz/dx = lim eps->0 ( f(x + eps, y) - f(x, y) ) / eps
// dz/dy = lim eps->0 ( f(x, y + eps) - f(x, y) ) / eps
std::vector<double> autograd(ArithmeticalExpression& func, std::vector<double> estimate) {

	auto temporary_increment = estimate;
	auto result = estimate;
	double eps = 0.00001;

	for (int i = 0; i < estimate.size(); i++) {

		temporary_increment = estimate;
		temporary_increment[i] += eps;
		result[i] = (func.count(temporary_increment) - func.count(estimate)) / eps;

	}

	return result;

}


std::vector<double> autograd(std::function<double(std::vector<double>)> func, std::vector<double> estimate) {

	auto temporary_increment = estimate;
	auto result = estimate;
	double eps = 0.00001;

	for (int i = 0; i < estimate.size(); i++) {

		temporary_increment = estimate;
		temporary_increment[i] += eps;
		result[i] = (func(temporary_increment) - func(estimate)) / eps;

	}

	return result;

}


std::vector<double> grad_descent(std::function<double(std::vector<double>)> func, \
	std::function<std::vector<double>(std::vector<double>)> deriv, \
	config config\
) {

	// values near the mean are the most likely
	// standard deviation affects the dispersion of generated values from the mean
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<> d;

	int number_dimensions = config.number_of_variables;
	std::vector<double> start(number_dimensions);

	if (number_dimensions != 0) {

		for (int i = 0; i < number_dimensions; i++) {

			start[i] = d(gen);

		}

	}
	else {

		start = config.points;
		if (start.size() < 1) {

			return std::vector<double>(0);

		}

	}

	std::vector<double> estimate = start;
	int number_of_steps = 0;

	double lr = config.lr;
	double eps = config.eps;
	bool logs = config.logs;

	double functional = func(start);

	while (true) {

		if (number_of_steps >= config.MAX_STEPS) {

			if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

				std::cout << "Number of steps was exceeded" << std::endl;

			}

		}

		auto gradient = deriv(estimate);
		if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

			std::cout << "Parameteres values: " << std::endl;

		}
		for (int i = 0; i < number_dimensions; i++) {

			estimate[i] = estimate[i] - lr * gradient[i];
			if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

				std::cout << "x_" << i << " = " << estimate[i] << std::endl;

			}

		}

		auto current_functional = func(estimate);
		if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

			std::cout << "Last function value = " << functional << ". Current value = " << current_functional << ". Delta = " \
				<< functional - current_functional << std::endl;

		}

		bool f = false;
		for (int i = 0; i < number_dimensions; i++) {

			if (abs(deriv(estimate)[i]) > eps) {

				f = true;

			}

		}

		if (!f or (abs(functional - current_functional) < eps)) {

			break;

		}

		functional = current_functional;
		number_of_steps++;

	}

	return estimate;

}


std::vector<double> grad_descent(std::function<double(std::vector<double>)> func, \
	config config) {

	// values near the mean are the most likely
	// standard deviation affects the dispersion of generated values from the mean
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<> d;

	int number_dimensions = config.number_of_variables;
	std::vector<double> start(number_dimensions);

	if (number_dimensions != 0) {

		for (int i = 0; i < number_dimensions; i++) {

			start[i] = d(gen);

		}

	}
	else {

		start = config.points;
		if (start.size() < 1) {

			return std::vector<double>(0);

		}

	}

	std::vector<double> estimate = start;
	int number_of_steps = 0;

	double lr = config.lr;
	double eps = config.eps;
	bool logs = config.logs;

	double functional = func(start);

	while (true) {

		if (number_of_steps >= config.MAX_STEPS) {

			if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

				std::cout << "Number of steps was exceeded" << std::endl;

			}

		}

		auto gradient = autograd(func, estimate);
		if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

			std::cout << "Parameteres values: " << std::endl;

		}
		for (int i = 0; i < number_dimensions; i++) {

			estimate[i] = estimate[i] - lr * gradient[i];
			if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

				std::cout << "x_" << i << " = " << estimate[i] << std::endl;

			}

		}

		auto current_functional = func(estimate);
		if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

			std::cout << "Last function value = " << functional << ". Current value = " << current_functional << ". Delta = " \
				<< functional - current_functional << std::endl;

		}

		bool f = false;
		for (int i = 0; i < number_dimensions; i++) {

			if (abs(autograd(func, estimate)[i]) > eps) {

				f = true;

			}

		}

		if (!f or (abs(functional - current_functional) < eps)) {

			break;

		}

		functional = current_functional;
		number_of_steps++;

	}

	return estimate;

}


std::vector<double> grad_descent(ArithmeticalExpression& func, config config) {

	std::random_device rd{};
	std::mt19937 gen{ rd() };

	// values near the mean are the most likely
	// standard deviation affects the dispersion of generated values from the mean
	std::normal_distribution<> d;

	int number_dimensions = config.number_of_variables;
	std::vector<double> start(number_dimensions);

	if (number_dimensions != 0) {

		for (int i = 0; i < number_dimensions; i++) {

			start[i] = d(gen);

		}

	}
	else {

		start = config.points;
		if (start.size() < 1) {

			return std::vector<double>(0);

		}

	}

	std::vector<double> estimate = start;
	int number_of_steps = 0;

	double lr = config.lr;
	double eps = config.eps;
	bool logs = config.logs;

	double functional = func.count(start);

	while (true) {

		if (number_of_steps >= config.MAX_STEPS) {

			if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

				std::cout << "Number of steps was exceeded" << std::endl;

			}

		}

		auto gradient = autograd(func, estimate);
		if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

			std::cout << "Parameteres values: " << std::endl;

		}
		for (int i = 0; i < number_dimensions; i++) {

			estimate[i] = estimate[i] - lr * gradient[i];
			if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

				std::cout << "x_" << i << " = " << estimate[i] << std::endl;

			}

		}

		auto current_functional = func.count(estimate);
		if ((logs) and (number_of_steps % config.number_steps_to_log == 0)) {

			std::cout << "Last function value = " << functional << ". Current value = " << current_functional << ". Delta = " \
				<< functional - current_functional << std::endl;

		}

		bool f = false;
		for (int i = 0; i < number_dimensions; i++) {

			if (abs(autograd(func, estimate)[i]) > eps) {

				f = true;

			}

		}

		if (!f or (abs(functional - current_functional) < eps)) {

			break;

		}
		functional = current_functional;
		number_of_steps++;

	}

	return estimate;

}