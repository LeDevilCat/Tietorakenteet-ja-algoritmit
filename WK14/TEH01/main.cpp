#include <iostream>

using namespace std;

int main() {
	cout << "WK14 / TEH01 - Singly linked list functions" << endl;
	cout << "Exercise 1: first simply linked list implementation" << endl;
	cout << endl;
	cout << "Same style as earlier weeks: the program prints the solution outline." << endl;
	cout << endl;
	cout << R"cpp(
Required member functions:
  (a) constructor List
  (b) copy constructor
  (c) operator=
  (d) destructor ~List
  (e) clear
  (f) size
  (g) empty
  (h) full
  (i) replace
  (j) retrieve
  (k) remove
  (l) traverse

Core idea for the first simply linked implementation:
  - keep a head pointer and a count
  - locate the node at a position by walking from head
  - make copy / assignment perform a deep copy
  - clear and destructor delete every node

Compact reference implementation:

template <class List_entry>
struct Node {
	List_entry entry;
	Node *next;
	Node(const List_entry &item, Node *link = 0) : entry(item), next(link) {}
};

template <class List_entry>
class List {
public:
	List() : head(0), count(0) {}
	List(const List &original) : head(0), count(0) { copy_from(original); }
	List &operator=(const List &original) {
		if (this != &original) {
			clear();
			copy_from(original);
		}
		return *this;
	}
	~List() { clear(); }

	void clear() {
		while (head != 0) {
			Node<List_entry> *old = head;
			head = head->next;
			delete old;
		}
		count = 0;
	}

	int size() const { return count; }
	bool empty() const { return count == 0; }
	bool full() const { return false; }

	Error_code replace(int position, const List_entry &x) {
		Node<List_entry> *current = locate(position);
		if (current == 0) return range_error;
		current->entry = x;
		return success;
	}

	Error_code retrieve(int position, List_entry &x) const {
		Node<List_entry> *current = locate(position);
		if (current == 0) return range_error;
		x = current->entry;
		return success;
	}

	Error_code remove(int position, List_entry &x) {
		if (position < 0 || position >= count) return range_error;
		Node<List_entry> *current = head;
		Node<List_entry> *previous = 0;
		for (int i = 0; i < position; ++i) {
			previous = current;
			current = current->next;
		}
		x = current->entry;
		if (previous == 0) {
			head = current->next;
		} else {
			previous->next = current->next;
		}
		delete current;
		--count;
		return success;
	}

	void traverse(void (*visit)(List_entry &)) {
		for (Node<List_entry> *current = head; current != 0; current = current->next) {
			(*visit)(current->entry);
		}
	}

private:
	Node<List_entry> *head;
	int count;

	Node<List_entry> *locate(int position) const {
		if (position < 0 || position >= count) return 0;
		Node<List_entry> *current = head;
		for (int i = 0; i < position; ++i) {
			current = current->next;
		}
		return current;
	}

	void copy_from(const List &original) {
		if (original.head == 0) {
			head = 0;
			count = 0;
			return;
		}
		head = new Node<List_entry>(original.head->entry);
		Node<List_entry> *dest = head;
		Node<List_entry> *src = original.head->next;
		while (src != 0) {
			dest->next = new Node<List_entry>(src->entry);
			dest = dest->next;
			src = src->next;
		}
		count = original.count;
	}
};

Notes:
  - full() for a linked list is effectively false in the usual section-6.1 model.
  - replace/retrieve only walk to the node and then update/read the entry.
  - remove must relink the predecessor around the deleted node.
  - traverse visits every entry in order from head to tail.
)cpp" << endl;
	return 0;
}