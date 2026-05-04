#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class HomeworkChooser {
private:
	map<string, vector<string>> m;
	map<int, string> priority;

public:
	// Добавить новое домашнее задание
	void add_homework(const std::string &task, const std::string &subject)
	{
		m[subject].insert(m[subject].begin(), task);
	}

	// Добавить учебный предмет и степень его важности для Григоригоря
	void set_priority(const std::string &subject, unsigned prio)
	{
		priority[prio] = subject;
	}
	// Получить имя следующего задания для выполнения
	std::string get_next_task()
	{
		bool is_any_task = false;
		for (auto i : m) {
			if (i.second.size() != 0) {
				is_any_task = true;
				break;
			}
		}
		if (!is_any_task) {
			return "have a rest";
		}
		int max_priority = -1000;
		string subj;
		for (auto p : priority) {
			if (p.first > max_priority && m[p.second].size() != 0) {
				max_priority = p.first;
				subj = p.second;
			}
		}
		string ans = "";
		for (auto &i : m) {
			if (i.first == subj && !i.second.empty()) {
				ans = i.second.back();
				i.second.pop_back();
				return ans;
			}
		}

		return "have a rest";
	}
}

;

int main()
{
	HomeworkChooser hc;
	int n_tasks;
	cin >> n_tasks;
	for (int i = 0; i < n_tasks; i++) {
		std::string task, subject;
		std::cin >> task >> subject;
		hc.add_homework(task, subject);
	}
	int n_subjs;
	std::cin >> n_subjs;
	for (int i = 0; i < n_subjs; i++) {
		int priority;
		std::string subject;
		std::cin >> subject >> priority;
		hc.set_priority(subject, priority);
	}

	int n_attempts_to_do_something;
	std::cin >> n_attempts_to_do_something;
	for (int i = 0; i < n_attempts_to_do_something; i++)
		std::cout << hc.get_next_task() << std::endl;
	return 0;
}
