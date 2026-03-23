#include <iostream>

class Rational {
public:
	Rational(int num, int den): num(num), den(den)
	{
		if (den == 0) {
			// bad
		}
	}

	Rational(int value): num(value), den(1) {}

	Rational operator*(Rational other)
	{
		return {num * other.num, den * other.den};
		// это у нас такой список инициализации
		// компилятор смотрит и думает, какой тип тут подразумевается и ставит его
	}

	Rational operator+(const Rational &other)
	{
		return {num * other.den + den * other.num, den * other.den};
	}

	Rational &operator/=(Rational other)
	{
		num *= other.den;
		den *= other.num;
		return *this;
	}

	void print() { std::cout << num << '/' << den << std::endl; }

private:
	int num, den; // numerator, denominator
};
