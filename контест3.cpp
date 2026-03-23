#include <iostream>
#include <string>
class Vector2D {
public:
	// Конструкторы
	Vector2D(int x, int y): x(x), y(y) {}
	Vector2D(): Vector2D(0, 0) {}

	// Деструктор
	~Vector2D()
	{
		x = 0;
		y = 0;
	}

	// Получение координат
	int getX() const { return x; }
	int getY() const { return y; };

	// Задание координат
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }

	// Перегруженный оператор - сравнение двух векторов на равенство
	bool operator==(const Vector2D &v2) const { return x == v2.x && y == v2.y; }

	// Ещё один перегруженный оператор - неравенство векторов
	// Да, это отдельный оператор! Хинт - настоящие джедаи смогут для !=
	// использовать уже написанное ==
	bool operator!=(const Vector2D &v2) const { return !(*this == v2); }

	// Сумма двух векторов, исходные вектора не меняются, возвращается новый
	// вектор
	Vector2D operator+(const Vector2D &v2) const { return {x + v2.x, y + v2.y}; }

	// Вычитание векторов, исходные вектора не меняются, возвращается новый вектор
	Vector2D operator-(const Vector2D &v2) const { return {x - v2.x, y - v2.y}; }

	// Оператор умножения вектора на скаляр, исходный вектор не меняется,
	// возвращается новый вектор
	Vector2D operator*(const int a) const { return {x * a, y * a}; }

private:
	int x, y;
};

// Оператор умножения скаляра на вектор, исходный вектор не меняется,
// возвращается новый вектор Неожиданно, правда? Умножение скаляра на вектор -
// это отдельный оператор, причём описанный *вне* класса.
Vector2D operator*(int a, const Vector2D &v)
{
	return {v.getX() * a, v.getY() * a};
}

// Вывод вектора, ожидается строго в формате (1; 1)
std::ostream &operator<<(std::ostream &os, const Vector2D &v)
{
	os << '(' << v.getX() << "; " << v.getY() << ')';
	return os;
}

// Чтение вектора, читает просто две координаты без хитростей
std::istream &operator>>(std::istream &is, Vector2D &v)
{
	int x, y;
	is >> x >> y;
	v.setX(x);
	v.setY(y);
	return is;
}

class VectorN {
public:
	// Конструктор вектора размерности n
	VectorN(unsigned int n): n(n) { vec = new int(n); }

	// Деструктор
	~VectorN()
	{
		n = 0;
		delete vec;
	}

	// Получение размерности вектора
	unsigned getSize() const { return n; }

	// Получение значения i-ой координаты вектора,
	// i находится в диапазоне от 0 до n-1
	int getValue(unsigned int i) const { return vec[i]; }

	// Задание значения i-ой координаты вектора равным value,
	// i находится в диапазоне от 0 до n-1
	void setValue(unsigned int i, int value) { vec[i] = value; }

	/*
	 * Далее реализуйте перегруженные операторы
	 */

	// Оператор == проверяет два вектора на равенство,
	// равны они, если строго равны всех их координаты
	bool operator==(VectorN other)
	{
		bool res = true;
		for (auto i = 0u; i < n; i++)
			if (vec[i] != other.vec[i])
				res = false;
		return res;
	}

	// Оператор != проверяет два вектора на неравенство,
	// они не равны, если хотя бы одна координата отличается
	bool operator!=(VectorN other) { return (!(*this == other)); }

	// Оператор + складывает два вектора покоординатно,
	// возвращает результат как новый экземпляр вектора
	VectorN operator+(const VectorN other) const
	{
		VectorN res(n);
		for (auto i = 0u; i < n; i++)
			res.setValue(i, vec[i] + other.vec[i]);
		return res;
	}

	// Оператор * умножает вектор на скаляр типа int покоординатно,
	// возвращает результат как новый экземпляр вектора.
	// Умножение должно работать при любом порядке операндов.

private:
	unsigned int n;
	int *vec;
};

VectorN operator*(int a, VectorN vec)
{
	VectorN res(vec.getSize());
	for (auto i = 0u; i < vec.getSize(); i++)
		res.setValue(i, vec.getValue(i) * a);
	return res;
}
VectorN operator*(VectorN vec, int a)
{
	VectorN res(vec.getSize());
	for (auto i = 0u; i < vec.getSize(); i++)
		res.setValue(i, vec.getValue(i) * a);
	return res;
}

class Student {
public:
	// Задать имя студента
	void setName(std::string name)
	{
		this->name = name;
		this->score = 0;
	}

	// Указать количество баллов за контрольную
	void setScore(unsigned int score) { this->score = score; }

	// Получить имя студента
	std::string getName() const { return this->name; }

	// Получить количество баллов студента
	unsigned int getScore() const { return this->score; }

private:
	std::string name;
	unsigned int score;
};
