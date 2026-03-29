// WK13 TEH03
// Exercise 3: Constructors for singly and doubly linked Node objects.

#include <iostream>

template <class Node_entry>
struct Singly_node {
	Node_entry entry;
	Singly_node<Node_entry> *next;

	// Default constructor form.
	Singly_node() : next(nullptr) {}

	// Constructor with entry and optional next-link.
	Singly_node(const Node_entry &item, Singly_node<Node_entry> *link = nullptr)
		: entry(item), next(link) {}
};

template <class Node_entry>
struct Doubly_node {
	Node_entry entry;
	Doubly_node<Node_entry> *next;
	Doubly_node<Node_entry> *back;

	// Default constructor form.
	Doubly_node() : next(nullptr), back(nullptr) {}

	// Constructor with entry, optional back-link and next-link.
	Doubly_node(
		const Node_entry &item,
		Doubly_node<Node_entry> *link_back = nullptr,
		Doubly_node<Node_entry> *link_next = nullptr)
		: entry(item), next(link_next), back(link_back) {}
};

int main() {
	// Singly linked node constructor tests.
	Singly_node<int> s_default;
	Singly_node<int> s_tail(20);
	Singly_node<int> s_head(10, &s_tail);

	std::cout << "Singly: head=" << s_head.entry
			  << ", head->next=" << s_head.next->entry << '\n';
	std::cout << "Singly default next is null: " << (s_default.next == nullptr) << '\n';

	// Doubly linked node constructor tests.
	Doubly_node<int> d_default;
	Doubly_node<int> d_middle(200);
	Doubly_node<int> d_first(100, nullptr, &d_middle);
	Doubly_node<int> d_last(300, &d_middle, nullptr);
	d_middle.back = &d_first;
	d_middle.next = &d_last;

	std::cout << "Doubly chain: " << d_first.entry << " <-> "
			  << d_middle.entry << " <-> " << d_last.entry << '\n';
	std::cout << "Doubly default links null: "
			  << (d_default.back == nullptr && d_default.next == nullptr) << '\n';

	return 0;
}