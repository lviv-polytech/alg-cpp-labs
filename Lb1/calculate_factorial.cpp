#include <iostream>

using namespace std;

void runFactorialLogic(istream& input, ostream& output) {
    output << "Hello, World!" << endl;

    int p = 1;
    int i = 1;

    // Calculate factorial of 10
    while (i <= 10) {
        p *= i;
        i++; // uncomment this line to fix the infinite loop
    }

    output << "P: " << p << " i: " << i << endl;
}