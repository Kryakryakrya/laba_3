module;
#include <math.h>
#include <iostream>
export module Math;
namespace Math {
	export class Complex
	{
		double m_re;
		double m_im;
	public:

		friend Complex operator+(const Complex&, const Complex&);
		friend Complex operator-(const Complex&, const Complex&);
		friend Complex operator*(const Complex&, const Complex&);
		friend Complex operator/(const Complex&, const Complex&);
		friend std::ostream& operator<<(std::ostream&, const Complex&);
		friend Complex operator ""i(long double);
		friend Complex operator ""i(unsigned long long);


		Complex() :m_re(0), m_im(0) {}
		Complex(double re) :m_re(re), m_im(0) {}
		Complex(double re, double im) :m_re(re), m_im(im) {}

		Complex static FromExponentialForm(double mod, double arg) {
			return Complex{ mod * cos(arg), mod * sin(arg) };
		}

		Complex static FromAlgebraicForm(double re, double im) {
			return Complex{ re, im };
		}

		double Re() const {
			return m_re;
		}

		double Im() const {
			return m_im;
		}

		double Mod() const {
			return sqrt(m_re * m_re + m_im * m_im);
		}

		double Arg() const {
			return atan2(m_im, m_re);
		}

		explicit operator double() { return m_re; }
		Complex operator-() const
		{
			return Complex(-m_re, -m_im);
		}

		Complex& operator++()
		{
			m_re++;
			return *this;
		}

		Complex operator++(int)
		{
			Complex newObj(*this);
			++(*this);
			return newObj;
		}

		Complex& operator--()
		{
			m_re--;
			return *this;
		}

		Complex operator--(int)
		{
			Complex newObj(*this);
			--(*this);
			return newObj;
		}

		Complex& operator+=(Complex right)
		{
			m_re += right.m_re;
			m_im += right.m_im;
			return *this;
		}

		Complex& operator-=(Complex right)
		{
			m_re -= right.m_re;
			m_im -= right.m_im;
			return *this;
		}

		Complex& operator*=(Complex right)
		{
			double re = m_re * right.m_re - m_im * right.m_im;
			double im = m_re * right.m_im + m_im * right.m_re;
			m_re = re;
			m_im = im;
			return *this;
		}

		Complex& operator/=(Complex right)
		{
			double reLeft = m_re, reRight = right.m_re, re;
			double imLeft = m_im, imRight = right.m_im, im;
			re = (reLeft * reRight + imLeft * imRight) / (reRight * reRight + imRight * imRight);
			im = (reRight * imLeft - reLeft * imRight) / (reRight * reRight + imRight * imRight);
			m_re = re;
			m_im = im;
			return *this;
		}
	};

	export Complex operator+(const Complex& left, const Complex& right)
	{
		return Complex(left.m_re + right.m_re, left.m_im + right.m_im);
	}

	export Complex operator-(const Complex& left, const Complex& right)
	{
		return Complex(left.m_re - right.m_re, left.m_im - right.m_im);
	}

	export Complex operator*(const Complex& left, const Complex& right)
	{
		double re = left.m_re * right.m_re - left.m_im * right.m_im;
		double im = left.m_re * right.m_im + left.m_im * right.m_re;
		return Complex(re, im);
	}

	export Complex operator/(const Complex& left, const Complex& right)
	{
		double reLhs = left.m_re, reRhs = right.m_re, re;
		double imLhs = left.m_im, imRhs = right.m_im, im;
		re = (reLhs * reRhs + imLhs * imRhs) / (reRhs * reRhs + imRhs * imRhs);
		im = (reRhs * imLhs - reLhs * imRhs) / (reRhs * reRhs + imRhs * imRhs);
		return Complex(re, im);
	}

	export Complex operator ""i(unsigned long long im) {
		return Complex(0.0, (double)im);
	}
	export Complex operator ""i(long double im) {
		return Complex(0.0, (double)im);
	}
	export std::ostream& operator<<(std::ostream& stream, const Complex& inst) {
		if (inst.m_im < 0) {
			stream << inst.m_re << inst.m_im << "i";
		}
		else {
			stream << inst.m_re << "+" << inst.m_im << "i";
		}
		return stream;
	}

	export int FindGreatestCommonDivisor(int a, int b) {
		if (a < 0) {
			a *= -1;
		}
		if (b < 0) {
			b *= -1;
		}
		while (a != 0 && b != 0) {
			if (a > b) {
				a %= b;
			}
			else {
				b %= a;
			}
		}
		return a + b;
	}

	export int FindLeastCommonMultiple(int a, int b) {
		return abs(a * b) / FindGreatestCommonDivisor(a, b);
	}

	export class Rational {

		int m_nominator;
		int m_denominator;

		void norm() {
			int gcd = FindGreatestCommonDivisor(m_nominator, m_denominator);
			m_nominator /= gcd;
			m_denominator /= gcd;
			if (m_denominator < 0) {
				m_denominator *= -1;
				m_nominator *= -1;
			}
		}

	public:
		Rational() :m_nominator(0), m_denominator(1) {}
		Rational(int nominator, int denominator) :m_nominator(nominator), m_denominator(denominator) { norm(); }
		Rational(int nominator) :m_nominator(nominator), m_denominator(1) { norm(); }

		int Nominator() const {
			return m_nominator;
		}

		int Denominator() const {
			return m_denominator;
		}

		explicit operator double() const {
			return (double)m_nominator / m_denominator;
		}

		Rational operator-() const {
			return Rational(-m_nominator, m_denominator);
		}


		Rational& operator++()
		{
			m_nominator += m_denominator;
			norm();
			return *this;
		}

		Rational operator++(int)
		{
			Rational newObj(*this);
			++(*this);
			norm();
			return newObj;
		}

		Rational& operator--()
		{
			m_nominator -= m_denominator;
			norm();
			return *this;
		}

		Rational operator--(int)
		{
			Rational newObj(*this);
			--(*this);
			norm();
			return newObj;
		}

		Rational& operator+=(Rational right)
		{
			int denominator = FindLeastCommonMultiple(m_denominator, right.m_denominator);
			int nominator = denominator / m_denominator * m_nominator;
			nominator += denominator / right.m_denominator * right.m_nominator;
			m_nominator = nominator;
			m_denominator = denominator;
			norm();
			return *this;
		}

		Rational& operator-=(Rational right)
		{
			int denominator = FindLeastCommonMultiple(m_denominator, right.m_denominator);
			int nominator = denominator / m_denominator * m_nominator;
			nominator -= denominator / right.m_denominator * right.m_nominator;
			m_nominator = nominator;
			m_denominator = denominator;
			norm();
			return *this;
		}

		Rational& operator*=(Rational right)
		{
			m_nominator *= right.m_nominator;
			m_denominator *= right.m_denominator;
			norm();
			return *this;
		}

		Rational& operator/=(Rational right)
		{
			m_nominator *= right.m_denominator;
			m_denominator *= right.m_nominator;
			norm();
			return *this;
		}
		friend Rational operator+ (const Rational& left, const Rational& right);
		friend Rational operator- (const Rational& left, const Rational& right);
		friend Rational operator* (const Rational& left, const Rational& right);
		friend Rational operator/(const Rational& left, const Rational& right);
		friend bool operator==(const Rational& left, const Rational& right);
		friend bool operator>(const Rational& left, const Rational& right);
		friend bool operator<(const Rational& left, const Rational& right);
		friend bool operator>=(const Rational& left, const Rational& right);
		friend bool operator<=(const Rational& left, const Rational& right);
		friend std::ostream& operator<<(std::ostream& stream, const Rational& instance);
	};


	export Rational operator+ (const Rational& left, const Rational& right) {
		int denominator = FindLeastCommonMultiple(left.m_denominator, right.m_denominator);
		int nominator = denominator / left.m_denominator * left.m_nominator;
		nominator += denominator / right.m_denominator * right.m_nominator;
		return Rational(nominator, denominator);
	}

	export Rational operator-(const Rational& left, const Rational& right)
	{
		int denominator = FindLeastCommonMultiple(left.m_denominator, right.m_denominator);
		int nominator = denominator / left.m_denominator * left.m_nominator;
		nominator -= denominator / right.m_denominator * right.m_nominator;
		return Rational{ nominator, denominator };
	}

	export Rational operator*(const Rational& left, const Rational& right)
	{
		return Rational(left.m_nominator * right.m_nominator, right.m_denominator * left.m_denominator);
	}

	export Rational operator/(const Rational& left, const Rational& right)
	{
		return Rational(left.m_nominator * right.m_denominator, left.m_denominator * right.m_nominator);
	}

	export bool operator==(const Rational& left, const Rational& right)
	{
		return left.m_nominator == right.m_nominator && left.m_denominator == right.m_denominator;
	}

	export bool operator>(const Rational& left, const Rational& right)
	{
		int lcm = FindLeastCommonMultiple(left.m_denominator, right.m_denominator);
		return lcm / left.m_denominator * left.m_nominator > lcm / right.m_denominator * right.m_nominator;
	}
	export bool operator<(const Rational& left, const Rational& right)
	{
		int lcm = FindLeastCommonMultiple(left.m_denominator, right.m_denominator);
		return lcm / left.m_denominator * left.m_nominator < lcm / right.m_denominator * right.m_nominator;
	}
	export bool operator>=(const Rational& left, const Rational& right)
	{
		int lcm = FindLeastCommonMultiple(left.m_denominator, right.m_denominator);
		return lcm / left.m_denominator * left.m_nominator >= lcm / right.m_denominator * right.m_nominator;
	}
	export bool operator<=(const Rational& left, const Rational& right)
	{
		int lcm = FindLeastCommonMultiple(left.m_denominator, right.m_denominator);
		return lcm / left.m_denominator * left.m_nominator <= lcm / right.m_denominator * right.m_nominator;
	}

	export std::ostream& operator<<(std::ostream& stream, const Rational& inst) {
		stream << inst.m_nominator << "/" << inst.m_denominator;
		return stream;
	}

	export Complex f(const Complex& u) {
		Complex a = Complex(0.0, 5.0);
		return u / 3 - 1 / (u + a);
	}

	export Rational f(const Rational& u) {
		Rational a(1, 5);
		return u / 3 - 1 / (u + a);
	}

	export double f(double u) {
		double a = 0.2;
		return u / 3 - 1 / (u + a);
	}
}