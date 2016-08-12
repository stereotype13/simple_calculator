#ifndef _EVALUATOR_
#define _EVALUATOR_ 

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace _calc_evaluator {
	template <class T>
	class Evaluator
	{
		vector<string> _parsed_line;
		vector<vector<char>> _operator_stack;
		vector<vector<T>> _argument_stack;

		int _parsed_line_index = 0;
		int _open_parentheses = 0;

		void _load_stacks();
		T _evaluate_stacks();
	public:
		Evaluator();
		~Evaluator();

		T evaluate( const vector<string>& parsed_line );

		/* data */
	};

	//Implementation
	template <class T>
	Evaluator<T>::Evaluator() {
		_operator_stack.push_back(vector<char>());
		_argument_stack.push_back(vector<T>());
	}

	template <class T>
	T Evaluator<T>::_evaluate_stacks() {
		T left, right;
		while ( _operator_stack[_open_parentheses].size() > 0 ) {
			switch ( _operator_stack[_open_parentheses].back() ) {
				//Should only be + or - at this point
				case '+':
				right = _argument_stack[_open_parentheses].back();
				_argument_stack[_open_parentheses].pop_back();

				left = _argument_stack[_open_parentheses].back();
				_argument_stack[_open_parentheses].pop_back();

				_argument_stack[_open_parentheses].push_back( left + right );
				_operator_stack[_open_parentheses].pop_back();
				break;

				case '-':
				right = _argument_stack[_open_parentheses].back();
				_argument_stack[_open_parentheses].pop_back();

				left = _argument_stack[_open_parentheses].back();
				_argument_stack[_open_parentheses].pop_back();

				_argument_stack[_open_parentheses].push_back( left - right );

				_operator_stack[_open_parentheses].pop_back();
				break;
			}
		}
		return _argument_stack[_open_parentheses].back();
	}

	template <class T>
	void Evaluator<T>::_load_stacks() {

		T left, right;
		//loop through each string in parsed_line and put it either on an operator_stack or argument_stack.
		for ( const auto& str : _parsed_line ) {

			bool token_is_operator = true;
			if ( str.size() == 1 /*it may be an operator*/ ) {
				switch ( str[0] /*is a char*/) {
					case '+':
					_operator_stack[_open_parentheses].push_back('+');
					break;

					case '-':
					_operator_stack[_open_parentheses].push_back('-');
					break;

					case '*':
					_operator_stack[_open_parentheses].push_back('*');
					break;

					case '/':
					_operator_stack[_open_parentheses].push_back('/');
					break;

					case '(':
					++_open_parentheses;
					//push new operator and argument stacks
					_operator_stack.push_back( vector<char>() );
					_argument_stack.push_back( vector<T>() );
					break;
					//7-((6-2*13)/(7))
					case ')':
					_argument_stack[_open_parentheses - 1].push_back( _evaluate_stacks() );

					_operator_stack.pop_back();
					_argument_stack.pop_back();
					--_open_parentheses;
					token_is_operator = false;
					break;

					default:
					//str is an argument, not an operator

					token_is_operator = false;
				}	
			}
			else {
				token_is_operator = false;
			}

			if (!token_is_operator) {
				//str is an argument, not an operator
				if (str[0] != ')') {
					istringstream sstream( str );
					T arg;
					sstream >> arg;

					_argument_stack[_open_parentheses].push_back( arg );
				}
				

				//If we've just pushed an argument (as opposed to an operator) onto the stack, and if the last operator pushed onto the operator stack is * or /, execute immediately.
				if ( _argument_stack[_open_parentheses].size() > 1 ) {
					switch ( _operator_stack[_open_parentheses].back() ) {
						case '*':
						right = _argument_stack[_open_parentheses].back();
						_argument_stack[_open_parentheses].pop_back();

						left = _argument_stack[_open_parentheses].back();
						_argument_stack[_open_parentheses].pop_back();

						_argument_stack[_open_parentheses].push_back( left * right );
						_operator_stack[_open_parentheses].pop_back();
						break;

						case '/':
						right = _argument_stack[_open_parentheses].back();
						_argument_stack[_open_parentheses].pop_back();

						left = _argument_stack[_open_parentheses].back();
						_argument_stack[_open_parentheses].pop_back();

						_argument_stack[_open_parentheses].push_back( left / right );
						_operator_stack[_open_parentheses].pop_back();
						break;

						default:
						//do nothing
						break;
					}
				}
			}
			

			
			
			++_parsed_line_index;
		}
		//Done looping through each token. Now, evaluate of args/operators until operator stack is empty.
		
	}

	template <class T>
	T Evaluator<T>::evaluate( const vector<string>& parsed_line ) {
		
		_parsed_line_index = 0;
		_open_parentheses = 0;

		_parsed_line = parsed_line;

		_load_stacks();
		_evaluate_stacks();

		T result = _argument_stack[0].back();
	
		return _argument_stack[0].back();
	}

	template <class T>
	Evaluator<T>::~Evaluator() {}
}

#endif