#include <ctime>
#include <iostream>
#include <random>

class Subject {
public:
  Subject(std::string name, std::string teacher_name, int longliness_in_minutes,
          int chance_of_luck, std::string *themes, int number_of_themes) {
    this->number_of_themes = number_of_themes;
    this->name = name;
    this->teacher_name = teacher_name;
    this->longliness_in_minutes = longliness_in_minutes;
    this->chance_of_luck = chance_of_luck; // го делать просто int от 0 до 100,
                                           // типа проценты
    this->themes = themes;
  }
  void increase_or_decrease_luck(int cof) {
    this->chance_of_luck +=
        cof; //типа ты обосрался/сделал что-то хорошо на занятии и + карма
  }
  void add_theme(std::string t) {
    this->number_of_themes++;
    std::string *new_list = new std::string[number_of_themes];
    for (int i = 0; i < number_of_themes - 1; i++) {
      new_list[i] = this->themes[i];
    }
    new_list[number_of_themes - 1] = t;
    delete[] this->themes;
    this->themes = new_list;
  }
  void print() {
    std::cout << "Название предмета: " << this->name << std::endl;
    std::cout << "Имя преподавателя: " << this->teacher_name << std::endl;
    std::cout << "Длительность в неделю в минутах: "
              << this->longliness_in_minutes << std::endl;
    std::cout << "Вероятность Вашей удачи: " << this->chance_of_luck
              << std::endl;
    std::cout << "Изучаемые темы: ";
    for (int i = 0; i < this->number_of_themes - 1; i++)
      std::cout << this->themes[i] << ", ";
    std::cout << this->themes[number_of_themes - 1] << std::endl;
  }

protected:
  std::string name;
  std::string teacher_name;
  int longliness_in_minutes;
  int chance_of_luck;
  std::string *themes;
  int number_of_themes;
};

int main() {
  std::mt19937 engine; // эта и следующая строчка для рандома
  engine.seed(std::time(nullptr));

  //проверка subject:
  std::string *themes_1 =
      new std::string[2]{"фильм Барби", "как стать самым крутым в школе"};
  Subject first_one("первяш", "Бобчинский", 10, 50, themes_1, 2);
  first_one.increase_or_decrease_luck(-30);
  first_one.add_theme("как выжить в зомбиапокалипсисе");
  first_one.print();
}
