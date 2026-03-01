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

protected:
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

// ===================================================================
// EXTENDED_QUEUE-LUOKKA
// ===================================================================
class Extended_queue : public Queue {
public:
	bool full() const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry &item);
	int size() const;
	void print_queue() const;
};

bool Extended_queue::full() const {
	return count == maxqueue;
}

void Extended_queue::clear() {
	count = 0;
	rear = maxqueue - 1;
	front = 0;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item) {
	if (count <= 0)
		return underflow;
	item = entry[front];
	count--;
	front = ((front + 1) == maxqueue) ? 0 : (front + 1);
	return success;
}

int Extended_queue::size() const {
	return count;
}

void Extended_queue::print_queue() const {
	if (count == 0) {
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
	cout << "  Week 8 / Exercise 2" << endl;
	cout << "  Extended Queue: full(), clear()," << endl;
	cout << "  serve_and_retrieve()" << endl;
	cout << "========================================" << endl;
	cout << endl;

	Extended_queue q;
	Queue_entry item;

	cout << "Initial queue: ";
	q.print_queue();
	cout << endl;

	cout << "q.full() -> " << (q.full() ? "true" : "false") << endl;

	q.append('X');
	q.append('Y');
	q.append('Z');

	cout << "After append X, Y, Z: ";
	q.print_queue();
	cout << " (size = " << q.size() << ")" << endl;

	if (q.serve_and_retrieve(item) == success)
		cout << "q.serve_and_retrieve(item) -> " << item << endl;

	cout << "After serve_and_retrieve: ";
	q.print_queue();
	cout << " (size = " << q.size() << ")" << endl;

	q.clear();
	cout << "After q.clear(): ";
	q.print_queue();
	cout << " (size = " << q.size() << ")" << endl;

	return 0;
}