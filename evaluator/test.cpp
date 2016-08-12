#include <iostream>
#include <string>

#include "evaluator.h"
#include "../parser/parser.h"

using namespace _calc_parser;
using namespace _calc_evaluator;
using namespace std;

int main(int argc, char const *argv[])
{
	Evaluator<double> evaluator;
	Parser parser;

	cout << evaluator.evaluate( parser.parse("-7 + 5") ) << endl; //-2
	cout << evaluator.evaluate( parser.parse("-7 + 5 * 3") ) << endl; //8

	parser.parse("-7 + 5 * 3 * (13 -4)");
	cout << parser.printOutputString() << endl;
	cout << evaluator.evaluate( parser.parse("-7 + 5 * 3 * (13 -4)") ) << endl; //128

	parser.parse("(13 + -4*(2-8)/5)/7+2");
	cout << parser.printOutputString() << endl;
	cout << evaluator.evaluate( parser.parse("(13 + -4*(2-8)/5)/7+2") ) << endl; //4.54285714286

	parser.parse("7 - (2 + 6)");
	cout << parser.printOutputString() << endl;
	cout << evaluator.evaluate( parser.parse("7 - (2 + 6)") ) << endl; //-1

	
	parser.parse("7-((6-2*13)/(7))");
	cout << parser.printOutputString() << endl;
	cout << evaluator.evaluate( parser.parse("7-((6-2*13)/(7))") ) << endl; //9.85714285714

	parser.parse("7-((6-2*13)/(7)-2)-3");
	cout << parser.printOutputString() << endl;
	cout << evaluator.evaluate( parser.parse("7-((6-2*13)/(7)-2)-3") ) << endl; //8.85714285714
	return 0;
}