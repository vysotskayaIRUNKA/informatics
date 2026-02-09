#include <iostream>
using std::cin, std::cout, std::endl;

// как было бы, если бы писали структурой
/*struct Node {
  int value;
  Node *prev = nullptr;
  Node *next = nullptr;
};

struct Queue {
  Node *first = nullptr;
  Node *last = nullptr;
  unsigned size = 0u;
};

void push(Queue *q, int value)
{
  auto node = new Node();
  node->value = value;
  if (!q->size) {
    q->first = node;
    q->last = node;
  }
  else {
    q->last->next = node;
    node->prev = q->last;
    q->last = node;
  }
  q->size += 1;
}

int pop(Queue *q)
{
  int value = 0;
  if (q->size) {
    auto first = q->first;
    value = first->value;
    q->first = first->next;
    delete first;

    if (q->size == 1) {
      q->last = nullptr;
    }
    q->size -= 1;
  }
  return value;
}

unsigned size(Queue *q)
{
  return q->size;
}

void destruct(Queue *q)
{
  while (q->size) {
    pop(q);
  }
}

int main()
{
  Queue q;
  push(&q, 1);
  push(&q, 2);
  push(&q, 3);
  cout << pop(&q) << endl;
  cout << pop(&q) << endl;
  destruct(&q);
}*/

struct Node {
	int value;
	Node *prev = nullptr;
	Node *next = nullptr;
};

class Queue {
public:
	Queue()
	{
		cout << "constructor called" << endl;
		first = nullptr;
		last = nullptr;
		q_size = 0;
	}

	void push(int value)
	{
		auto node = new Node();
		node->value = value;
		if (!q_size) {
			first = node;
			last = node;
		}
		else {
			last->next = node;
			node->prev = last;
			last = node;
		}
		q_size += 1;
	}

	int pop()
	{
		int value = 0;
		if (q_size) {
			auto to_remove = first;
			value = to_remove->value;
			first = to_remove->next;
			delete to_remove;

			if (q_size == 1) {
				last = nullptr;
			}
			q_size -= 1;
		}
		return value;
	}

	unsigned size() { return q_size; }

	~Queue()
	{
		cout << "Destructor called" << endl;
		while (q_size) {
			pop();
		}
	}

private:
	Node *first = nullptr;
	Node *last = nullptr;
	unsigned q_size = 0u;
};

int main()
{
	Queue q;
	q.push(1);
	q.push(2);
	q.push(3);
	cout << q.pop() << endl;
	cout << q.pop() << endl;
	cout << "work finished" << endl;
}
