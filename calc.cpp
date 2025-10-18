#include <iostream>
#include <cmath>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;
int main() {
	void *handle = dlopen("./libladd.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "Failed to load libladd.so: %s\n", dlerror());
      
    } else {
        fprintf(stderr, "libladd.so loaded successfully\n");
    }

    
    printf("Starting calculator...\n");
	printf("waiting 5 seconds... \n");
	sleep(5);
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
			cout << result << "\n";
			break;
		case '-':
			result = num1 - num2;
			cout << result << "\n";
			break;
		case '*':
			result = num1 * num2;
			cout << result << "\n";
			break;
		case '/':
			result = num1 / num2;
			cout << result << "\n";
			break;
		default:
			cout << " please enter only one of the op above:";
	
	}
	return 0;
}