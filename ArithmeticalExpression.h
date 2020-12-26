#include <iostream>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm> 
#include <string>
#include <map>
#include "Stack.h"

const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

typedef struct {

	int priority;
	std::function<double(double, double)> function;

} binary_operation;

typedef struct {

	int priority;
	std::function<double(double)> function;

} unary_operation;



class ArithemticalExpression
{

private:


	//std::string chars_binary_operations;
	//std::vector<std::function<double(double, double)>> binary_operations;
	std::map <std::string, binary_operation> binary_operations;

	//std::string chars_unary_operations;
	//std::vector<std::function<double(double)>> unary_operations;
	std::map <std::string, unary_operation> unary_operations;

	std::string chars_variables;

	std::string postfix;
	std::string infix;

	// Возвращает истину, если символ c является постфиксной функцией, иначе возвращает ложь
	bool is_postfix_function(std::string c) {

		return false;

	}

	// Возвращает истину, если символ c является префиксной функцией, иначе возвращает ложь
	bool is_prefix_function(std::string c) {

		return  unary_operations.find(c) != unary_operations.end();

	}

	// Возвращает истину, если символ c является бинарной операцией, иначе возвращает ложь
	bool is_binary_operation(std::string c) {

		return  binary_operations.find(c) != binary_operations.end();

	}

	// Возвращает истину, если символ c является переменной, иначе возвращает ложь
	bool is_variable(char c) {

		return alphabet.find(c) != std::string::npos;

	}

	bool is_digit(char c) {

		return (c >= '0') and (c <= '9');

	}

	// Возвращает значение = 0 - если приоритеты одинаковые, >1 - если приоритет pos1 > pos2, <1 - если приоритет pos1 < pos2
	int is_more_prioritive(std::string c1, std::string c2) {

		auto op1 = binary_operations[c1];
		auto op2 = binary_operations[c2];

		return (op2.priority - op1.priority);

	}

	// Алгоритм Дейкстры для преобразования инфиксной нотации, передаются функции, которые определяют, как будут сравниваться символы
	// Функции, которые используются в алгоритме:
	// is_variable - является ли символ переменной
	// is_postfix_function - является ли символ постфиксной функцией
	// is_prefix_function - является ли символ префиксной функцией
	// is_binary_operation - является ли символ бинарной операцией
	// is_more_prioritive - определяет, какая операция более приоритетная
	std::string dijkstra_algorithm(std::string s) {

		postfix = s;

		int i = 0; // индекс считывания
		std::string result; // строка для записи постфиксного выражения
		int len = s.length();

		Stack<std::string> stack;

		while (i < len) {

			std::string current;
			current += s[i];

			if (is_variable(current[0])) {

				if (i + 1 < len) {

					if (not is_variable(s[i + 1])) {

						result += current;

						if (chars_variables.find(current[0]) == std::string::npos) {

							chars_variables += current[0];

						}

					}
					else {

						while ((i + 1 < len) and is_variable(s[i + 1])) {

							current += s[i + 1];
							i++;

						}

					}

				}
				else {

					result += current;

					if (chars_variables.find(current[0]) == std::string::npos) {

						chars_variables += current[0];

					}

				}
			}
			else if (is_digit(current[0])) {

				while ((i + 1 < len) and (is_digit(s[i + 1]))) {

					current += s[i];
					i++;

				}
				result += current;

			}

			else if (is_postfix_function(current)) {

				result += current;

			}

			else if (is_prefix_function(current)) {

				stack.push(current);

			}

			else if (current == "(") {

				stack.push(current);

			}

			else if (current == ")") {

				while (!stack.is_empty() and (stack.top() != "(")) {

					result += stack.pop();

				}

				if (stack.top() != "(") {

					std::cout << "Ошибка - неправильно поставлен разделитель, либо не согласованы скобки\n";
					return result;

				}

				stack.pop();

			}

			else if (is_binary_operation(current)) {

				while (!stack.is_empty() and ((is_prefix_function(stack.top())) or ((is_binary_operation(stack.top())) and ((is_more_prioritive(stack.top(), current)) >= 0)))) {

					result += stack.pop();

				}

				stack.push(current);

			}

			i++;

		}

		while (!stack.is_empty()) {

			result += stack.pop();

		}

		infix = result;
		std::sort(chars_variables.begin(), chars_variables.end());

		return result;

	}

	// Посчитать выражение, используя значения values
	bool count_infix(std::vector<double> values) {

		std::string s = infix;
		std::string t;

		for (int i = 0; i < s.size(); i++) {

			if (is_variable(s[i]) and (((i + 1 < s.size()) and not is_variable(s[i + 1])) or (i < s.size()))) {

				int pos = chars_variables.find(s[i]);
				s.erase(pos, 1);
				s.insert(pos, std::to_string(values[i]));


			}	

		}

		Stack<double> stack;
		int i = 0;
		int len = s.size();

		while (i < len) {

			std::string current;
			current += s[i];

			if (is_digit(current[0])) {

				while ((i + 1 < len) and is_digit(s[i + 1])) {

					current += s[i + 1];
					i++;

				}
				stack.push(std::stod(current));

			}
			else if (is_variable(current[0])) {
			
				while ((i + 1 < len) and is_variable(s[i + 1])) {

					current += s[i + 1];
					i++;

				}

			
			}

			else if (is_binary_operation(current)) {

				bool operand1 = stack.pop();
				bool operand2 = stack.pop();

				auto function = binary_operations[current];
				stack.push(function.function(operand2, operand1));


			}

			else if (is_prefix_function(current)) {

				bool operand = stack.pop();

				auto function = unary_operations[current];
				stack.push(function.function(operand));

			}

			i++;

		}

		return stack.top();

	}

public:

	// Конструктор - пустой, как моя жизнь
	ArithemticalExpression() {

		//  init all maps
		
	}

	// задать формулу строкой s - посл.действие, так как сразу же переводит в инфиксную форму
	void set_formula(std::string s) {

		postfix = s;
		infix = dijkstra_algorithm(s);

	}

	// посчитать выражение для values
	bool count(std::vector<double> values) {

		return count_infix(values);

	}

	std::string get_formula() {

		return postfix;

	}

};
