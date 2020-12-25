#pragma once
#include <functional>
#include <random>

const int num_steps_to_log = 500;

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
	const int MAX_STEPS = INT_FAST32_MAX;
	double functional = func(start);
	double current_functional = 0;

	while (true) {

		estimate = estimate - lr * deriv(estimate);
		if ((logs) and (steps % num_steps_to_log == 0)) {

			std::cout << "Deriv = " << abs(deriv(estimate)) << " | " ;
			std::cout << "Value of function = " << func(estimate) << std::endl;

		}

		if ((abs(deriv(estimate)) < eps) or (abs(functional - func(estimate)) < eps)) {

			break;

		}
		functional = func(estimate);

		steps++;

	}

	return estimate;

}

std::vector<double> grad_descent(std::function<double(std::vector<double>)> func, std::function<std::vector<double>(std::vector<double>)> deriv,
	std::vector<double> start, bool need_start = false, double lr = 0.1, double eps = 0.00001, bool logs = false) {

	std::random_device rd{};
	std::mt19937 gen{ rd() };

	// values near the mean are the most likely
	// standard deviation affects the dispersion of generated values from the mean
	std::normal_distribution<> d;

	int number_dimensions = start.size();

	if (need_start == NULL) {

		for (int i = 0; i < number_dimensions; i++) {

			start[i] = d(gen);

		}

	}

	std::vector<double> estimate = start;
	int steps = 0;
	const int MAX_STEPS = INT_FAST32_MAX;
	double functional = func(start);

	while (true) {
		
		auto gradient = deriv(estimate);
		for (int i = 0; i < number_dimensions; i++) {

			estimate[i] = estimate[i] - lr * gradient[i];
			std::cout << "x_" << i << " = " << estimate[i] << std::endl;

		}

		bool f = false;
		for (int i = 0; i < number_dimensions; i++) {

			if (abs(deriv(estimate)[i]) > eps) {

				f = true;

			}

		}
		std::cout << "Func = " << functional << ". Current = " << func(estimate) << std::endl;

		if (!f or (abs(functional - func(estimate)) < eps)) {

			break;

		}
		functional = func(estimate);

	}

	return estimate;

}