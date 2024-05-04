#include <iostream>

#include "Fraction.h"
using namespace std;

int main() {
    Fraction f(2, 4), g(1, 3), h(2, 7);

    cout << f << endl;
    cout << g << endl;
    cout << h << endl;
    cout << f + g << endl;
    cout << f - g << endl;
    cout << f * g << endl;
    cout << f / g << endl;
    cout << f + h << endl;

    Fraction z(f + g * h);
    cout << z << endl;

    Fraction x;
    cin >> x;

    cout << (f == x) << endl;

    cout << (f < g) << endl;

    cout << (f > g) << endl;
}