#include <iostream>

using namespace std;

int main() {
	cout << "Hello, World!" << endl;
	
	int p = 1;
	int i = 1;
		
	// Calculate factorial of 10
	while (i <= 10) {
		p *= i;
		i++; // uncomment this line to fix the infinite loop
	}

	cout << "P: " << p << " i: " << i << endl;
	return 0;
}