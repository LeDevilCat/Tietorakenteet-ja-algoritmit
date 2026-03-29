// WK13 TEH01
// Exercise 1: List utility functions using only the List ADT interface.

#include <iostream>

enum Error_code {
	success,
	fail,
	overflow,
	underflow,
	range_error
};

template <class List_entry, int max_list = 50>
class List {
public:
	List();
	int size() const;
	bool full() const;
	bool empty() const;
	void clear();
	void traverse(void (*visit)(List_entry &));
	Error_code retrieve(int position, List_entry &x) const;
	Error_code replace(int position, const List_entry &x);
	Error_code remove(int position, List_entry &x);
	Error_code insert(int position, const List_entry &x);

private:
	int count;
	List_entry entry[max_list];
};

template <class List_entry, int max_list>
List<List_entry, max_list>::List() : count(0) {}

template <class List_entry, int max_list>
int List<List_entry, max_list>::size() const {
	return count;
}

template <class List_entry, int max_list>
bool List<List_entry, max_list>::full() const {
	return count >= max_list;
}

template <class List_entry, int max_list>
bool List<List_entry, max_list>::empty() const {
	return count == 0;
}

template <class List_entry, int max_list>
void List<List_entry, max_list>::clear() {
	count = 0;
}

template <class List_entry, int max_list>
void List<List_entry, max_list>::traverse(void (*visit)(List_entry &)) {
	for (int i = 0; i < count; ++i) {
		(*visit)(entry[i]);
	}
}

template <class List_entry, int max_list>
Error_code List<List_entry, max_list>::retrieve(int position, List_entry &x) const {
	if (position < 0 || position >= count) {
		return range_error;
	}
	x = entry[position];
	return success;
}

template <class List_entry, int max_list>
Error_code List<List_entry, max_list>::replace(int position, const List_entry &x) {
	if (position < 0 || position >= count) {
		return range_error;
	}
	entry[position] = x;
	return success;
}

template <class List_entry, int max_list>
Error_code List<List_entry, max_list>::remove(int position, List_entry &x) {
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
void report_error(const char *fn_name, Error_code code) {
	if (code != success) {
		std::cerr << "Error in " << fn_name << ": code=" << code << '\n';
	}
}

// E1
template <class List_entry, int max_list>
Error_code insert_first(const List_entry &x, List<List_entry, max_list> &a_list)
/* Pre: a_list exists.
   Post: If a_list is not full, x is inserted at position 0.
		 Else returns overflow. */
{
	Error_code result = a_list.insert(0, x);
	report_error<List_entry, max_list>("insert_first", result);
	return result;
}

// E2
template <class List_entry, int max_list>
Error_code remove_first(List_entry &x, List<List_entry, max_list> &a_list)
/* Pre: a_list exists.
   Post: If a_list is not empty, first entry is removed and copied to x.
		 Else returns underflow. */
{
	if (a_list.empty()) {
		report_error<List_entry, max_list>("remove_first", underflow);
		return underflow;
	}
	Error_code result = a_list.remove(0, x);
	report_error<List_entry, max_list>("remove_first", result);
	return result;
}

// E3
template <class List_entry, int max_list>
Error_code insert_last(const List_entry &x, List<List_entry, max_list> &a_list)
/* Pre: a_list exists.
   Post: If a_list is not full, x is inserted as the last entry.
		 Else returns overflow. */
{
	Error_code result = a_list.insert(a_list.size(), x);
	report_error<List_entry, max_list>("insert_last", result);
	return result;
}

// E4
template <class List_entry, int max_list>
Error_code remove_last(List_entry &x, List<List_entry, max_list> &a_list)
/* Pre: a_list exists.
   Post: If a_list is not empty, last entry is removed and copied to x.
		 Else returns underflow. */
{
	if (a_list.empty()) {
		report_error<List_entry, max_list>("remove_last", underflow);
		return underflow;
	}
	Error_code result = a_list.remove(a_list.size() - 1, x);
	report_error<List_entry, max_list>("remove_last", result);
	return result;
}

// E5
template <class List_entry, int max_list>
Error_code median_list(List_entry &x, List<List_entry, max_list> &a_list)
/* Pre: a_list exists.
   Post: If a_list is not empty, x receives middle entry.
		 For even size, left-central entry is used.
		 Else returns underflow. */
{
	if (a_list.empty()) {
		report_error<List_entry, max_list>("median_list", underflow);
		return underflow;
	}
	int median_pos = (a_list.size() - 1) / 2;
	Error_code result = a_list.retrieve(median_pos, x);
	report_error<List_entry, max_list>("median_list", result);
	return result;
}

// E6
template <class List_entry, int max_list>
Error_code interchange(int pos1, int pos2, List<List_entry, max_list> &a_list)
/* Pre: a_list exists.
   Post: If pos1 and pos2 are valid positions, entries are interchanged.
		 Else returns range_error. */
{
	int n = a_list.size();
	if (pos1 < 0 || pos2 < 0 || pos1 >= n || pos2 >= n) {
		report_error<List_entry, max_list>("interchange", range_error);
		return range_error;
	}
	if (pos1 == pos2) {
		return success;
	}

	List_entry first_value, second_value;
	Error_code result = a_list.retrieve(pos1, first_value);
	if (result != success) {
		report_error<List_entry, max_list>("interchange", result);
		return result;
	}
	result = a_list.retrieve(pos2, second_value);
	if (result != success) {
		report_error<List_entry, max_list>("interchange", result);
		return result;
	}
	result = a_list.replace(pos1, second_value);
	if (result != success) {
		report_error<List_entry, max_list>("interchange", result);
		return result;
	}
	result = a_list.replace(pos2, first_value);
	report_error<List_entry, max_list>("interchange", result);
	return result;
}

// E7
template <class List_entry, int max_list>
void reverse_traverse_list(List<List_entry, max_list> &a_list, void (*visit)(List_entry &))
/* Pre: a_list exists and visit is a valid function pointer.
   Post: visit has been applied from last entry to first entry.
		 If visit modifies an entry, the modified value is written back. */
{
	for (int i = a_list.size() - 1; i >= 0; --i) {
		List_entry current;
		Error_code result = a_list.retrieve(i, current);
		if (result != success) {
			report_error<List_entry, max_list>("reverse_traverse_list", result);
			return;
		}
		(*visit)(current);
		result = a_list.replace(i, current);
		if (result != success) {
			report_error<List_entry, max_list>("reverse_traverse_list", result);
			return;
		}
	}
}

// E8
template <class List_entry, int max_list>
Error_code copy(List<List_entry, max_list> &dest, List<List_entry, max_list> &source)
/* Pre: dest and source exist.
   Post: If all insertions succeed, dest becomes an exact copy of source.
		 source remains unchanged.
		 Previous entries in dest are discarded. */
{
	dest.clear();
	for (int i = 0; i < source.size(); ++i) {
		List_entry value;
		Error_code result = source.retrieve(i, value);
		if (result != success) {
			report_error<List_entry, max_list>("copy", result);
			return result;
		}
		result = dest.insert(dest.size(), value);
		if (result != success) {
			report_error<List_entry, max_list>("copy", result);
			return result;
		}
	}
	return success;
}

// E9
template <class List_entry, int max_list>
Error_code join(List<List_entry, max_list> &list1, List<List_entry, max_list> &list2)
/* Pre: list1 and list2 exist.
   Post: If all insertions succeed, entries of list1 are appended to list2.
		 list1 remains unchanged. */
{
	for (int i = 0; i < list1.size(); ++i) {
		List_entry value;
		Error_code result = list1.retrieve(i, value);
		if (result != success) {
			report_error<List_entry, max_list>("join", result);
			return result;
		}
		result = list2.insert(list2.size(), value);
		if (result != success) {
			report_error<List_entry, max_list>("join", result);
			return result;
		}
	}
	return success;
}

// E10
template <class List_entry, int max_list>
void reverse(List<List_entry, max_list> &a_list)
/* Pre: a_list exists.
   Post: Entry order in a_list is reversed. */
{
	int left = 0;
	int right = a_list.size() - 1;
	while (left < right) {
		List_entry left_value, right_value;
		Error_code result = a_list.retrieve(left, left_value);
		if (result != success) {
			report_error<List_entry, max_list>("reverse", result);
			return;
		}
		result = a_list.retrieve(right, right_value);
		if (result != success) {
			report_error<List_entry, max_list>("reverse", result);
			return;
		}
		result = a_list.replace(left, right_value);
		if (result != success) {
			report_error<List_entry, max_list>("reverse", result);
			return;
		}
		result = a_list.replace(right, left_value);
		if (result != success) {
			report_error<List_entry, max_list>("reverse", result);
			return;
		}
		++left;
		--right;
	}
}

// E11
template <class List_entry, int max_list>
Error_code split(
	List<List_entry, max_list> &source,
	List<List_entry, max_list> &oddlist,
	List<List_entry, max_list> &evenlist)
/* Pre: source, oddlist, and evenlist exist.
   Post: oddlist gets entries from source positions 1,3,5,... in human counting
		 (indices 0,2,4,...), and evenlist gets positions 2,4,6,...
		 (indices 1,3,5,...). Any previous content in oddlist/evenlist is discarded. */
{
	oddlist.clear();
	evenlist.clear();

	for (int i = 0; i < source.size(); ++i) {
		List_entry value;
		Error_code result = source.retrieve(i, value);
		if (result != success) {
			report_error<List_entry, max_list>("split", result);
			return result;
		}

		if (i % 2 == 0) {
			result = oddlist.insert(oddlist.size(), value);
		} else {
			result = evenlist.insert(evenlist.size(), value);
		}

		if (result != success) {
			report_error<List_entry, max_list>("split", result);
			return result;
		}
	}

	return success;
}

void print_int(int &value) {
	std::cout << value << ' ';
}

void increment_and_print(int &x) {
	++x;
	std::cout << x << ' ';
}

int main() {
	List<int, 20> numbers;

	insert_last(10, numbers);
	insert_last(20, numbers);
	insert_last(30, numbers);
	insert_first(5, numbers);

	std::cout << "Initial: ";
	numbers.traverse(print_int);
	std::cout << '\n';

	interchange(1, 3, numbers);
	std::cout << "After interchange(1,3): ";
	numbers.traverse(print_int);
	std::cout << '\n';

	int med = 0;
	if (median_list(med, numbers) == success) {
		std::cout << "Median(left middle if even): " << med << '\n';
	}

	reverse(numbers);
	std::cout << "Reversed: ";
	numbers.traverse(print_int);
	std::cout << '\n';

	List<int, 20> copied;
	copy(copied, numbers);

	List<int, 20> odds;
	List<int, 20> evens;
	split(copied, odds, evens);

	std::cout << "Odd positions: ";
	odds.traverse(print_int);
	std::cout << '\n';

	std::cout << "Even positions: ";
	evens.traverse(print_int);
	std::cout << '\n';

	std::cout << "Reverse traverse (increment each): ";
	reverse_traverse_list(numbers, increment_and_print);
	std::cout << '\n';

	int removed = 0;
	remove_first(removed, numbers);
	remove_last(removed, numbers);

	std::cout << "Final: ";
	numbers.traverse(print_int);
	std::cout << '\n';

	return 0;
}