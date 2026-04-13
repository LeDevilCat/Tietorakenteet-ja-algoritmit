#include <iostream>

using namespace std;

int main() {
	cout << "WK14 / TEH02 - Remove for the second singly linked list" << endl;
	cout << "Exercise 2: list remembers the last-used position" << endl;
	cout << endl;
	cout << R"cpp(
The important idea in the second implementation is that the list keeps
track of the last accessed node and its position. That lets a search start
from the remembered place instead of always starting from head.

	The book's model uses these mutable data members:
	  - int current_position
	  - Node<List_entry> *current
	and a helper
	  - void set_position(int position) const

	So remove should follow the same pattern: locate the node through the
	current-position helper, relink the predecessor around it, and then repair
	the remembered position.

For remove, the safe structure is:

  Error_code remove(int position, List_entry &x) {
	  if (position < 0 || position >= count) {
		  return range_error;
	  }

		  if (position == 0) {
			  Node<List_entry> *old_head = head;
			  x = old_head->entry;
			  head = old_head->next;
			  delete old_head;
			  --count;
			  current = head;
			  current_position = (head == 0 ? -1 : 0);
			  return success;
		  }

		  set_position(position - 1);
		  Node<List_entry> *previous = current;
		  Node<List_entry> *doomed = previous->next;
		  x = doomed->entry;
		  previous->next = doomed->next;
		  delete doomed;
	  --count;

		  current = previous;
		  current_position = position - 1;

	  return success;
  }

Minimal state kept by the implementation:
  - head: pointer to first node
	  - current: pointer to the last-used node
	  - current_position: index of current
  - count: number of nodes

Why this works:
  - positions are checked before any traversal
  - removal of the first node is handled separately by relinking head
	  - the remembered position is repaired after the delete so future accesses
		still have a valid starting point

If you want the exact textbook version, the only extra helper needed is a
"locate" function that updates the remembered node while walking.
)cpp" << endl;
	return 0;
}