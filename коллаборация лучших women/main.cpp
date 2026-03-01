#include <ctime>
#include <iostream>

int my_rand() {
  time_t seed;
  time(&seed);
  return (int)seed;
}

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

  ~Subject() { delete[] this->themes; }

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

class PE : public Subject {
public:
  PE(std::string name, std::string teacher_name, int longliness_in_minutes,
     int chance_of_luck, std::string *themes, int number_of_themes,
     std::string mood)
      : Subject(name, teacher_name, longliness_in_minutes, chance_of_luck,
                themes, number_of_themes) {
    if (mood != "awful" && mood != "neutral" && mood != "normal" &&
        mood != "wonderful") {
      std::cout << "Error: mood cannot be " << mood << std::endl;
      return;
    }
    this->mood = mood;
  }
  void set_necessary_visits(int num) { this->necessary_visits = num; }
  void mood_after_lesson() {
    int value = my_rand();
    std::cout << value << " " << value % 4 << std::endl;
    if (value % 4 == 0) {
      mood = "awful";
    };
    if (value % 4 == 1) {
      mood = "neutral";
    }
    if (value % 4 == 2) {
      this->mood = "normal";
    }
    if (value % 4 == 3) {
      this->mood = "wonderful";
    }
    std::cout << mood << std::endl;
  }
  void visit_class() {
    my_visits++;
    std::cout << "Great! You visited class! Now you have visited " << my_visits
              << " classes" << std::endl;
  }
  void mb_skip() {
    if (my_visits < 0.9 * necessary_visits && chance_of_luck < 20) {
      std::cout << "It's bad idea, you have only " << my_visits << " visits"
                << std::endl;
    } else {
      chance_of_luck -= 5;
      std::cout << "OK, you may skip today" << std::endl;
    }
  }

protected:
  int necessary_visits = 25;
  int my_visits = 0;
  std::string mood = "neutral"; //могут быть awful, neutral, normal, wonderful
};

class Chemistry : public PE {
public:
  Chemistry(std::string name, std::string teacher_name,
            int longliness_in_minutes, std::string *themes,
            int number_of_themes)
      : PE(name, teacher_name, longliness_in_minutes, 40, themes,
           number_of_themes, "awful") {}
  void test(std::string t) {
    int value = my_rand();
    int prokatit = value % 100;
    for (int i = 0; i < number_of_themes; i++) {
      if (themes[i] == t) {
        if (prokatit > chance_of_luck) {
          std::cout << "На контрольной тебе не повезло. ";
          if (prokatit % 10 > chance_of_luck) {
            std::cout << "Теперь у тебя незачёт по " << name << std::endl;
            return;
          }
          chance_of_luck -= prokatit % 10;
          std::cout << "Теперь процент твоей удачи: " << chance_of_luck << "%"
                    << std::endl;
          return;
        }
        chance_of_luck += prokatit % 10;
        std::cout << "Ты успешно написал контрольную по " << t
                  << "!. Теперь твой процент удачи: " << chance_of_luck << "%"
                  << std::endl;
        return;
      }
    }
    std::cout << "Ты вообще впервые слышишь о теме сегодняшней контрольной и "
                 "ты завалил её. Теперь твой процент удачи "
              << chance_of_luck - prokatit % 10 << "%" << std::endl;
    chance_of_luck -= prokatit % 10;
  }
};

int main() {
  //проверка subject:
  /*
std::string *themes_1 =
new std::string[2]{"фильм Барби", "как стать самым крутым в школе"};
Subject first_one("первяш", "Бобчинский", 10, 50, themes_1, 2);
first_one.increase_or_decrease_luck(-30);
first_one.add_theme("как выжить в зомбиапокалипсисе");
first_one.print();
  */

  //проверка PE
  /*std::string *themes_2 =
      new std::string[4]{"легкая атлетика", "бассейн", "зал", "коньки"};
  PE fizra("ОФП женские группы", "Юрова", 80, 100, themes_2, 4, "wonderful");
  fizra.mood_after_lesson();
  fizra.print();
  fizra.visit_class();
  for (int i = 0; i < 25; i++) {
    fizra.mb_skip();
  }
  fizra.visit_class();
  fizra.print();*/

  //проверка Chemistry
  std::string *themes_3 = new std::string[2]{"хим связи", "строение атома"};
  Chemistry chem("Неорганика", "бабуля", 90, themes_3, 3);
  chem.set_necessary_visits(6);
  chem.visit_class();
  chem.test("строение атома");
}
