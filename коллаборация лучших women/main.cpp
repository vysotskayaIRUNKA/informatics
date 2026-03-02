#include <ctime>
#include <iostream>
#include <set>
#include <string>

int my_rand()
{
	time_t seed;
	time(&seed);
	return (int)seed;
}
class Subject {
public:
	Subject(std::string name, std::string teacher_name, int longliness_in_minutes,
	        int chance_of_luck, std::string *themes, int number_of_themes)
	{
		this->number_of_themes = number_of_themes;
		this->name = name;
		this->teacher_name = teacher_name;
		this->longliness_in_minutes = longliness_in_minutes;
		this->chance_of_luck = chance_of_luck; // го делать просто int от 0 до 100,
		                                       // типа проценты
		this->themes = nullptr;
		if (themes != nullptr && number_of_themes > 0) {
			this->themes = new std::string[number_of_themes];
			for (int i = 0; i < number_of_themes; i++) {
				this->themes[i] = themes[i];
			}
		}
	}
	Subject(const Subject &other)
	{
		this->name = other.name;
		this->teacher_name = other.teacher_name;
		this->longliness_in_minutes = other.longliness_in_minutes;
		this->chance_of_luck = other.chance_of_luck;
		this->number_of_themes = other.number_of_themes;

		this->themes = nullptr;
		if (other.themes != nullptr && other.number_of_themes > 0) {
			this->themes = new std::string[other.number_of_themes];
			for (int i = 0; i < other.number_of_themes; i++) {
				this->themes[i] = other.themes[i];
			}
		}
	}
	Subject &operator=(const Subject &other)
	{
		if (this != &other) {
			if (this->themes != nullptr) {
				delete[] this->themes;
				this->themes = nullptr;
			}

			this->name = other.name;
			this->teacher_name = other.teacher_name;
			this->longliness_in_minutes = other.longliness_in_minutes;
			this->chance_of_luck = other.chance_of_luck;
			this->number_of_themes = other.number_of_themes;

			if (other.themes != nullptr && other.number_of_themes > 0) {
				this->themes = new std::string[other.number_of_themes];
				for (int i = 0; i < other.number_of_themes; i++) {
					this->themes[i] = other.themes[i];
				}
			}
		}
		return *this;
	}
	~Subject()
	{
		if (this->themes != nullptr) {
			delete[] this->themes;
			this->themes = nullptr;
		}
	}

	void increase_or_decrease_luck(int cof)
	{
		this->chance_of_luck += cof; // типа ты обосрался/сделал что-то хорошо на
		                             // занятии и + карма
	}

	void add_theme(std::string t)
	{
		this->number_of_themes++;
		std::string *new_list = new std::string[number_of_themes];
		for (int i = 0; i < number_of_themes - 1; i++) {
			new_list[i] = this->themes[i];
		}
		new_list[number_of_themes - 1] = t;
		delete[] this->themes;
		this->themes = new_list;
	}

	void print()
	{
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
	  : Subject(name, teacher_name, longliness_in_minutes, chance_of_luck, themes,
	            number_of_themes)
	{
		if (mood != "awful" && mood != "neutral" && mood != "normal" &&
		    mood != "wonderful") {
			std::cout << "Error: mood cannot be " << mood << std::endl;
			return;
		}
		this->mood = mood;
	}
	void set_necessary_visits(int num) { this->necessary_visits = num; }
	void mood_after_lesson()
	{
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
	void visit_class()
	{
		my_visits++;
		std::cout << "Great! You visited class! Now you have visited " << my_visits
		          << " classes" << std::endl;
	}
	void mb_skip()
	{
		if (my_visits < 0.9 * necessary_visits && chance_of_luck < 20) {
			std::cout << "It's bad idea, you have only " << my_visits << " visits"
			          << std::endl;
		}
		else {
			chance_of_luck -= 5;
			std::cout << "OK, you may skip today" << std::endl;
		}
	}

protected:
	int necessary_visits = 25;
	int my_visits = 0;
	std::string mood = "neutral"; // могут быть awful, neutral, normal, wonderful
};

class Language : public PE {
public:
	Language(std::string name, std::string teacher_name,
	         int longliness_in_minutes, int chance_of_luck)
	  : PE(name, teacher_name, longliness_in_minutes, chance_of_luck, {}, 0,
	       "normal")
	{
	}
	void test(std::string t)
	{
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
		if (chance_of_luck < prokatit % 10) {
			std::cout << "Ты завалил решающую контрольную по " << name
			          << " и тебя отправили в академ" << std::endl;
			return;
		}
		std::cout << "Ты вообще впервые слышишь о теме сегодняшней контрольной и "
		             "ты завалил её. Теперь твой процент удачи "
		          << chance_of_luck - prokatit % 10 << "%" << std::endl;
		chance_of_luck -= prokatit % 10;
	}
};

class Chemistry : public Language {
public:
	Chemistry(std::string name, std::string teacher_name,
	          int longliness_in_minutes, int chance_of_luck)
	  : Language(name, teacher_name, longliness_in_minutes, 40)
	{
	}
	void laba()
	{
		int number_of_necessary_oksids = my_rand() % 7;
		std::string *taken_oksids = new std::string[number_of_necessary_oksids];
		std::set<std::string> our_set;
		for (int i = 0; i < number_of_necessary_oksids; i++) {
			std::string t = std::to_string(my_rand());
			taken_oksids[i] = oksids[t[t.length() - i - 1] - '0'];
			our_set.insert(taken_oksids[i]);
		}
		if (our_set.size() <= 1) {
			std::cout << "ЕЕЕЕ ВАМ ОТМЕНИЛИ ЛАБУ!!! Удача +10: "
			          << chance_of_luck + 10 << "%" << std::endl;
			chance_of_luck += 10;
			return;
		}
		std::string result = results[my_rand() % 4];
		std::cout << "Вы взяли ";
		for (const auto &element : our_set)
			std::cout << element << ", ";
		std::cout << "смешали всё это в огромной колбе, и " << result << ", что";
		int liked_or_disliked = my_rand() % 2;
		if (liked_or_disliked == 0) {
			std::cout << "очень понравилось " << teacher_name << ", и теперь у вас "
			          << chance_of_luck + 10 << "% удачи" << std::endl;
			chance_of_luck += 10;
		}
		else {
			std::cout << "максимально не понравилось " << teacher_name
			          << ", и теперь у вас " << chance_of_luck - 10 << "% удачи"
			          << std::endl;
			chance_of_luck -= 10;
		}
	}

private:
	std::string *oksids =
	  new std::string[10]{"серную кислоту",    "изопропиловый спирт",
	                      "гидроксид натрия",  "азотную кислоту",
	                      "перекись водорода", "катализатор",
	                      "блёстки",           "воду",
	                      "оксид железа",      "какою-то щелочь"};
	std::string *results =
	  new std::string[4]{"всё взорвалось", "выпал осадок", "реакция не произошла",
	                     "мешанина поменяла цвет"};
};

class Linal : public Language {
public:
	Linal(std::string name, std::string teacher_name, int longliness_in_minutes,
	      int chance_of_luck)
	  : Language(name, teacher_name, longliness_in_minutes, chance_of_luck)
	{
		themes =
		  new std::string[4]{"СЛАУ", "Метод Гаусса", "Замена базиса в ЛП", "ЛПП"};
	}
	void exam()
	{
		int value = my_rand();
		std::cout << value << std::endl;
		std::cout << "Вы пришли на экзамен по линалу. Вы достались "
		          << examinators[(value % 10) % 4];
		if (examinators[(value % 10) % 4] == "Умнову") {
			std::cout << ". Поднимем щиты за королеву и пожелаем удачи... "
			             "Вероятность удачи понижается до 15%";
			chance_of_luck = 15;
		}
		if (examinators[(value % 10) % 4] == "Кузнецову") {
			std::cout << ". Поздравляем с уже почти сданным экзаменом! Вероятность "
			             "удачи повышается до 90%";
		}
		std::cout << std::endl;
		std::string st = std::to_string(value);
		std::cout << "Вы получаете билет " << (int)((value % 100) / 10)
		          << ". Он состоит из теоретического вопроса по теме "
		          << themes[(int)((value % 1000) / 100) % 4] << " и задачи по "
		          << themes[(int)((value % 10000) / 1000) % 4] << std::endl;
		int theor_result =
		  chance_of_luck * ((st[4] - '0') * 10 + (st[5] - '0')) % 100 * 1.3;
		std::cout << theor_result << std::endl;
		int task_result =
		  chance_of_luck * ((st[6] - '0') * 10 + (st[7] - '0')) % 100 * 1.3;
		int anti_result = 0;
		if (theor_result > chance_of_luck) {
			std::cout << "Вы провалились в теории..."
			          << examinators_[(value % 10) % 4] << " недоволен." << std::endl;
			anti_result++;
		}
		else {
			std::cout << "Вы успешно ответили теорию!" << std::endl;
		}
		if (task_result > chance_of_luck) {
			std::cout << "Вы провалились в задаче..."
			          << examinators_[(value % 10) % 4] << " недоволен." << std::endl;
			anti_result++;
		}
		else {
			std::cout << "Вы успешно решили задачу!" << std::endl;
		}
		if (anti_result == 2) {
			std::cout << "К сожалению, Вы не смогли сдать экзамен. Вас будут ждать "
			             "на пересдаче"
			          << std::endl;
			return;
		}
		if (anti_result == 1) {
			std::cout << "Несмотря на совершенные ошибки, экзаменатор остался "
			             "доволен "
			             "Вами, и поставил удос. Поздравляем со сдачей экзамена!"
			          << std::endl;
			return;
		}
		std::cout << "Поздравляем Вас с отлом! Терешин очень горд Вами!"
		          << std::endl;
	}

protected:
	std::string *examinators =
	  new std::string[4]{"Умнову", "Терешину", "Кузнецову", "Голубеву"};
	std::string *examinators_ =
	  new std::string[4]{"Умнов", "Терешин", "Кузнецов", "Голубев"};
};

class Informatics : public Subject {
public:
	Informatics(std::string name, std::string teacher_name,
	            int longliness_in_minutes, int chance_of_luck,
	            std::string *themes, int number_of_themes)
	  : Subject(name, teacher_name, longliness_in_minutes, chance_of_luck, themes,
	            number_of_themes)
	{
		code_completed = 0;
		total_code = 8;
		current_project = "";
		programming_language = "C++";
	}

	// Метод для выполнения лабораторной работы
	void do_code(int code_number)
	{
		if (code_number < 1 || code_number > total_code) {
			std::cout << "Некорректный номер лабораторной работы!" << std::endl;
			return;
		}

		int value = my_rand();
		int success_chance = chance_of_luck + (code_completed * 5); // Чем больше
		                                                            // сделано лаб,
		                                                            // тем выше шанс

		std::cout << "Вы делаете лабораторную работу №" << code_number;
		std::cout << " по теме \"" << themes[code_number % number_of_themes]
		          << "\"... ";

		if (value % 100 < success_chance) {
			std::cout << "Успешно!" << std::endl;
			code_completed++;
			chance_of_luck += 3;

			if (code_completed == total_code) {
				std::cout << "ПОЗДРАВЛЯЮ! Вы закрыли все лабораторные работы по "
				          << name << "!" << std::endl;
				chance_of_luck += 30;
			}
		}
		else {
			std::cout << "Неудача... Придется переделывать." << std::endl;
			chance_of_luck -= 5;
		}

		std::cout << "Прогресс: " << code_completed << "/" << total_code << " лаб"
		          << std::endl;
	}

	void submit_project()
	{
		if (code_completed < total_code) {
			std::cout << "Нельзя сдавать курсовой проект, пока не сделаны все лабы! ";
			std::cout << "Осталось: " << (total_code - code_completed) << std::endl;
			return;
		}

		int value = my_rand();
		std::string projects[] = {"Калькулятор", "Телефонный справочник",
		                          "Игру 'Змейка'", "Банковскую систему"};
		current_project = projects[value % 4];

		std::cout << "Вы выбрали тему проекта: " << current_project << std::endl;
		std::cout << "Начинаете писать код";

		for (int i = 0; i < 3; i++) {
			std::cout << ".";
			for (int j = 0; j < 10000000; j++)
				; // Небольшая задержка
		}
		std::cout << std::endl;

		int bugs = (value / 100) % 10; // Количество багов в коде
		std::cout << "В коде обнаружено " << bugs << " багов" << std::endl;

		if (chance_of_luck > bugs * 15) {
			std::cout << "Вы успешно исправили все баги и защитили проект!"
			          << std::endl;
			chance_of_luck += 25;
			std::cout << "Теперь ваш шанс удачи: " << chance_of_luck << "%"
			          << std::endl;
		}
		else {
			std::cout << "Багов оказалось слишком много... Проект отправлен на "
			             "доработку."
			          << std::endl;
			chance_of_luck -= 15;
		}
	}

	// Метод для участия в хакатоне
	void hackathon()
	{
		std::cout << "Участвуете в хакатоне по программированию!" << std::endl;

		int value = my_rand();
		int team_size = (value % 3) + 2; // Размер команды от 2 до 4

		std::cout << "Ваша команда из " << team_size << " человек" << std::endl;

		if (team_size == 2 && chance_of_luck > 50) {
			std::cout << "Вдвоем вы смогли совершить невозможное и ПОБЕДИТЬ!"
			          << std::endl;
			chance_of_luck += 50;
		}
		else if (code_completed > 0 && value % code_completed == 0) {
			std::cout << "Ваш опыт с лабораторными помог занять призовое место!"
			          << std::endl;
			chance_of_luck += 20;
		}
		else {
			std::cout << "Хакатон прошел, но без побед. Получили ценный опыт."
			          << std::endl;
			chance_of_luck += 5;
		}

		std::cout << "Новый шанс удачи: " << chance_of_luck << "%" << std::endl;
	}

	// Переопределенный метод print для добавления специфичной информации
	void preparation_for_work()
	{
		Subject::print(); // Вызов метода родительского класса
		std::cout << "Язык программирования: " << programming_language << std::endl;
		std::cout << "Выполнено лабораторных: " << code_completed << "/"
		          << total_code << std::endl;
		if (!current_project.empty()) {
			std::cout << "Текущий проект: " << current_project << std::endl;
		}
	}

protected:
	int code_completed;               // Количество выполненных лабораторных
	int total_code;                   // Общее количество лабораторных
	std::string current_project;      // Текущий проект
	std::string programming_language; // Язык программирования
};

class VCP : public Informatics {
public:
	VCP(std::string name, std::string teacher_name, int longliness_in_minutes,
	    int chance_of_luck)
	  : Informatics(name, teacher_name, longliness_in_minutes, chance_of_luck,
	                themes, number_of_themes)
	{
		// Переопределяем темы для инженерной практики
		delete[] this->themes; // Освобождаем старый массив тем
		this->number_of_themes = 5;
		this->themes =
		  new std::string[number_of_themes]{"3D-моделирование в Solidworks",
		                                    "Схемотехника и Arduino", "3D-печать",
		                                    "Работа с лазерным станком",
		                                    "Пайка и монтаж электроники"};

		// Специфичные поля для инженерной практики
		this->project_stage = 0; // 0-5 этапов проекта
		this->tools_mastered = 0;
		this->total_tools = 5;
		this->current_device = "";
		this->broken_tools = 0;
		this->has_soldering_experience = false;
	}

	// Метод для работы над проектом
	void work_on_project(std::string device_name)
	{
		if (project_stage == 0) {
			current_device = device_name;
			std::cout << "Вы начинаете работу над устройством: " << current_device
			          << std::endl;
			std::cout << "Этап 1/5: Проектирование в Solidworks..." << std::endl;

			int value = my_rand();
			if (value % 100 < chance_of_luck) {
				std::cout << "Чертеж получился отличный! Можно печатать детали."
				          << std::endl;
				project_stage = 1;
				chance_of_luck += 5;
			}
			else {
				std::cout << "Ошибка в чертеже! Придется переделывать." << std::endl;
				chance_of_luck -= 3;
			}
		}
		else {
			std::cout << "Вы уже работаете над устройством " << current_device
			          << std::endl;
		}
	}

	// Метод для 3D-печати деталей
	void print_details()
	{
		if (project_stage < 1) {
			std::cout << "Сначала нужно сделать чертеж!" << std::endl;
			return;
		}

		if (project_stage >= 2) {
			std::cout << "Детали уже напечатаны!" << std::endl;
			return;
		}

		std::cout << "Запускаем 3D-принтер для печати деталей..." << std::endl;

		int value = my_rand();
		if (value % 10 == 0) {
			std::cout << "О нет! Принтер зажевал пластик! Теряете время на ремонт."
			          << std::endl;
			tools_mastered += 0; // Не увеличиваем
			broken_tools++;
		}
		else if (value % 5 == 0) {
			std::cout << "Детали напечатались криво. Может быть, пригодится?"
			          << std::endl;
			chance_of_luck -= 2;
			project_stage = 2;
		}
		else {
			std::cout << "Детали напечатаны идеально! Можно собирать." << std::endl;
			tools_mastered++;
			chance_of_luck += 5;
			project_stage = 2;
		}

		std::cout << "Освоено инструментов: " << tools_mastered << "/"
		          << total_tools << std::endl;
	}

	// Метод для пайки электроники
	void soldering()
	{
		if (project_stage < 2) {
			std::cout << "Сначала нужно напечатать детали!" << std::endl;
			return;
		}

		if (project_stage >= 3) {
			std::cout << "Пайка уже выполнена!" << std::endl;
			return;
		}

		std::cout << "Берем паяльник и начинаем паять плату..." << std::endl;

		if (!has_soldering_experience) {
			std::cout << "Вы впервые держите паяльник! Это может быть опасно..."
			          << std::endl;
		}

		int value = my_rand();

		if (value % 20 == 0) {
			std::cout << "АЙ! Обожгли палец! Больно, но жить можно." << std::endl;
			chance_of_luck -= 5;
		}
		else if (value % 15 == 0) {
			std::cout << "Вы перегрели микросхему и она сгорела. Нужно купить новую."
			          << std::endl;
			chance_of_luck -= 10;
			broken_tools++;
		}
		else if (value % 10 == 0 && !has_soldering_experience) {
			std::cout << "Неожиданно хорошо! Видимо, у вас талант к пайке!"
			          << std::endl;
			has_soldering_experience = true;
			chance_of_luck += 15;
			project_stage = 3;
			tools_mastered++;
		}
		else if (value % 100 < chance_of_luck) {
			std::cout << "Пайка прошла отлично! Контакты надежные." << std::endl;
			has_soldering_experience = true;
			chance_of_luck += 8;
			project_stage = 3;
			tools_mastered++;
		}
		else {
			std::cout << "Пайка получилась так себе, но работать будет." << std::endl;
			chance_of_luck -= 2;
			project_stage = 3;
		}

		std::cout << "Ваш опыт пайки: "
		          << (has_soldering_experience ? "Есть" : "Нет") << std::endl;
	}

	// Метод для программирования Arduino
	void program_arduino()
	{
		if (project_stage < 3) {
			std::cout << "Сначала соберите устройство!" << std::endl;
			return;
		}

		if (project_stage >= 4) {
			std::cout << "Код уже залит!" << std::endl;
			return;
		}

		std::cout << "Пишем код для Arduino в Arduino IDE..." << std::endl;

		// Используем опыт из Informatics (лабораторные работы)
		if (code_completed > 5) {
			std::cout << "Опыт программирования помогает писать код быстрее!"
			          << std::endl;
			chance_of_luck += 10;
		}

		int value = my_rand();
		int bugs = (value / 100) % 10;

		std::cout << "Написали код. Компиляция..." << std::endl;

		if (bugs > 7) {
			std::cout << "ОШИБКА! В коде куча синтаксических ошибок!" << std::endl;
			std::cout << "Придется переписывать заново." << std::endl;
			chance_of_luck -= 15;
		}
		else if (bugs > 4) {
			std::cout << "Код компилируется, но есть предупреждения." << std::endl;
			std::cout << "Заливаем на плату... Работает через раз." << std::endl;
			chance_of_luck -= 3;
			project_stage = 4;
		}
		else {
			std::cout << "Код идеален! Заливаем на плату... ВСЕ РАБОТАЕТ!"
			          << std::endl;
			chance_of_luck += 12;
			project_stage = 4;
			tools_mastered++;
		}
	}

	// Метод для тестирования устройства
	void test_device()
	{
		if (project_stage < 4) {
			std::cout << "Устройство еще не готово к тестированию!" << std::endl;
			return;
		}

		if (project_stage >= 5) {
			std::cout << "Устройство уже протестировано и работает!" << std::endl;
			return;
		}

		std::cout << "Включаем " << current_device << " для тестирования..."
		          << std::endl;

		int value = my_rand();

		if (broken_tools > 2) {
			std::cout << "Из-за сломанных инструментов устройство работает "
			             "некорректно."
			          << std::endl;
			std::cout << "Придется переделывать с нуля." << std::endl;
			project_stage = 0; // Начинаем заново
			chance_of_luck -= 25;
			return;
		}

		if (value % 100 < chance_of_luck) {
			std::cout << "УРА! Устройство работает идеально! Защита проекта на 5!"
			          << std::endl;
			std::cout << "Преподаватель " << teacher_name << " очень доволен!"
			          << std::endl;
			chance_of_luck += 30;
			project_stage = 5;
		}
		else if (value % 50 < chance_of_luck) {
			std::cout << "Устройство работает, но нестабильно. Тройка за проект."
			          << std::endl;
			chance_of_luck += 5;
			project_stage = 5;
		}
		else {
			std::cout << "Устройство не работает... Что-то пошло не так."
			          << std::endl;
			std::cout << "Попробуйте отладить снова." << std::endl;
			chance_of_luck -= 10;
			project_stage = 3; // Откатываемся к этапу отладки
		}
	}

	// Метод для участия в инженерном конкурсе
	void engineering_competition()
	{
		std::cout << "\n*** ИНЖЕНЕРНЫЙ КОНКУРС ***" << std::endl;
		std::cout << "Вы представляете свой проект: " << current_device
		          << std::endl;

		if (project_stage < 5) {
			std::cout << "Но проект еще не готов! Приходится показывать сырой "
			             "прототип."
			          << std::endl;
		}

		int value = my_rand();
		int jury_score =
		  (tools_mastered * 20) + (code_completed * 5) + (chance_of_luck / 10);

		std::cout << "Оценка жюри: " << jury_score << " баллов" << std::endl;

		if (jury_score > 80) {
			std::cout << "ГРАН-ПРИ! Вы выиграли главный приз - 3D-принтер!"
			          << std::endl;
			tools_mastered++;
			chance_of_luck += 50;
		}
		else if (jury_score > 60) {
			std::cout << "Второе место! Вы получаете набор отверток и паяльник."
			          << std::endl;
			tools_mastered++;
			chance_of_luck += 25;
		}
		else if (jury_score > 40) {
			std::cout << "Третье место! Вам дарят книгу по Arduino." << std::endl;
			chance_of_luck += 10;
		}
		else {
			std::cout << "Участие без победы. Но опыт бесценен!" << std::endl;
			chance_of_luck += 5;
		}
	}

	// Метод для ремонта сломанных инструментов
	void repair_tools()
	{
		if (broken_tools == 0) {
			std::cout << "Все инструменты в порядке!" << std::endl;
			return;
		}

		std::cout << "Чиним сломанные инструменты..." << std::endl;

		int value = my_rand();
		if (value % 100 < chance_of_luck) {
			std::cout << "Успешно починили " << broken_tools << " инструментов!"
			          << std::endl;
			broken_tools = 0;
			chance_of_luck += 10;
		}
		else {
			std::cout << "Неудачный ремонт, инструменты окончательно сломались."
			          << std::endl;
			std::cout << "Придется покупать новые." << std::endl;
			broken_tools = 0;
			total_tools--;
			chance_of_luck -= 15;
		}
	}

	// Переопределяем метод print
	void print()
	{
		Subject::print(); // Вызов метода Subject (обходим Informatics)
		std::cout << "=== Инженерная практика ===" << std::endl;
		std::cout << "Текущее устройство: "
		          << (current_device.empty() ? "не выбрано" : current_device)
		          << std::endl;
		std::cout << "Этап проекта: " << project_stage << "/5" << std::endl;
		std::cout << "Освоено инструментов: " << tools_mastered << "/"
		          << total_tools << std::endl;
		std::cout << "Сломано инструментов: " << broken_tools << std::endl;
		std::cout << "Опыт пайки: " << (has_soldering_experience ? "есть" : "нет")
		          << std::endl;

		// Показываем прогресс по этапам
		std::cout << "Прогресс: ";
		if (project_stage >= 1)
			std::cout << "[Проект] ";
		if (project_stage >= 2)
			std::cout << "[Печать] ";
		if (project_stage >= 3)
			std::cout << "[Пайка] ";
		if (project_stage >= 4)
			std::cout << "[Код] ";
		if (project_stage >= 5)
			std::cout << "[Готово]";
		std::cout << std::endl;
	}

protected:
	int project_stage;             // Этап проекта (0-5)
	int tools_mastered;            // Освоенные инструменты
	int total_tools;               // Всего инструментов
	std::string current_device;    // Текущее устройство
	int broken_tools;              // Сломанные инструменты
	bool has_soldering_experience; // Опыт пайки
};

int main()
{
	// проверка subject:
	/*
	 */

	// проверка PE
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

	// проверка Chemistry
	/*Chemistry chem("Неорганика", "бабуля", 90, 40);
	chem.set_necessary_visits(6);
	chem.visit_class();
	chem.test("строение атома");
	chem.laba();*/

	// проверка Language
	/*Language english("Английский", "Наталья Леонидовна", 180, 80);
	english.add_theme("Past simple");
	english.add_theme("Present Continuous");
	english.test("writing");
	english.test("Past simple");*/

	// проверка Linal
	Linal lin("Линал", "Терешка", 180, 75);
	lin.exam();

	// Проверка класса Informatics
	std::cout << "\n========== ТЕСТИРОВАНИЕ INFORMATICS ==========\n"
	          << std::endl;

	// Создаем массив тем для информатики
	std::string *info_themes =
	  new std::string[4]{"Переменные и типы данных", "Условные операторы",
	                     "Циклы", "Массивы"};

	Informatics programming("Программирование на C++", "Сидоров А.В.", 240, 60,
	                        info_themes, 4);

	std::cout << "--- Начальное состояние ---" << std::endl;
	programming.preparation_for_work();

	std::cout << "\n--- Выполнение кода работ ---" << std::endl;
	// Делаем несколько лабораторных
	programming.do_code(1);
	programming.do_code(2);
	programming.do_code(3);
	programming.do_code(1); // Повторно, для проверки

	std::cout << "\n--- Пытаемся сдать проект до завершения всех кодов ---"
	          << std::endl;
	programming.submit_project();

	std::cout << "\n--- Завершаем оставшиеся работы ---" << std::endl;
	for (int i = 4; i <= 8; i++) {
		programming.do_code(i);
	}

	std::cout << "\n--- Сдаем курсовой проект ---" << std::endl;
	programming.submit_project();

	std::cout << "\n--- Участвуем в хакатоне ---" << std::endl;
	programming.hackathon();

	std::cout << "\n--- Итоговое состояние Informatics ---" << std::endl;
	programming.preparation_for_work();

	// Проверка класса VCP (Engineering Competition)
	std::cout << "\n========== ТЕСТИРОВАНИЕ VCP ==========\n" << std::endl;

	VCP engineering("Инженерная практика", "Петров И.И.", 360, 70);

	std::cout << "--- Начальное состояние ---" << std::endl;
	engineering.print();

	std::cout << "\n--- Работа над проектом 'Умный светофор' ---" << std::endl;
	engineering.work_on_project("Умный светофор");

	std::cout << "\n--- 3D-печать деталей ---" << std::endl;
	engineering.print_details();

	std::cout << "\n--- Пайка электроники ---" << std::endl;
	engineering.soldering();

	std::cout << "\n--- Используем навыки из Informatics (делаем лабы) ---"
	          << std::endl;
	// Показываем, что VCP наследует методы Informatics
	engineering.do_code(1);
	engineering.do_code(2);
	engineering.do_code(3);

	std::cout << "\n--- Программирование Arduino ---" << std::endl;
	engineering.program_arduino();

	std::cout << "\n--- Тестирование устройства ---" << std::endl;
	engineering.test_device();

	std::cout << "\n--- Инженерный конкурс ---" << std::endl;
	engineering.engineering_competition();

	std::cout << "\n--- Ремонт инструментов ---" << std::endl;
	engineering.repair_tools();

	std::cout << "\n--- Финальное состояние VCP ---" << std::endl;
	engineering.print();

	// Дополнительный тест: создаем несколько проектов и проверяем разные сценарии
	std::cout << "\n========== ДОПОЛНИТЕЛЬНЫЙ ТЕСТ: НЕСКОЛЬКО ПРОЕКТОВ "
	             "==========\n"
	          << std::endl;

	VCP engineering2("Робототехника", "Смирнова Е.В.", 400, 50);

	std::cout << "--- Проект 1: Умная теплица ---" << std::endl;
	engineering2.work_on_project("Умная теплица");
	engineering2.print_details();
	engineering2.soldering();

	// Специально ломаем инструменты
	std::cout << "\n--- Имитируем поломку инструментов (вызовем печать несколько "
	             "раз) ---"
	          << std::endl;
	for (int i = 0; i < 3; i++) {
		engineering2.print_details(); // Несколько раз для шанса поломки
	}

	std::cout << "\n--- Пробуем починить ---" << std::endl;
	engineering2.repair_tools();

	std::cout << "\n--- Продолжаем проект ---" << std::endl;
	engineering2.program_arduino();
	engineering2.test_device();

	std::cout << "\n--- Итог второго проекта ---" << std::endl;
	engineering2.print();

	// Проверка взаимодействия с другими классами
	std::cout << "\n========== ТЕСТ ВЗАИМОДЕЙСТВИЯ С ДРУГИМИ КЛАССАМИ "
	             "==========\n"
	          << std::endl;

	// Создаем объекты разных классов
	std::string *pe_themes = new std::string[3]{"Бег", "Плавание", "Силовые"};
	PE physical("Физра", "Сидорова М.П.", 90, 80, pe_themes, 3, "normal");

	Chemistry chem("Органическая химия", "Иванова Л.Д.", 120, 45);

	std::cout << "--- Проверяем независимость объектов ---" << std::endl;
	std::cout << "VCP объект:" << std::endl;
	engineering.preparation_for_work();

	std::cout << "\nPE объект:" << std::endl;
	physical.print();
	physical.mood_after_lesson();

	std::cout << "\nChemistry объект:" << std::endl;
	chem.add_theme("Алканы");
	chem.print();
	chem.laba();

	// проверка PE
	std::string *themes_2 =
	  new std::string[4]{"легкая атлетика", "бассейн", "зал", "коньки"};
	PE fizra("ОФП женские группы", "Юрова", 80, 100, themes_2, 4, "wonderful");
	fizra.mood_after_lesson();
	fizra.print();
	fizra.visit_class();
	for (int i = 0; i < 25; i++) {
		fizra.mb_skip();
	}
	fizra.visit_class();
	fizra.print();

	// проверка Chemistry
	chem.set_necessary_visits(6);
	chem.visit_class();
	chem.test("строение атома");
	chem.laba();

	// проверка Language
	Language english("Английский", "Наталья Леонидовна", 180, 80);
	english.add_theme("Past simple");
	english.add_theme("Present Continuous");
	english.test("writing");
	english.test("Past simple");
}
