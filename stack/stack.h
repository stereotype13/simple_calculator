#ifndef _STACK_
#define _STACK_ 

#include <vector>
#include <string>

using namespace std;

namespace calc_stack {
	template <class T>
	class Stack {

		vector<T> _stack;
		string _output_string;

		void constructOutputString();

	public:
		Stack() {}
		void push( const T& t );
		T pop();
		T back();

		string printOutputString();
	};

	template <class T>
	void Stack<T>::constructOutputString() {
		_output_string = "[";

		for ( int i = 0; i < _stack.size(); ++i ) {
			_output_string += "[";
			_output_string += to_string(_stack[i]);
			_output_string += "]";
			_output_string += ( i == _stack.size() - 1 ? "" : ", ");
		}
		_output_string += "]";
	}

	template <class T>
	void Stack<T>::push( const T& t ) {
		_stack.push_back( t );
	}

	template <class T>
	T Stack<T>::pop() {
		T temp = _stack.back();
		_stack.pop_back();
		return temp;
	}

	template <class T>
	T Stack<T>::back() {
		return _stack.back();
	}

	template <class T>
	string Stack<T>::printOutputString() {
		constructOutputString();
		return _output_string;
	}
}

#endif