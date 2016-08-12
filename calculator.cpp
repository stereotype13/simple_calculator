#include <iostream>
#include <string>
#include "parser/parser.h"
#include "evaluator/evaluator.h"

using namespace std;

int main(int argc, char const *argv[])
{
	string input_line;
	_calc_evaluator::Evaluator<double> evaluator;
	_calc_parser::Parser parser;
	while (true) {
		cout << ">> ";
		getline( cin, input_line );
		parser.parse( input_line );
		cout << parser.printOutputString() << "\n" << endl;
		cout << evaluator.evaluate( parser.parse( input_line ) ) << "\n" << endl;

	}
	return 0;
}