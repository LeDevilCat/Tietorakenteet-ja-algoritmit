#include <iostream>

using namespace std;

struct Node {
	char data;
	Node *next;

	Node(char value, Node *link = nullptr) : data(value), next(link) {}
};

void print_node(const char *name, Node *p) {
	cout << name << " @ " << p;
	if (p == nullptr) {
		cout << " (nullptr)" << endl;
		return;
	}
	cout << "  data='" << p->data << "'  next=" << p->next << endl;
}

int main() {
	Node *p0 = new Node('0');
	Node *p1 = p0->next = new Node('1');
	Node *p2 = p1->next = new Node('2', p1);

	cout << "WK10 / TEH02 - Solmuketjun konfiguraatio" << endl;
	cout << "\nLauseet:" << endl;
	cout << "  Node *p0 = new Node('0');" << endl;
	cout << "  Node *p1 = p0->next = new Node('1');" << endl;
	cout << "  Node *p2 = p1->next = new Node('2', p1);" << endl;

	cout << "\nASCII-kaavio:" << endl;
	cout << "  p0 --> [0|*] ----> [1|*] ----> [2|*]" << endl;
	cout << "                       ^            |" << endl;
	cout << "                       |____________|" << endl;
	cout << "  p1 osoittaa solmuun [1], p2 osoittaa solmuun [2]." << endl;
	cout << "  (Luvun 4 mukaisesti * = next-linkki, NULL puuttuu koska ketju on syklinen.)" << endl;

	cout << "\nTulostetaan solmujen sisalto (data ja next):" << endl;
	print_node("p0", p0);
	print_node("p1", p1);
	print_node("p2", p2);

	cout << "\nHuomio: ennen poistamista katkaistaan sykli, jotta delete on turvallinen." << endl;
	p2->next = nullptr;
	delete p2;
	p2 = nullptr;
	delete p1;
	p1 = nullptr;
	delete p0;
	p0 = nullptr;

	return 0;
}