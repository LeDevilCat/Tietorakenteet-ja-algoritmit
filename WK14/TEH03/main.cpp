#include <iostream>

using namespace std;

int main() {
	cout << "WK14 / TEH03 - Singly vs doubly linked lists" << endl;
	cout << "Exercise 3: identify common functions and rewrite the different ones" << endl;
	cout << endl;
	cout << R"cpp(
Functions that are the same for singly and doubly linked lists:
  (a) constructor List
  (b) copy constructor
  (c) operator=
  (d) destructor ~List
  (e) clear
  (f) size
  (g) empty
  (h) full
  (i) replace
  (k) retrieve
  (m) traverse

Functions that need new doubly linked versions:
  (j) insert
  (l) remove

Reason:
  - replace, retrieve, size, empty, full, clear and traverse do not depend
    on whether each node has one link or two links.
  - insert and remove must update both next and back links in the doubly
    linked version.

Typical doubly linked node:

template <class List_entry>
struct Node {
	List_entry entry;
	Node *next;
	Node *back;
	Node(const List_entry &item, Node *prev = 0, Node *link = 0)
		: entry(item), next(link), back(prev) {}
};

The methods that differ in the doubly linked version:

  Error_code insert(int position, const List_entry &x) {
      if (position < 0 || position > count) return range_error;
	  Node *new_node = new Node(x);
	  if (position == 0) {
	      new_node->next = head;
	      if (head != 0) head->back = new_node;
	      head = new_node;
	  } else {
	      Node *before = locate(position - 1);
	      Node *after = before->next;
	      new_node->back = before;
	      new_node->next = after;
	      before->next = new_node;
	      if (after != 0) after->back = new_node;
	  }
	  ++count;
	  return success;
  }

  Error_code remove(int position, List_entry &x) {
      if (position < 0 || position >= count) return range_error;

	  Node *current = locate(position);
	  x = current->entry;

	  if (current->back != 0) {
	      current->back->next = current->next;
	  } else {
	      head = current->next;
	  }

	  if (current->next != 0) {
	      current->next->back = current->back;
	  }

	  delete current;
	  --count;
	  return success;
  }

Short comparison:
  - singly linked list uses only next links
  - doubly linked list uses both next and back links
  - that is why insert/remove need different pointer updates
  - the remaining methods keep the same external behavior and can stay the same
)cpp" << endl;
	return 0;
}