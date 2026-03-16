#include <iostream>
#include <vector>
#include <chrono>

const size_t CONST_SIZE = 10000000;

using clock_type = std::chrono::steady_clock;

class Timer { // что-то тут насрано, у меня оч большие числа
public:
	Timer() { auto start = clock_type::now(); }
	~Timer()
	{
		auto finish = clock_type::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish -
		                                                                   start)
		               .count()
		          << std::endl;
	}

private:
	clock_type::time_point start;
};

// полиморфизм по ?времени выполнения?
/*void print(int x)
{
  std::cout << x << std::endl;
}
void print(double x)
{
  std::cout << x << std::endl;
}

int main()
{
  int a = 5;
  double b = 42.1;
  print(a);
  print(b);
}*/

void sqr(int *px)
{
	(*px) *= (*px);
}

void sqr(int &x) // тут мы короче ссылочку сделали и всё тип-топ
{
	x *= x;
}

size_t get_size(const std::vector<int> nums)
{
	// nums.push_back(42); -- не получится, т.к. nums константный
	return nums.size();
}

int main()
{
	int a = 5;
	sqr(a);
	std::cout << a << std::endl;

	size_t s;
	std::vector<int> nums;
	for (auto i = 0; i < 1000; i++) {
		nums.push_back(i);
	}
	{
		Timer t;
		auto s = get_size(nums);
	}
	std::cout << "size is " << s << std::endl;
}
