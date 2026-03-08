#include <iostream>

using namespace std;

typedef int Stack_entry;

enum Error_code { success, underflow };

struct Node {
	Stack_entry entry;
	Node *next;
	Node(Stack_entry value, Node *link = nullptr) : entry(value), next(link) {}
};

class LinkedStackNoCounter {
public:
	LinkedStackNoCounter() : top_node(nullptr) {}

	~LinkedStackNoCounter() {
		clear();
	}

	bool empty() const {
		return top_node == nullptr;
	}

	Error_code push(Stack_entry item) {
		top_node = new Node(item, top_node);
		return success;
	}

	Error_code pop(Stack_entry &item) {
		if (empty()) {
			return underflow;
		}
		Node *old_top = top_node;
		item = old_top->entry;
		top_node = old_top->next;
		delete old_top;
		return success;
	}

	int size() const {
		int count = 0;
		Node *current = top_node;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	void clear() {
		Stack_entry trash = 0;
		while (pop(trash) == success) {
		}
	}

private:
	Node *top_node;
};

class LinkedStackWithCounter {
public:
	LinkedStackWithCounter() : top_node(nullptr), count(0) {}

	~LinkedStackWithCounter() {
		clear();
	}

	bool empty() const {
		return top_node == nullptr;
	}

	Error_code push(Stack_entry item) {
		top_node = new Node(item, top_node);
		count++;
		return success;
	}

	Error_code pop(Stack_entry &item) {
		if (empty()) {
			return underflow;
		}
		Node *old_top = top_node;
		item = old_top->entry;
		top_node = old_top->next;
		delete old_top;
		count--;
		return success;
	}

	int size() const {
		return count;
	}

	void clear() {
		Stack_entry trash = 0;
		while (pop(trash) == success) {
		}
	}

private:
	Node *top_node;
	int count;
};

void print_discussion() {
	cout << "\n(b) Muutokset muihin metodeihin, kun lisataan laskuri (count):" << endl;
	cout << "- Konstruktori: alustaa count = 0." << endl;
	cout << "- push: count++ onnistuneen lisayksen yhteydessa." << endl;
	cout << "- pop: count-- onnistuneen poiston yhteydessa." << endl;
	cout << "- clear/destruktori: taytyy paivittaa count oikein (yleensa popin kautta)." << endl;
	cout << "- kopiokonstruktori/operator=: count kopioitava oikein myos." << endl;

	cout << "\nEdut:" << endl;
	cout << "- size() on O(1), eli valiton." << endl;
	cout << "- tehokkaampi jos size() kutsutaan usein." << endl;

	cout << "\nHaitat:" << endl;
	cout << "- enemman tilaa yhdelle int-jasenelle." << endl;
	cout << "- enemman yllapitovastuuta: jokaisen rakenteen muuttavan metodin" << endl;
	cout << "  on paivitettava count oikein." << endl;
	cout << "- virheriski kasvaa, jos count paivitys unohtuu." << endl;

	cout << "\nLuvun 4 safeguards-huomio:" << endl;
	cout << "- Linkitetyssa toteutuksessa kannattaa aina toteuttaa destruktori," << endl;
	cout << "  kopiokonstruktori ja operator= (Rule of Three), jotta ei synny" << endl;
	cout << "  muistivuotoa tai vahingossa jaettuja solmuja." << endl;
}

int main() {
	cout << "WK10 / TEH05 - Linked stack size" << endl;
	cout << "(a) loopilla laskettava size, (b) laskurijasenella O(1)-size" << endl;

	LinkedStackNoCounter s1;
	s1.push(10);
	s1.push(20);
	s1.push(30);
	cout << "(a) size() ilman laskuria (loopilla): " << s1.size() << endl;

	LinkedStackWithCounter s2;
	s2.push(10);
	s2.push(20);
	s2.push(30);
	cout << "(b) size() laskurilla: " << s2.size() << endl;

	int value = 0;
	s2.pop(value);
	cout << "Popin jalkeen size() laskurilla: " << s2.size() << endl;

	print_discussion();
	return 0;
}