#include <iostream>
#include <cmath>
using namespace std;
int main() {
	char op;
	double num1;
	double num2;
	double result;
	cout << "enter number 1: ";
	cin >> num1; 
	cout << "Enter either (+ - * /): ";
	cin >> op;
	cout << "enter number 2:";
	cin >> num2;
	switch (op) {
		case '+' :
			result = num1 + num2;
			cout << result << "/n";
			break;
		case '-':
			result = num1 - num2;
			cout << result << "/n";
			break;
		case '*':
			result = num1 * num2;
			cout << result << "/n";
			break;
		case '/':
			result = num1 / num2;
			cout << result << "/n";
			break;
		default:
			cout << " please enter only one of the op above:";
	
	}
	return 0;
}