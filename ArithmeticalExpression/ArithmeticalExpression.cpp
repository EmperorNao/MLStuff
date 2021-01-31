#include "ArithmeticalExpression.h"


double _sum(double a, double b) {

	return a + b;

}


double _sub(double a, double b) {

	return a - b;

}


double _mult(double a, double b) {

	return a * b;

}


double _div(double a, double b) {

	return a / b;

}


double _log(double a) {

	return log(a);

}


double _lg(double a) {

	return log10(a);

}


double _opp(double a) {

	return -1*a;

}


double _expo(double a, double b) {

	if ((b > 0) and (trunc(b) == b)) {

		double exp = 1;
		for (int i = b; i > 0; --i) {

			exp *= a;

		}

		return exp;

	}
	else {

		return pow(a, b);

	}

}

double _sin(double a) {

	return sin(a);

}

double _cos(double a) {

	return cos(a);

}

double _tg(double a) {

	return sin(a) / cos(a);

}

double _ln(double a) {

	return log(a);

}

double _pi() {

	return 3.14159265;

}

double _e() {

	return 2.7182818284;

}

// ���������� ������, ���� ������ c �������� ����������� ��������, ����� ���������� ����
bool ArithmeticalExpression::is_postfix_function(std::string c) {

	return false;

}

// ���������� ������, ���� ������ c �������� ���������� ��������, ����� ���������� ����
bool ArithmeticalExpression::is_prefix_function(std::string c) {

	return  unary_operations.find(c) != unary_operations.end();

}

// ���������� ������, ���� ������ c �������� �������� ���������, ����� ���������� ����
bool ArithmeticalExpression::is_binary_operation(std::string c) {

	return  binary_operations.find(c) != binary_operations.end();

}

// ���������� ������, ���� ������ c �������� ����������, ����� ���������� ����
bool ArithmeticalExpression::is_variable(char c) {

	return alphabet.find(c) != std::string::npos;

}

bool ArithmeticalExpression::is_digit(char c) {

	return (((c >= '0') and (c <= '9')) or (c == '.'));

}

// ���������� �������� = 0 - ���� ���������� ����������, >1 - ���� ��������� pos1 > pos2, <1 - ���� ��������� pos1 < pos2
int ArithmeticalExpression::is_more_prioritive(std::string c1, std::string c2) {

	auto op1 = binary_operations[c1];
	auto op2 = binary_operations[c2];

	return (op2.priority - op1.priority);

}

// �������� �������� ��� �������������� ��������� �������, ���������� �������, ������� ����������, ��� ����� ������������ �������
// �������, ������� ������������ � ���������:
// is_variable - �������� �� ������ ����������
// is_postfix_function - �������� �� ������ ����������� ��������
// is_prefix_function - �������� �� ������ ���������� ��������
// is_binary_operation - �������� �� ������ �������� ���������
// is_more_prioritive - ����������, ����� �������� ����� ������������
std::string ArithmeticalExpression::dijkstra_algorithm(std::string s) {

	postfix = s;

	int i = 0; // ������ ����������
	std::string result; // ������ ��� ������ ������������ ���������
	int len = s.length();

	Stack<std::string> stack;

	while (i < len) {

		std::string current;
		current += s[i];
		if (current == " ") {
			result += s[i];

		}
		else if (is_variable(current[0])) {

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

		if (is_digit(current[0])) {

			while ((i + 1 < len) and (is_digit(s[i + 1]))) {

				current += s[i + 1];
				i++;

			}
			result += current;

		}

		if (is_prefix_function(current)) {

			stack.push(current);

		}

		else if (is_postfix_function(current)) {

			stack.push(current);

		}

		else if (current == "(") {

			result += ' ';
			stack.push(current);

		}

		else if (current == ")") {

			result += ' ';
			while (!stack.is_empty() and (stack.top() != "(")) {

				result += stack.pop();

			}

			if (stack.top() != "(") {

				std::cout << "������ - ����������� ��������� �����������, ���� �� ����������� ������\n";
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

// ��������� ���������, ��������� �������� values
double ArithmeticalExpression::count_infix(std::vector<double> values) {

	std::string s = infix;
	std::string t;

	for (int i = 0; i < s.size(); i++) {

		if (is_variable(s[i]) and !(((i > 1) and is_variable(s[i - 1]) and is_variable(s[i])) or ((i + 1 < s.size()) and is_variable(s[i]) and is_variable(s[i + 1])))) {

			int pos = chars_variables.find(s[i]);
			s.erase(i, 1);
			s.insert(i, (" " + std::to_string(values[pos]) + " "));


		}

	}

	Stack<double> stack;
	int i = 0;
	int len = s.size();

	while (i < len) {

		std::string current;
		current += s[i];
		if (current == " ") {

			i++;
			continue;

		}
		if ((is_digit(current[0])) or ((s[i] == '-') and (is_digit(s[i + 1])))) {

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

		if (is_binary_operation(current)) {

			double operand1 = stack.pop();
			if (stack.is_empty()) {

				auto function = unary_operations[current];
				stack.push(function.function(operand1));

			}

			else {

				double operand2 = stack.pop();

				auto function = binary_operations[current];
				stack.push(function.function(operand2, operand1));

			}


		}

		if (is_prefix_function(current)) {

			double operand = stack.pop();

			auto function = unary_operations[current];
			stack.push(function.function(operand));

		}

		i++;

	}

	return stack.top();

}

// ����������� - ������, ��� ��� �����
ArithmeticalExpression::ArithmeticalExpression() {

	//  init all maps

	unary_operation un_op;
	un_op.priority = 2;
	un_op.function = _log;
	unary_operations["log"] = un_op;

	un_op;
	un_op.priority = 2;
	un_op.function = _sin;
	unary_operations["sin"] = un_op;

	un_op;
	un_op.priority = 2;
	un_op.function = _cos;
	unary_operations["cos"] = un_op;

	un_op;
	un_op.priority = 2;
	un_op.function = _tg;
	unary_operations["tg"] = un_op;

	un_op.priority = 1;
	un_op.function = _opp;
	unary_operations["~"] = un_op;

	un_op.priority = 2;
	un_op.function = _ln;
	unary_operations["ln"] = un_op;

	un_op.priority = 2;
	un_op.function = _lg;
	unary_operations["lg"] = un_op;





	binary_operation bin_op;
	bin_op.priority = 1;
	bin_op.function = _expo;
	binary_operations["^"] = bin_op;
	bin_op.priority = 1;
	bin_op.function = _expo;
	binary_operations["$"] = bin_op;

	bin_op.priority = 2;
	bin_op.function = _mult;
	binary_operations["*"] = bin_op;

	bin_op.priority = 2;
	bin_op.function = _div;
	binary_operations["/"] = bin_op;

	bin_op.priority = 3;
	bin_op.function = _sum;
	binary_operations["+"] = bin_op;

	bin_op.priority = 3;
	bin_op.function = _sub;
	binary_operations["-"] = bin_op;

}

// ������ ������� ������� s - ����.��������, ��� ��� ����� �� ��������� � ��������� �����
void ArithmeticalExpression::set_formula(std::string s) {

	postfix = "";
	bool f = false;
	for (int i = 0; i < s.size(); ++i) {

		if (is_digit(s[i]) and not f) {

			f = true;
			postfix += " ";


		}
		if ((not is_digit(s[i])) and f) {

			f = false;
			postfix += " ";

		}
		postfix += s[i];

	}
	infix = dijkstra_algorithm(postfix);

}

// ��������� ��������� ��� values
double ArithmeticalExpression::count(std::vector<double> values) {

	return count_infix(values);

}

std::string ArithmeticalExpression::get_variables() {

	return chars_variables;

}

std::string ArithmeticalExpression::get_formula() {

	return postfix;

}