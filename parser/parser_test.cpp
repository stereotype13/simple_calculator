#include "parser.h"

#include <iostream>

using namespace std;
using namespace _calc_parser;

int main(int argc, char const *argv[])
{
	//test
	Parser parser("Test");
	vector<string> s1 = parser.parse();

	for ( const auto& i : s1) {
		cout << i << endl;
	}

	
	vector<string> s2 = parser.parse("1 + 2");

	for ( const auto& i : s2) {
		cout << i << endl;
	}

	vector<string> s3 = parser.parse("1 - 2");

	cout << parser.printOutputString() << endl;

	auto s4 = parser.parse("-7 + 5");
	cout << parser.printOutputString() << endl;

	auto s5 = parser.parse("-7 +  - 5 + 2 - 8");
	cout << parser.printOutputString() << endl;

	auto s6 = parser.parse("-7 +  - 5 + 2 - 8 / 2 *  - 5");
	cout << parser.printOutputString() << endl;

	parser.parse("7 - (2 +6)");
	cout << parser.printOutputString() << endl;
	return 0;
}