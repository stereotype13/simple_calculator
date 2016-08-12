#ifndef _PARSER_
#define _PARSER_ 

#include <vector>
#include <string>
#include <regex>



using namespace std;

namespace _calc_parser {
	class Parser
	{
		string _input_string;
		vector<string> _output_vector;
		string _output_string;

		void constructOutputString();

	public:
		Parser() {}
		Parser( const string& s ) : _input_string{ /* Remove whitespace */ regex_replace(s , regex("\\s+"), "") } {}
		
		vector<string> parse( const string& s );
		vector<string> parse();
		string printOutputString() const;
		

		~Parser();
	
		/* data */
	};


	//Implementation

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
				if ( temp.size() > 0)
					_output_vector.push_back( temp );
				_output_vector.push_back( string( 1, '+') );
				temp = "";
				break;

				case '-':
				//4--2 --> 4+-
				if ( _output_vector.size() > 0 && _output_vector.back() == "-") {
					_output_vector.pop_back();
					_output_vector.push_back("+");
					break;
				}

				if ( _output_vector.size() > 0 && _output_vector.back() == "+") {
					temp = "-";
					break;
				}

				if ( temp.size() > 0) {
					_output_vector.push_back( temp );		
				}


				if (_output_vector.size() > 0 && _output_vector.back() != "(" && _output_vector.back() != ")" && _output_vector.back() != "*" && _output_vector.back() != "/" && _output_vector.back() != "-")
					_output_vector.push_back( string( 1, '+') );

				_output_vector.push_back("-1");
				_output_vector.push_back( string(1, '*') );
				temp = "";
				break;

				case '*':
				if ( temp.size() > 0 )
					_output_vector.push_back( temp );
				_output_vector.push_back( string( 1, '*') );
				temp = "";
				break;

				case '/':	
				if ( temp.size() > 0)
					_output_vector.push_back( temp );
				_output_vector.push_back( string( 1, '/') );
				temp = "";
				break;

				case '(':	
				_output_vector.push_back( string( 1, '(') );
				temp = "";
				break;

				case ')':	
				if ( temp.size() > 0)
					_output_vector.push_back( temp );
				_output_vector.push_back( string( 1, ')') );
				temp = "";
				break;

				default:
				temp += c;
			
			}
		
		}

		if ( temp.size() > 0 )
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




#endif