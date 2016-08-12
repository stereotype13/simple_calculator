#include <iostream>
#include "stack.h"

using namespace stack;
using namespace std;

int main(int argc, char const *argv[])
{
	Stack<float> floatStack;
	floatStack.push(4.5);
	floatStack.push(-2.3);
	floatStack.push(2.336);
	cout << floatStack.printOutputString() << endl;
	floatStack.pop();
	cout << floatStack.printOutputString() << endl;
	cout << floatStack.pop() << endl;
	return 0;
}