#include <iostream>
#include <list>
#include <forward_list>

int main()
{
	std::list<int> l;
	l.push_back(3);
	l.push_front(1);
	l.insert(std::next(l.begin()), 2);

	for (auto item : l) {
		std::cout << item;
	}
}
