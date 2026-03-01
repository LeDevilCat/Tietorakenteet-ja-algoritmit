#include <iostream>
using namespace std;

// Virheenkäsittelykoodit
enum Error_code { success, fail, overflow, underflow };

// Jonon alkiotyyppi
typedef char Queue_entry;

const int maxqueue = 100;

// ===================================================================
// JONO-LUOKKA
// ===================================================================
class Queue {
public:
	Queue();
	bool empty() const;
	Error_code append(const Queue_entry &item);
	Error_code serve();
	Error_code retrieve(Queue_entry &item) const;
	void print_queue() const;

private:
	int count;
	int front, rear;
	Queue_entry entry[maxqueue];
};

Queue::Queue() {
	count = 0;
	rear = maxqueue - 1;
	front = 0;
}

bool Queue::empty() const {
	return count == 0;
}

Error_code Queue::append(const Queue_entry &item) {
	if (count >= maxqueue)
		return overflow;
	count++;
	rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
	entry[rear] = item;
	return success;
}

Error_code Queue::serve() {
	if (count <= 0)
		return underflow;
	count--;
	front = ((front + 1) == maxqueue) ? 0 : (front + 1);
	return success;
}

Error_code Queue::retrieve(Queue_entry &item) const {
	if (count <= 0)
		return underflow;
	item = entry[front];
	return success;
}

void Queue::print_queue() const {
	if (empty()) {
		cout << "[empty]";
		return;
	}

	cout << "[";
	int current = front;
	for (int i = 0; i < count; i++) {
		cout << entry[current];
		if (i < count - 1)
			cout << " ";
		current = ((current + 1) == maxqueue) ? 0 : (current + 1);
	}
	cout << "]";
}

// ===================================================================
// PÄÄOHJELMA
// ===================================================================
int main()
{
	cout << "========================================" << endl;
	cout << "  Week 8 / Exercise 1" << endl;
	cout << "  Queue: empty() and retrieve()" << endl;
	cout << "========================================" << endl;
	cout << endl;

	Queue q;
	Queue_entry item;

	cout << "Initial queue: ";
	q.print_queue();
	cout << endl;

	cout << "q.empty() -> " << (q.empty() ? "true" : "false") << endl;

	if (q.retrieve(item) == underflow)
		cout << "q.retrieve(item) on empty queue -> underflow" << endl;

	q.append('A');
	q.append('B');
	q.append('C');

	cout << "After append A, B, C: ";
	q.print_queue();
	cout << endl;

	if (q.retrieve(item) == success)
		cout << "q.retrieve(item) -> " << item << endl;

	q.serve();
	if (q.retrieve(item) == success)
		cout << "After q.serve(), q.retrieve(item) -> " << item << endl;

	return 0;
}