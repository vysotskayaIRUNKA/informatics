#include <iostream>
using std::cout, std::endl;

template<typename T>
class subvector {
public:
	subvector()
	{
		mas = NULL;
		top = 0;
		capacity = 0;
	}

	bool push_back(T d)
	{
		if (top == capacity) {
			if (capacity == 0)
				capacity = 100;
			else
				capacity *= 2;
			T *new_mas = new T[capacity];
			for (auto i = 0u; i < top; i++)
				new_mas[i] = mas[i];
			if (mas != NULL)
				delete[] mas;
			mas = new_mas;
		}
		mas[top] = d;
		top++;
		return true;
	}

	T pop_back()
	{
		if (top == 0)
			return 0;
		top--;
		return mas[top];
	}

	void shrink_to_fit() { capacity = top; }

	bool resize(unsigned int new_capacity)
	{
		if (new_capacity < capacity) {
			top = new_capacity;
			capacity = new_capacity;
			return true;
		}
		if (new_capacity == capacity)
			return true;
		T *new_mas = new T[new_capacity];
		for (auto i = 0u; i < top; i++)
			new_mas[i] = mas[i];
		capacity = new_capacity;
		delete[] mas;
		mas = new_mas;
		return true;
	}

	void clear()
	{
		if (mas != NULL) {
			delete[] mas;
			mas = NULL;
		}
		top = 0;
	}

	void print()
	{
		for (unsigned i = 0; i < top; i++)
			cout << mas[i] << " ";
		cout << endl;
	}

	~subvector()
	{
		if (mas != NULL)
			delete[] mas;
		top = 0;
		capacity = 0;
		mas = NULL;
	}

private:
	T *mas;
	unsigned int top;
	unsigned int capacity;
};

int main()
{
	subvector<double> vec;
	vec.push_back(1.76);
	vec.push_back(2.01);
	vec.push_back(3.15);
	vec.push_back(4.1);
	vec.print();
	vec.pop_back();
	vec.pop_back();
	vec.print();
	vec.clear();
	vec.print();
}
