#include "parser.h"

namespace parser {

	void Parser::constructOutputString() {
		_output_string = "[";

		for ( int i = 0; i < _output_vector.size(); ++i ) {
			_output_string += "[";
			_output_string += _output_vector[i];
			_output_string += "]";
			_output_string += ( i == _output_vector.size() - 1 ? "" : ", ");
		}
		_output_string += "]";
	}

	vector<string> Parser::parse( const string& s ) {
		_output_vector.clear();
		//Remove whitespace
		_input_string = regex_replace(s , regex("\\s+"), "");

		string temp = "";

		for ( const auto& c : _input_string ) {
			switch ( c ) {
				case '+':
				_output_vector.push_back( temp );
				_output_vector.push_back( string( 1, '+') );
				temp = "";
				break;

				case '-':
				//Add a negative number
				if ( temp.size() == 0 ) {
					temp += "-";
					break;
				}
				
				_output_vector.push_back( temp );							
				_output_vector.push_back( string( 1, '+') );
				temp = "-";
				break;

				case '*':
				_output_vector.push_back( temp );
				_output_vector.push_back( string( 1, '*') );
				temp = "";
				break;

				case '/':	
				_output_vector.push_back( temp );
				_output_vector.push_back( string( 1, '/') );
				temp = "";
				break;

				default:
				temp += c;
			
			}
		}
		_output_vector.push_back( temp );
		constructOutputString();
		return _output_vector;
	}

	vector<string> Parser::parse() {
		return parse( _input_string );
	}

	string Parser::printOutputString() const {
		return _output_string;
	}

	Parser::~Parser() {}
}