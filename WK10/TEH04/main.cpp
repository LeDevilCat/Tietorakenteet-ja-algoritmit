#include <iostream>

using namespace std;

int main() {
	cout << "WK10 / TEH04 - Miksi annettu push-toteutus on vaarallinen" << endl;
	cout << "(Luku 4: pointers, automatic vs dynamic object, linked stack)" << endl;
	cout << endl;
	cout << "Virheellinen malli:" << endl;
	cout << "  Error_code Stack::push(Stack_entry item)" << endl;
	cout << "  {" << endl;
	cout << "      Node new_top(item, top_node);" << endl;
	cout << "      top_node = new_top;" << endl;
	cout << "      return success;" << endl;
	cout << "  }" << endl;
	cout << endl;

	cout << "Perustelut:" << endl;
	cout << "1) new_top on automaattinen olio (stack-muisti), ei dynaaminen (heap/free store)." << endl;
	cout << "   Se tuhoutuu funktion lopussa, jolloin siihen viittaava linkki olisi dangling." << endl;
	cout << endl;
	cout << "2) Linkitetyssa pinossa top_node on yleensa Node* (osoitin)." << endl;
	cout << "   Silloin lause top_node = new_top; on tyyppivirhe (Node* <- Node)." << endl;
	cout << endl;
	cout << "3) Oikea toteutus varaa uuden solmun dynaamisesti (new)," << endl;
	cout << "   jotta solmu elaa push-funktion paluun jalkeenkin:" << endl;
	cout << "   top_node = new Node(item, top_node);" << endl;
	cout << endl;
	cout << "4) Luvun 4 policy: linkitetylla rakenteella on oltava myos destruktori," << endl;
	cout << "   kopiokonstruktori ja operator=, jotta ei synny muistivuotoja tai jaettuja solmuja." << endl;

	return 0;
}