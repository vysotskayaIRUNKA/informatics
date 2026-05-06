#include "cards.h"

Card::Card(int number, std::string information, int contribution,
           std::vector<std::string> information_for_everyone)
  : number(number), information(information), contribution(contribution),
    information_for_everyone(information_for_everyone)
{
}

int Card::getNumber() const
{
	return number;
}
std::string Card::getInformation() const
{
	return information;
}
int Card::getContribution() const
{
	return contribution;
}
std::vector<std::string> const Card::getInformationForEveryone()
{
	return information_for_everyone;
}
void Card::put_on_stack(std::vector<int> &s)
{
	s.push_back(number);
}

std::ostream &operator<<(std::ostream &os, const Card &c)
{
	os << "Карта №" << c.getNumber() << ":" << std::endl;
	os << c.getInformation();
	return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &v)
{
	for (auto i : v) {
		os << i << "; ";
	}
	return os;
}

std::vector<int> Table;
std::vector<int> Thrown;
std::vector<int> Thrown_by_bot;
std::set<int> queueCards = {2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
int ban = 0;

Bot::Bot(std::string difficulty)
  : number_of_cards(0), difficulty(difficulty), cards_in_hand()
{
}
int Bot::getNumberOfCards()
{
	return number_of_cards;
}
std::vector<Card> &Bot::getCards()
{
	return cards_in_hand;
}
void Bot::draw_cards(std::set<int> &queueCards, std::vector<Card> &pack)
{
	while (number_of_cards < 3 && size(queueCards) > 0) {
		std::vector<int> cardsVector(queueCards.begin(), queueCards.end());
		int randomElement = cardsVector[rand() % cardsVector.size()];
		number_of_cards++;
		cards_in_hand.push_back(pack[randomElement]);
		queueCards.erase(randomElement);
	}
}

void cards_on_the_table();

void Bot::put_on_stack(std::vector<int> &s, int index)
{
	int n = cards_in_hand[index].getNumber();
	cards_in_hand.erase(cards_in_hand.begin() + index);
	s.push_back(n);
	number_of_cards--;
}
void Bot::make_move()
{
	std::cout << "===========================================" << std::endl;
	std::cout << "ОСТАТОК В КОЛОДЕ: " << size(queueCards) << std::endl
	          << "КОЛИЧЕСТВО В СБРОСЕ: " << size(Thrown) << std::endl
	          << "ХОД БОТА" << std::endl;
	cards_on_the_table();
	std::cout << std::endl;
	if (number_of_cards == 0) {
		std::cout << "У меня закончились карты, скипаю" << std::endl;
		return;
	}
	if (difficulty == "easy") {
		if (cards_in_hand[0].getContribution() == 1) {
			std::cout << "Я выложил на стол карту:" << std::endl
			          << cards_in_hand[0] << std::endl;
			put_on_stack(Table, 0);
		}
		else {
			Thrown_by_bot.push_back(cards_in_hand[0].getNumber());
			put_on_stack(Thrown, 0);
			std::cout << "Я сбросил карту в сброс" << std::endl;
		}
		draw_cards(queueCards, pack);
		return;
	}

	else {
		std::cout << "У меня есть карты:" << std::endl;
		for (int i = 0; i < size(cards_in_hand); i++) {
			std::cout << i + 1 << ": ";
			for (auto j : cards_in_hand[i].getInformationForEveryone())
				std::cout << j << "; ";
			std::cout << std::endl << std::endl;
		}
		std::cout << "Какую карту мне использовать?" << std::endl;
		std::cout << "(Если непонятно, сделаю выбор сам (введи -10))" << std::endl;
		int n;
		std::cin >> n;
		while (n != -10 && !(n >= 1 && n <= number_of_cards)) {
			std::cout << "Пожалуйста, введи номер одной из моих карт (1-3) или -10"
			          << std::endl;
			std::cin >> n;
		}
		if (n != -10) {
			std::cout << "Выложить (put) или сбросить (throw)?" << std::endl;
			std::string what_to_do;
			std::cin >> what_to_do;
			while (what_to_do != "put" && what_to_do != "p" &&
			       what_to_do != "throw" && what_to_do != "t") {
				std::cout << "Пожалуйста, введи put, p, throw или t" << std::endl;
				std::cin >> what_to_do;
			}
			if (what_to_do == "put" || what_to_do == "p") {
				std::cout << "Выложена карта:" << std::endl
				          << cards_in_hand[n - 1] << std::endl;
				put_on_stack(Table, n - 1);
				if (cards_in_hand[n - 1].getContribution() == -1)
					ban++;
			}
			else {
				Thrown_by_bot.push_back(cards_in_hand[n - 1].getNumber());
				put_on_stack(Thrown, n - 1);
			}
			draw_cards(queueCards, pack);
			return;
		}
		else {
			n = rand() % number_of_cards;
			int i = rand() % 2;
			if (i == 0) {
				std::cout << "Я выложил на стол карту: " << std::endl
				          << cards_in_hand[n] << std::endl;
				put_on_stack(Table, n);
			}
			else {
				std::cout << "Я сбросил карту" << std::endl;
				Thrown_by_bot.push_back(cards_in_hand[n].getNumber());
				put_on_stack(Thrown, n);
			}
			draw_cards(queueCards, pack);
			return;
		}
	}
}

void Bot::clue_for_friend(std::vector<Card> his_cards)
{
	if (difficulty == "easy") {
		if (his_cards[0].getContribution() == 1) {
			std::cout << "Я бы выложил карту "
			          << his_cards[0].getInformationForEveryone() << std::endl;
			return;
		}
		else
			std::cout << "Я бы сбросил карту "
			          << his_cards[0].getInformationForEveryone() << std::endl;
		return;
	}
	else {
		std::vector<std::string> h = {"выложил", "сбросил"};
		int n = rand() % size(his_cards);
		int wtd = rand() % 2;
		std::cout << "Я бы " << h[wtd] << " карту "
		          << his_cards[n].getInformationForEveryone() << std::endl;
		return;
	}
}

Player::Player(std::string difficulty): Bot(difficulty)
{
}

void cards_on_the_table()
{
	std::cout << "Карты на столе: " << std::endl;
	for (auto i : pack) {
		if (find(Table.begin(), Table.end(), i.getNumber()) != Table.end())
			std::cout << i << std::endl << std::endl;
	}
}

void Player::make_move()
{
	auto &my_hand = Bot::getCards();
	if (size(my_hand) == 0) {
		std::cout << "У вас не осталось карт" << std::endl;
		return;
	}
	std::cout << "===========================================" << std::endl;
	std::cout << "ОСТАТОК В КОЛОДЕ: " << size(queueCards) << std::endl
	          << "КОЛИЧЕСТВО В СБРОСЕ: " << size(Thrown) << std::endl
	          << std::endl;
	cards_on_the_table();
	std::cout << "Твои карты: " << std::endl;
	int n = 1;
	for (auto i : my_hand) {
		std::cout << "(" << n << ")" << " " << i << std::endl;
		n++;
	}
	int count = n - 1;
	std::cout << std::endl << "Твои действия?" << std::endl;
	std::cout << "(1) Мне нужна подсказка" << std::endl
	          << "(2) Сам решу" << std::endl;
	std::cin >> n;
	while (n != 1 && n != 2) {
		std::cout << "Пожалуйста, введите корректный символ!" << std::endl;
		std::cin >> n;
	}
	if (n == 1) {
		clue_for_friend(my_hand);
	}
	std::cout << "С какой картой будешь работать? (введи номер твоей карты "
	             "по "
	             "списку твоих карт: 1, 2 или 3)"
	          << std::endl;
	std::cin >> n;
	while (!(n >= 1 && n <= count)) {
		std::cout << "Пожалуйста, введи номер моей карты (1-3)" << std::endl;
		std::cin >> n;
	}
	std::cout << "Выложишь на стол (put) или в сброс (throw)?" << std::endl;
	std::string what_to_do;
	std::cin >> what_to_do;
	while (what_to_do != "put" && what_to_do != "p" && what_to_do != "throw" &&
	       what_to_do != "t") {
		std::cout << "Пожалуйста, введи put, p, throw или t" << std::endl;
		std::cin >> what_to_do;
	}
	if (what_to_do == "put" || what_to_do == "p") {
		put_on_stack(Table, n - 1);
		if (my_hand[n - 1].getContribution() == -1)
			ban++;
	}
	else {
		put_on_stack(Thrown, n - 1);
	}
	Bot::draw_cards(queueCards, pack);
	std::cout << std::endl << std::endl << std::endl;
}

std::vector<Card>
  pack{Card{9,
            "Вся прислуга очень старалась, чтобы сад и особняк "
            "выглядели безупречно "
            "к визиту сенатора Джонсона",
            1,
            {"прислуга", "сенатора Джонсона"}},
       Card{1,
            "Особняк по центру, на западе роща, севернее неё "
            "сарай с "
            "инструментами, юго-восточнее особняка беседка и "
            "пруд, "
            "северо-восточнее особняка бассейн",
            1,
            {"Карта поместья"}},
       Card{17,
            "По данным судебно-медицинской экспертизы, раны на "
            "лице и на запястье были нанесены после смерти "
            "жертвы",
            1,
            {"Информация", "судебно-медицинской экспертизы, "
                           "раны"}},
       Card{18,
            "В области шеи на теле жертвы найдены отметины, "
            "явно от сдавливания звеньями металлической цепи",
            1,
            {"Информация", "теле", "отметины"}},
       Card{15,
            "Мистер Роквалли заявил, что их старший сын Джеймс "
            "хотел взять его машину, чтобы поехать на "
            "вечеринку в поместье Дунканов всего в 20 минутах "
            "от особбняка Роквалли. Он отказал сыну",
            -1,
            {"Мистер Роквалли", "взять его машину"}},
       Card{31,
            "На карте мы видим пересечение двух дорог: шоссе "
            "163 (идет с севера "
            "на юг) и шоссе 151 (идет с запада на восток). "
            "Вокруг них есть поля и "
            "лес, на северо-западе поместье Роквалли",
            1,
            {"Карта"}},
       Card{22,
            "Всё поместье окружено изгородью. В одном месте в "
            "изгороди была обнаружена дыра, достаточно "
            "большая, чтобы в неё могли пролезть два взрослых "
            "человека.",
            1,
            {"Информация", "изгородью", "дыра"}},
       Card{2,
            "Лицо жертвы было изуродовано. Правая рука была "
            "отделена от тела",
            1,
            {"Информация", "тела"}},
       Card{21,
            "Мистер Роквалли рассказал, что 4 июля они "
            "праздновали День независимости с сенатором "
            "Джонсоном и его семьёй. Обедали они в беседке, а "
            "фейерверки и петарды запускали около пруда",
            1,
            {"Показания", "Мистер Роквалли", "сенатором Джонсоном и его семьёй",
             "пруда"}},
       Card{29,
            "Мы видим шоссе 142 (с запада на восток), около "
            "него в направлении севера стриптиз-клуб, и на "
            "северо-западе виден Джексонвилл, на юго-западе "
            "находится поместье "
            "Роквалли",
            -1,
            {"Карта"}},
       Card{19,
            "С 19:10 до 03:15 движение на шоссе 151 было "
            "прервано из-за автомобильной аварии",
            1,
            {"Информация", "шоссе 151"}},
       Card{14,
            "По словам мистера Роквалли, их собаки пришли в "
            "сильно возбуждённое состояние из-за фейерверков, "
            "поэтому он попросил Розмари запереть их в сарае с "
            "инструментами",
            -1,
            {"Показания", "мистера Роквалли", "собаки",
             "сарае с инструментами"}},
       Card{23,
            "Розмари сказала, что пожалела собак и вместо "
            "того, чтобы запереть их, пошла с ними гулять "
            "около бассейна",
            -1,
            {"Показания", "Розмари", "собак", "бассейна"}},
       Card{7,
            "Горничная рассказала, что Розмри не было, когда "
            "вся семья и гости запускали фейерверки и петарды",
            -1,
            {"Показания", "Горничная", "Розмари не было"}},
       Card{8,
            "Сенатор Джонсон уверен, что некоторые "
            "республиканские сенаторы поддержат его "
            "законопроект о легализации марихуаны",
            -1,
            {"Информация", "Сенатор Джонсон", "марихуаны"}},
       Card{10,
            "Жертва - мужчина, на вид атлетического "
            "телосложения, с многочисленными татуировками на "
            "руках",
            1,
            {"Информация", "Жертва", "вид"}},
       Card{5,
            "Миссис Роквалли сообщила, что Джеймс весь вечер "
            "был "
            "поглощён мобильным телефоном",
            -1,
            {"Показания", "Миссис Роквалли", "Джеймс", "был поглощён"}},
       Card{3,
            "Миссис Роквалли заявила, что ночью были слышны полицейские "
            "сирены "
            "и "
            "вертолёт",
            1,
            {"Показания", "Миссис Роквалли"}},
       Card{28,
            "Мы видим шоссе 113 (с северо-запада на юго-восток), на "
            "юго-западе, "
            "ниже шоссе, видим медвежий заповедник с озером гусей, на "
            "северо-западе "
            "(выше шоссе) видим ранчо Мак-Квинли, на северо-востоке - "
            "поместье "
            "Роквалли",
            -1,
            {"Карта"}},
       Card{32,
            "У фермера Мак-Квинли недавно пропало несколько голов скота. Он "
            "уверен, "
            "что на скот напали медведи",
            -1,
            {"Показания", "Мак-Квинли", "Медведи"}},
       Card{4,
            "Прислуга состоит из повара, садовника, горничной и личного "
            "тренера "
            "миссис Роквалли",
            -1,
            {"Информация", "Прислуга состоит из"}},
       Card{11,
            "На фотографии мы видим камин, в котором лежит сгоревшая одежда",
            1,
            {"Камин"}},
       Card{25,
            "У Роквалли трое детей: Джеймс (16 лет), Розмари (12 лет) и "
            "Диана "
            "(10лет)",
            -1,
            {"Информация", "У Роквалли трое детей"}},
       Card{30,
            "Перекресток двух дорог - шоссе 142 и шоссе 163. Перекресток "
            "делит "
            "изображенеие на четыре части. В первой четверти виден кусочек "
            "тюрьмы, во второй - Грейамвилл (к нему есть съезд с шоссе 142), "
            "в "
            "третьей четверти - виден кусочек поместья Роквалли, в четвертой "
            "- "
            "ничего нет. Сверху север, справа восток.",
            1,
            {"Карта"}},
       Card{12,
            "Мистер и Миссис Роквалли каждую неделю ходят к семейному "
            "психологу",
            -1,
            {"Информация", "Семейному психологу"}},
       Card{20,
            "Сенатор Джонсон приехал на вечеринку без охраны",
            -1,
            {"Информация", "без охраны"}},
       Card{16,
            "Садовник уехал из поместья перед приездом семьи Джонсонов",
            -1,
            {"Информация", "уехал из поместья"}},
       Card{6,
            "На фотографии мы видим сарай с инструментами. На стене висят "
            "три "
            "топора, хотя место есть и для четвертого, в углу стоит лопата с "
            "острым концом, на полу лежит сломанный напильник",
            1,
            {"Сарай с инструментами"}},
       Card{27,
            "Из одежды на жертве были только трусы и носки. Спина убитого "
            "была "
            "зеленой от травы",
            1,
            {"Информация", "Одежды", "Жертве"}},
       Card{13,
            "По словам горничной из шкафа мистера Роквалли исчезли рубашка, "
            "штаны "
            "и пиджак. Больше у обитателей дома ничего не пропало",
            1,
            {"Показания", "Горничной", "не пропало"}},
       Card{26,
            "По данным судебно-медицинской экспертизы - причина смерти: "
            "удушение, "
            "время смерти: между 18:00 и 00:00",
            1,
            {"Информация", "Причина смерти"}},
       Card{24,
            "Горничная рассказала, что на прошлой неделе нашла в комнате "
            "Джеймса "
            "пакетик с марихуаной. По словам Джеймса пакетик принадлежал его "
            "другу",
            -1,
            {"Показания", "Горничная", "Пакетик с марихуаной"}}};
