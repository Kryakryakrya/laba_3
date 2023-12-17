#include <iostream>
#include <complex>
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
import Math;
using namespace std;
using namespace Math;
int main()
{
    int a;
    cout << "Complex:\n";
    cout << "1 - input the modulus and argument \n2 - input the real and imaginary parts\n";
    cin >> a;

    Complex complex;

    if (a == 1) {
        double mod, arg;
        cout << "Enter the modulus: ";
        cin >> mod;
        cout << "Enter the argument: ";
        cin >> arg;

        complex = Complex::FromExponentialForm(mod, arg);
    }
    else if (a == 2) {
        double re, im;
        cout << "Enter the real part: ";
        cin >> re;
        cout << "Enter the imaginary part: ";
        cin >> im;

        complex = Complex::FromAlgebraicForm(re, im);
    }
    else {
        cout << "Good bay" << endl;
        return 1;
    }
    cout << "Rational:\n";
    cout << "Input nominator denominator\n";
    int nominator, denominator;
    cin >> nominator >> denominator;

    Rational rational(nominator, denominator);

    double userDouble;
    cout << "Enter a real number: ";
    cin >> userDouble;

    cout << "f(" << complex << ") = " << f(complex) << endl;
    cout << "f(" << rational << ") = " << f(rational) << endl;
    cout << "f(" << userDouble << ") = " << f(userDouble) << endl;

    return 0;
}