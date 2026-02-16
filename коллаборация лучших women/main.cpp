#include <iostream>
class Subject {
public:
	Subject()
	{
		this->name = "";
		this->teacher_name = "";
		this->longliness_in_minutes = 0;
		this->chance_of_luck = 50; // го делать просто int от 0 до 100, типа
		                           // проценты
	}
	void set_luck(int cof) { this->chance_of_luck = cof; }

protected:
	std::string name;
	std::string teacher_name;
	int longliness_in_minutes;
	int chance_of_luck;
};

int main()
{
	std::cout << "пошли гулять?" << std::endl;
	std::cout << "ну или погамаем" << std::endl;
	std::cout << "пжпжп" << std::endl;
	std::cout << "господи не заставляй нас ломать репозиторий ещё раз"
	          << std::endl;
}
