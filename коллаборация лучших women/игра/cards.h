#include <iostream>
#include <vector>
#include <string>
#include <stack>

class Card {
private:
	int number;
	std::string information;
	int contribution;
	std::vector<std::string> information_for_everyone;

public:
	Card(int number, std::string information, int contribution,
	     std::vector<std::string> information_for_everyone);

	int getNumber() const;
	std::string getInformation() const;
	int getContribution() const;
	std::vector<std::string> const getInformationForEveryone();
	void put_on_stack(std::stack<int> &s);
};

std::ostream &operator<<(std::ostream &os, const Card &c);
