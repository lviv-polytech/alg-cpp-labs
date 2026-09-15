#include "Params.h"

#include <cmath>
#include <iostream>

using namespace std;

int main() {
    Params pr;

    bool isLoop = true;
    while (isLoop) {
        cout << "0 - Exit\n";
        cout << "Write number (m): ";
        cin >> pr.m;

        if (pr.m == 0) {
            return 0;
        } else if (pr.m > 0) {
            isLoop = false;

        } else {
            cout << "Don't write m < 0\n";
        }
    }

    // Calculate expression (ref)
    calc(pr);

    cout << "z1=" << pr.z1 << "\n" << "z2=" << pr.z2 << endl;
    return 0;
}