#include <iostream>
#include <cmath>

class Complex {
public:
	Complex(): x(0), y(0) {}
	Complex(int x, int y): x(x), y(y) {}
	Complex(int x): Complex(x, 0) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }

	void print() { std::cout << x << " + " << y << "i" << std::endl; }
	void print_trigonometry()
	{
		double r = sqrt(pow(x, 2) + pow(y, 2));
		double cosf = (double)x / r;
		double sinf = (double)y / r;
		std::cout << "r = " << r << ", cosf = " << cosf << ", sinf = " << sinf
		          << std::endl;
	}
	Complex conjigate() { return Complex(x, -y); }

	Complex operator+(Complex &second)
	{
		return Complex(this->x + second.x, this->y + second.y);
	}
	Complex operator-(Complex &second)
	{
		return Complex(this->x - second.x, this->y - second.y);
	}
	Complex operator*(Complex &second)
	{
		return Complex(this->x * second.x - this->y * second.y,
		               this->x * second.y + this->y * second.x);
	}
	Complex operator*(int n) { return Complex(this->x * n, this->y * n); }

private:
	int x, y;
};
std::istream &operator>>(std::istream &is, Complex &c)
{
	int x, y;
	is >> x >> y;
	c.setX(x);
	c.setY(y);
	return is;
}
std::ostream &operator<<(std::ostream &os, const Complex &c)
{
	os << c.getX() << " + " << c.getY() << "i" << std::endl;
	return os;
}

int main()
{
	int x, y;
	std::cin >> x >> y;
	Complex z(x, y);
	z.print();
	Complex a;
	Complex b(4);
	a.print();
	b.print();
	z.print_trigonometry();
	Complex d;
	std::cin >> d;
	d = d + z;
	std::cout << d;
}
