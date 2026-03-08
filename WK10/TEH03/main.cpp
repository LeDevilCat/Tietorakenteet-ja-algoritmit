#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Node {
	char data;
	Node *next;

	Node(char value, Node *link = nullptr) : data(value), next(link) {}
};

void print_node(const string &name, Node *p) {
	cout << name << " @ " << p;
	if (p == nullptr) {
		cout << " (nullptr)" << endl;
		return;
	}
	cout << "  data='" << p->data << "'  next=" << p->next << endl;
}

void delete_unique(const vector<Node *> &nodes) {
	set<Node *> unique_nodes;
	for (Node *p : nodes) {
		if (p != nullptr) {
			unique_nodes.insert(p);
		}
	}
	for (Node *p : unique_nodes) {
		delete p;
	}
}

int main() {
	cout << "WK10 / TEH03 - Solmuketjujen rakentaminen ja tarkistus" << endl;
	cout << "Kuvan (a), (b), (c) konfiguraatiot toteutettuna C++-lauseilla." << endl;

	cout << "\n=== Osa (a) ===" << endl;
	cout << "Lauseet:" << endl;
	cout << "  Node *a1 = new Node('0');" << endl;
	cout << "  Node *a2 = a1->next = new Node('1');" << endl;
	cout << "  Node *p0 = a1;" << endl;
	cout << "  Node *p1 = a2;" << endl;
	Node *a1 = new Node('0');
	Node *a2 = a1->next = new Node('1');
	Node *p0 = a1;
	Node *p1 = a2;
	print_node("p0", p0);
	print_node("p1", p1);
	print_node("node '0'", a1);
	print_node("node '1'", a2);
	delete_unique({a1, a2});

	cout << "\n=== Osa (b) ===" << endl;
	cout << "Lauseet:" << endl;
	cout << "  Node *n0 = new Node('0');" << endl;
	cout << "  Node *n1 = new Node('1');" << endl;
	cout << "  n0->next = nullptr;" << endl;
	cout << "  n1->next = n0;" << endl;
	cout << "  Node *p0 = n0;" << endl;
	cout << "  Node *p1 = n1;" << endl;
	cout << "  Node *p2 = n1;" << endl;
	Node *n0 = new Node('0');
	Node *n1 = new Node('1');
	n0->next = nullptr;
	n1->next = n0;
	Node *q0 = n0;
	Node *q1 = n1;
	Node *q2 = n1;
	print_node("p0", q0);
	print_node("p1", q1);
	print_node("p2", q2);
	print_node("node '0'", n0);
	print_node("node '1'", n1);
	delete_unique({n0, n1});

	cout << "\n=== Osa (c) ===" << endl;
	cout << "Lauseet:" << endl;
	cout << "  Node *c1 = new Node('0');" << endl;
	cout << "  Node *c2 = c1->next = new Node('1');" << endl;
	cout << "  Node *c3 = c2->next = new Node('2');" << endl;
	cout << "  c3->next = c2;" << endl;
	cout << "  Node *p0 = c1;" << endl;
	cout << "  Node *p1 = c2;" << endl;
	cout << "  Node *p2 = c3;" << endl;
	Node *c1 = new Node('0');
	Node *c2 = c1->next = new Node('1');
	Node *c3 = c2->next = new Node('2');
	c3->next = c2;
	Node *r0 = c1;
	Node *r1 = c2;
	Node *r2 = c3;
	print_node("p0", r0);
	print_node("p1", r1);
	print_node("p2", r2);
	print_node("node '0'", c1);
	print_node("node '1'", c2);
	print_node("node '2'", c3);

	c3->next = nullptr;
	delete_unique({c1, c2, c3});

	return 0;
}