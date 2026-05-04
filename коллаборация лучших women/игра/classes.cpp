#include "cards.h"

std::vector<int> const punishment = {4,  5,  7,  8,  12, 14, 15, 16,
                                     20, 23, 24, 25, 28, 29, 32};
std::vector<int> const story = {26, 18, 19, 30, 31, 22, 10, 21, 1,
                                6,  2,  27, 17, 3,  13, 11, 9};

int main()
{
	std::stack<int> Table;
	std::stack<int> Thrown;

	Card c9{9,
	        "Вся прислуга очень старалась, чтобы сад и особняк выглядели "
	        "безупречно к визиту сенатора Джонсона",
	        1,
	        {"прислуга", "сенатора Джонсона"}};
}
