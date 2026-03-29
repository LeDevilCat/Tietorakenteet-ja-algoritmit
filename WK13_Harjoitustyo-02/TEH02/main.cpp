// WK13 TEH02
// Exercise 2: Remaining contiguous List operations.

#include <iostream>

enum Error_code {
	success,
	overflow,
	underflow,
	range_error
};

template <class List_entry, int max_list = 20>
class List {
public:
	// (a) constructor
	List();

	// (b) clear
	void clear();

	// (c) empty
	bool empty() const;

	// (d) full
	bool full() const;

	int size() const;
	Error_code insert(int position, const List_entry &x);

	// (e) replace
	Error_code replace(int position, const List_entry &x);

	// (f) retrieve
	Error_code retrieve(int position, List_entry &x) const;

	// (g) remove
	Error_code remove(int position, List_entry &x);

private:
	int count;
	List_entry entry[max_list];
};

template <class List_entry, int max_list>
List<List_entry, max_list>::List() : count(0) {
	// Post: List created and initialized as empty.
}

template <class List_entry, int max_list>
void List<List_entry, max_list>::clear() {
	// Post: All entries removed.
	count = 0;
}

template <class List_entry, int max_list>
bool List<List_entry, max_list>::empty() const {
	// Post: true if list has no entries.
	return count == 0;
}

template <class List_entry, int max_list>
bool List<List_entry, max_list>::full() const {
	// Post: true if list capacity is exhausted.
	return count >= max_list;
}

template <class List_entry, int max_list>
int List<List_entry, max_list>::size() const {
	return count;
}

template <class List_entry, int max_list>
Error_code List<List_entry, max_list>::insert(int position, const List_entry &x) {
	if (full()) {
		return overflow;
	}
	if (position < 0 || position > count) {
		return range_error;
	}
	for (int i = count - 1; i >= position; --i) {
		entry[i + 1] = entry[i];
	}
	entry[position] = x;
	++count;
	return success;
}

template <class List_entry, int max_list>
Error_code List<List_entry, max_list>::replace(int position, const List_entry &x) {
	// Post: If position valid, element at position is replaced by x.
	if (position < 0 || position >= count) {
		return range_error;
	}
	entry[position] = x;
	return success;
}

template <class List_entry, int max_list>
Error_code List<List_entry, max_list>::retrieve(int position, List_entry &x) const {
	// Post: If position valid, x gets copy of element at position.
	if (position < 0 || position >= count) {
		return range_error;
	}
	x = entry[position];
	return success;
}

template <class List_entry, int max_list>
Error_code List<List_entry, max_list>::remove(int position, List_entry &x) {
	// Post: If position valid, entry is removed and copied to x.
	if (empty()) {
		return underflow;
	}
	if (position < 0 || position >= count) {
		return range_error;
	}
	x = entry[position];
	for (int i = position; i < count - 1; ++i) {
		entry[i] = entry[i + 1];
	}
	--count;
	return success;
}

int main() {
	List<int, 8> values;

	values.insert(0, 10);
	values.insert(1, 20);
	values.insert(2, 30);

	std::cout << "empty=" << values.empty() << ", full=" << values.full()
			  << ", size=" << values.size() << '\n';

	values.replace(1, 99);
	int x = 0;
	values.retrieve(1, x);
	std::cout << "retrieve(1)=" << x << '\n';

	values.remove(0, x);
	std::cout << "removed=" << x << ", size=" << values.size() << '\n';

	values.clear();
	std::cout << "after clear, empty=" << values.empty() << '\n';

	return 0;
}