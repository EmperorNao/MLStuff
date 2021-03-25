#pragma once
#include <functional>
#include <random>
#include "ArithmeticalExpression.h"
#include "Function.h"


typedef Function<double> RealFunction;


// #TODO 
// 1. rewrite config as class

struct config {

	// One of those parameteres is reqierable
	int number_of_variables = 0; // numbers of variables in function - if not stated, will take from points.size()
	std::vector<double> points; // starting points - if stated number of variables, it will be randomed from normal distribution with a = 0, sigma = 1
	// Optional parameteres
	double lr = 0.1; // learning rate
	double eps = 10e-6; // accuracy of counting derrivatives and function
	int MAX_STEPS = INT_FAST32_MAX; // max steps for descent
	int number_steps_to_log = 100; // number steps to log derivatives and function value
	bool logs = false; // is require logs for every number_steps_to_log step
	std::string filename = "con"; // file in which to out logs

};	


// Auto gradient functions
// by using aproximation for derivative by dy/dx = lim eps->0 ( f(x + eps) - f(x) ) / eps
// they can count and return values for derrivatives from all variables
// for 2-dimensional function it will be as :
// dz/dx = lim eps->0 ( f(x + eps, y) - f(x, y) ) / eps
// dz/dy = lim eps->0 ( f(x, y + eps) - f(x, y) ) / eps
std::vector<double> autograd(RealFunction& func, std::vector<double> estimate);


double autograd_1dim(RealFunction& func, double estimate);


double autograd_2ndderiv_1dim(RealFunction& func, double estimate);


std::vector<double> autograd(std::function<double(std::vector<double>)> func, std::vector<double> estimate);


std::vector<double> grad_descent(std::function<double(std::vector<double>)> func, \
	std::function<std::vector<double>(std::vector<double>)> deriv, \
	config config\
);


std::vector<double> grad_descent(std::function<double(std::vector<double>)> func, \
	config config);


std::vector<double> grad_descent(RealFunction& func, config config);