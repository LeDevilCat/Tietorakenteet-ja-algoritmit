#include <iostream>
#include <string>
using namespace std;

// Virheenkäsittelykoodit
enum Error_code { success, fail, overflow, underflow };

typedef char Queue_entry;

const int maxqueue = 1000;

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

// ===================================================================
// TEHTÄVÄN 3 FUNKTIO
// ===================================================================
char classify_line()
{
	string line;
	getline(cin, line);

	Queue left_part;
	bool colon_found = false;
	bool same = true;
	int left_length = 0;
	int right_length = 0;

	for (int i = 0; i < static_cast<int>(line.length()); i++) {
		char ch = line[i];

		if (!colon_found) {
			if (ch == ':') {
				colon_found = true;
			} else {
				if (left_part.append(ch) == overflow)
					return fail;
				left_length++;
			}
		} else {
			right_length++;
			Queue_entry left_char;

			if (left_part.retrieve(left_char) == success) {
				left_part.serve();
				if (left_char != ch)
					same = false;
			} else {
				same = false;
			}
		}
	}

	if (!colon_found)
		return 'N';

	if (left_length > right_length)
		return 'L';

	if (right_length > left_length)
		return 'R';

	if (same)
		return 'S';

	return 'D';
}

// ===================================================================
// PÄÄOHJELMA
// ===================================================================
int main()
{
	cout << "Enter one line: ";
	char result = classify_line();
	cout << result << endl;
	return 0;
}