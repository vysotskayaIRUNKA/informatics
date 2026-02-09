#include <iostream>

class Shape {
public:
	Shape() {}

	double area() { return 0; }

private:
	std::string name;
};

class Rectangle : public Shape {
public:
	Rectangle(double a, double b)
	{
		this->a = a;
		this->b = b;
	}

	double area() { return a * b; }

protected:
	double a, b;
};

class Square : public Rectangle {
	Square(double a)
	{
		this->a = a;
		this->b = a;
	}
};

class Circle : public Shape {
public:
	Circle(double r) { this->r = r; }
	double area() { return 3.14 * r * r; }

private:
	double r;
};
