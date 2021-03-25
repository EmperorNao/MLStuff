#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm> 
#include <string>
#include <map>
#include "Stack.h"

// TODO: comment and refactore this class

const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


typedef struct {

	int priority;
	std::function<double(double, double)> function;

} binary_operation;

typedef struct {

	int priority;
	std::function<double(double)> function;

} unary_operation;



class ArithmeticalExpression
{

private:


	//std::string chars_binary_operations;
	//std::vector<std::function<double(double, double)>> binary_operations;
	std::map<std::string, binary_operation> binary_operations;

	//std::string chars_unary_operations;
	//std::vector<std::function<double(double)>> unary_operations;
	std::map<std::string, unary_operation> unary_operations;

	std::string chars_variables;

	std::string postfix;
	std::string infix;

	// Возвращает истину, если символ c является постфиксной функцией, иначе возвращает ложь
	bool is_postfix_function(std::string c);

	// Возвращает истину, если символ c является префиксной функцией, иначе возвращает ложь
	bool is_prefix_function(std::string c);

	// Возвращает истину, если символ c является бинарной операцией, иначе возвращает ложь
	bool is_binary_operation(std::string c);

	// Возвращает истину, если символ c является переменной, иначе возвращает ложь
	bool is_variable(char c);

	bool is_digit(char c);

	// Возвращает значение = 0 - если приоритеты одинаковые, >1 - если приоритет pos1 > pos2, <1 - если приоритет pos1 < pos2
	int is_more_prioritive(std::string c1, std::string c2);

	double get_coefficient(std::string var);

public:
	// Алгоритм Дейкстры для преобразования инфиксной нотации, передаются функции, которые определяют, как будут сравниваться символы
	// Функции, которые используются в алгоритме:
	// is_variable - является ли символ переменной
	// is_postfix_function - является ли символ постфиксной функцией
	// is_prefix_function - является ли символ префиксной функцией
	// is_binary_operation - является ли символ бинарной операцией
	// is_more_prioritive - определяет, какая операция более приоритетная
	std::string dijkstra_algorithm(std::string s);

	// Посчитать выражение, используя значения values
	double count_infix(std::vector<double> values);

	// Конструктор - пустой, как моя жизнь
	ArithmeticalExpression();

	// задать формулу строкой s - посл.действие, так как сразу же переводит в инфиксную форму
	void set_formula(std::string s);

	void set_variables_in_formula(std::string variables_names, std::vector<double> values);

	// посчитать выражение для values
	double count(std::vector<double> values);

	std::string get_variables();

	std::string get_formula();

};
