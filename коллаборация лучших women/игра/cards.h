#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <algorithm>

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
	void put_on_stack(std::vector<int> &s);
};

std::ostream &operator<<(std::ostream &os, const Card &c);
std::ostream &operator<<(std::ostream &os, std::vector<std::string> &v);

extern std::vector<int> Table, Thrown, Thrown_by_bot;
extern std::set<int> queueCards;
extern int ban;

class Bot {
private:
	int number_of_cards;
	std::string difficulty;
	std::vector<Card> cards_in_hand;

public:
	Bot(std::string difficulty);
	int getNumberOfCards();
	std::vector<Card> &getCards();
	void draw_cards(std::set<int> &queueCards, std::vector<Card> &pack);
	void put_on_stack(std::vector<int> &s, int index);
	virtual void make_move();
	void clue_for_friend(std::vector<Card> his_cards);
};

class Player : public Bot {
public:
	Player(std::string difficulty);
	void make_move() override;
};

extern std::vector<Card> pack;
