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

	// ���������� ������, ���� ������ c �������� ����������� ��������, ����� ���������� ����
	bool is_postfix_function(std::string c);

	// ���������� ������, ���� ������ c �������� ���������� ��������, ����� ���������� ����
	bool is_prefix_function(std::string c);

	// ���������� ������, ���� ������ c �������� �������� ���������, ����� ���������� ����
	bool is_binary_operation(std::string c);

	// ���������� ������, ���� ������ c �������� ����������, ����� ���������� ����
	bool is_variable(char c);

	bool is_digit(char c);

	// ���������� �������� = 0 - ���� ���������� ����������, >1 - ���� ��������� pos1 > pos2, <1 - ���� ��������� pos1 < pos2
	int is_more_prioritive(std::string c1, std::string c2);

	double get_coefficient(std::string var);

public:
	// �������� �������� ��� �������������� ��������� �������, ���������� �������, ������� ����������, ��� ����� ������������ �������
	// �������, ������� ������������ � ���������:
	// is_variable - �������� �� ������ ����������
	// is_postfix_function - �������� �� ������ ����������� ��������
	// is_prefix_function - �������� �� ������ ���������� ��������
	// is_binary_operation - �������� �� ������ �������� ���������
	// is_more_prioritive - ����������, ����� �������� ����� ������������
	std::string dijkstra_algorithm(std::string s);

	// ��������� ���������, ��������� �������� values
	double count_infix(std::vector<double> values);

	// ����������� - ������, ��� ��� �����
	ArithmeticalExpression();

	// ������ ������� ������� s - ����.��������, ��� ��� ����� �� ��������� � ��������� �����
	void set_formula(std::string s);

	void set_variables_in_formula(std::string variables_names, std::vector<double> values);

	// ��������� ��������� ��� values
	double count(std::vector<double> values);

	std::string get_variables();

	std::string get_formula();

};
