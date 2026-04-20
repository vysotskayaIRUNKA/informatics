#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Task {
protected:
	int cpuNum;
	int size;

public:
	Task(int cpuNum, int size)
	{
		this->cpuNum = cpuNum;
		this->size = size;
	}

	// На каком ядре процессора выполняется задача
	int getCPU() const { return cpuNum; }

	// Оценка сложности задачи (в попугаях)
	int getSize() const { return size; }
};

class Analyzer {
public:
	// Создать анализатор для системы с numCores ядер
	Analyzer(int numCores)
	{
		this->numCores = numCores;
		load = vector<int>(numCores, 0);
	}

	// Проанализировать текущие задачи
	void analyze(const vector<Task> &tasks)
	{
		for (auto i = 0; i < load.size(); i++)
			load[i] = 0;
		for (auto i = tasks.begin(); i != tasks.end(); i++) {
			load[i->getCPU()] += i->getSize();
		}
	}

	// Сообщить общую нагрузку на заданное ядро
	int getLoadForCPU(int cpuNum) { return load[cpuNum]; }

private:
	int numCores;
	vector<int> load;
};

class ResultsTable {
public:
	// Зарегистрировать новый результат,
	// нас волнуют только баллы, имена пользователей не важны
	void addResult(unsigned int score)
	{
		results.push_back(score);
		sort(results.begin(), results.end());
	}

	// Получить минимальный балл из всех результатов за всё время
	unsigned int getMinScore() const { return results[0]; }

	// Получить, сколько баллов у игрока на заданном месте.
	// Внимание: места нумеруются так, как это принято на турнирах, то есть
	// лучший результат - 1-ое место, за ним 2-ое место и т.д.
	unsigned int getScoreForPosition(unsigned int positionNumber) const
	{
		return results[results.size() - positionNumber];
	}

private:
	vector<unsigned int> results;
};

class Person {
public:
	// Создать человека с ФИО
	Person(string surname = "", string name = "", string middleName = "")
	  : surname(surname), name(name), middleName(middleName)
	{
	}

	string getSurname() const { return surname; }
	string getName() const { return name; }
	string getMiddleName() const { return middleName; }

	void setSurname(string s) { this->surname = s; }
	void setName(string s) { this->name = s; }
	void setMiddleName(string s) { this->middleName = s; }

	bool operator<(Person &second)
	{
		if (this->surname == second.getSurname()) {
			if (this->name == second.getName())
				return this->middleName < second.getMiddleName();
			return this->name < second.getName();
		}
		return this->surname < second.getSurname();
	}

private:
	string surname;
	string name;
	string middleName;
};

std::ostream &operator<<(std::ostream &os, const Person &p)
{
	cout << p.getSurname() << " " << p.getName() << " " << p.getMiddleName();
	return os;
}

std::istream &operator>>(std::istream &is, Person &p)
{
	string surname, name, middleName;
	cin >> surname >> name >> middleName;
	p.setSurname(surname);
	p.setName(name);
	p.setMiddleName(middleName);
	return is;
}

int main()
{
	cout << "Testing I/O" << endl;
	Person p;
	cin >> p;
	cout << p << endl;

	cout << "Testing sorting" << endl;
	vector<Person> people;
	people.push_back(Person("Ivanov", "Ivan", "Ivanovich"));
	people.push_back(Person("Petrov", "Petr", "Petrovich"));
	people.push_back(Person("Ivanov", "Ivan", "Petrovich"));
	people.push_back(Person("Ivanov", "Petr", "Ivanovich"));

	sort(people.begin(), people.end());
	for (vector<Person>::const_iterator it = people.begin(); it < people.end();
	     it++) {
		cout << *it << endl;
	}
}
