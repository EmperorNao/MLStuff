#pragma once
#include "ArithmeticalExpression.h"


template <typename type>
class Function {

private:


	std::string formul;
	ArithmeticalExpression expression;
	bool cpp_func = false;
	std::function<type(std::vector<type>)> func;
	size_t number_of_variables;


public:


	Function() {



	}


	Function(std::string _formul) {

		formul = _formul;
		expression.set_formula(_formul);
		number_of_variables = expression.get_variables().size();

	}

	Function(std::function<double(std::vector<double>)> _formul) {

		cpp_func = true;
		func = _formul;

	}


	void set_formul(std::string _formul) {

		formul = _formul;
		expression.set_formula(_formul);
		number_of_variables = expression.get_variables().size();

	}


	std::string get_formul() {

		return expression.get_formula;

	}


	double operator() (double x) {

		if (!cpp_func) {
			return expression.count({ x });
		} 
		else {

			return func({ x });

		}

	}


	double operator() (std::vector<double> x) {

		if (!cpp_func) {
			if (x.size() == number_of_variables) {

				return expression.count(x);

			}
			else {

				return 0;

			}
		}
		else {

			return cpp_func;

		}

	}


	std::string get_variables() {

		if (!cpp_func) {
			return expression.get_variables();
		}

	}


	void set_variables_in_formula(std::string variables_names, std::vector<double> values) {

		if (!cpp_func) {

			expression.set_variables_in_formula(variables_names, values);
			number_of_variables = expression.get_variables().size();

		}

	}

	std::function<type(std::vector<type>)> get_function() {

		if (cpp_func) {

			return func;

		}

	}

	bool is_cpp_func() {

		return cpp_func;

	}


	// Доделать класс








};


typedef Function<double> RationalFunction;