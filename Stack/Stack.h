#pragma once
#include <iostream>
#include <vector>

// Realisation for Stack interface by vector template
template <class T>
class Stack
{

private:

	std::vector<T> stack;

public:

	Stack() { };
	bool is_empty();
	void push(T x);
	T pop();
	T top();

};

template <typename T>
bool Stack<T>::is_empty() {

	return stack.size() == 0;

}

template <typename T>
void Stack<T>::push(T x) {

	stack.push_back(x);

}

template <typename T>
T Stack<T>::pop() {

	if (!this->is_empty()) {

		auto elem = stack[stack.size() - 1];
		stack.pop_back();
		return elem;

	}

}

template <typename T>
T Stack<T>::top() {

	if (!this->is_empty()) {

		return stack[stack.size() - 1];

	}

}
