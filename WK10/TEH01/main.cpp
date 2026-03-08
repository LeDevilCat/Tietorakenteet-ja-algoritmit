#include <cmath>
#include <iostream>
#include <new>
#include <sstream>
#include <string>

using namespace std;

typedef double Stack_entry;

enum Error_code {
	success,
	overflow,
	underflow,
	divide_by_zero,
	bad_input,
	invalid_operation
};

struct Node {
	Stack_entry entry;
	Node *next;

	Node() : entry(0.0), next(nullptr) {}

	Node(Stack_entry item, Node *add_on = nullptr) : entry(item), next(add_on) {}
};

class Stack {
public:
	Stack() : top_node(nullptr) {}

	Stack(const Stack &original) : top_node(nullptr) {
		copy_from(original);
	}

	~Stack() {
		clear();
	}

	void operator=(const Stack &original) {
		if (this == &original) {
			return;
		}

		clear();
		copy_from(original);
	}

	bool empty() const {
		return top_node == nullptr;
	}

	int size() const {
		int count = 0;
		for (Node *current = top_node; current != nullptr; current = current->next) {
			count++;
		}
		return count;
	}

	Error_code push(const Stack_entry &item) {
		Node *new_top = new (nothrow) Node(item, top_node);
		if (new_top == nullptr) {
			return overflow;
		}
		top_node = new_top;
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

	Error_code top(Stack_entry &item) const {
		if (empty()) {
			return underflow;
		}
		item = top_node->entry;
		return success;
	}

	void clear() {
		Stack_entry trash = 0.0;
		while (pop(trash) == success) {
		}
	}

private:
	Node *top_node;

	void copy_from(const Stack &original) {
		if (original.top_node == nullptr) {
			top_node = nullptr;
			return;
		}

		Node *original_node = original.top_node;
		Node *new_copy = new Node(original_node->entry);
		top_node = new_copy;

		while (original_node->next != nullptr) {
			original_node = original_node->next;
			new_copy->next = new Node(original_node->entry);
			new_copy = new_copy->next;
		}
	}
};

class PostfixCalculator {
public:
	Error_code process_token(const string &token) {
		Stack_entry number = 0.0;
		if (try_parse_number(token, number)) {
			return data.push(number);
		}

		if (token.size() != 1) {
			return bad_input;
		}

		const char op = token[0];
		if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') {
			return binary_operation(op);
		}
		if (op == 'v') {
			return unary_sqrt();
		}
		return invalid_operation;
	}

	Error_code evaluate_line(const string &line, Stack_entry &result) {
		data.clear();

		istringstream input(line);
		string token;
		while (input >> token) {
			Error_code code = process_token(token);
			if (code != success) {
				return code;
			}
		}

		if (data.top(result) != success) {
			return underflow;
		}

		return success;
	}

private:
	Stack data;

	bool try_parse_number(const string &token, Stack_entry &value) const {
		istringstream parser(token);
		parser >> value;
		return parser && parser.eof();
	}

	Error_code binary_operation(char op) {
		Stack_entry right = 0.0;
		Stack_entry left = 0.0;
		if (data.pop(right) != success || data.pop(left) != success) {
			return underflow;
		}

		Stack_entry answer = 0.0;
		switch (op) {
			case '+':
				answer = left + right;
				break;
			case '-':
				answer = left - right;
				break;
			case '*':
				answer = left * right;
				break;
			case '/':
				if (right == 0.0) {
					return divide_by_zero;
				}
				answer = left / right;
				break;
			case '^':
				answer = pow(left, right);
				break;
			default:
				return invalid_operation;
		}

		return data.push(answer);
	}

	Error_code unary_sqrt() {
		Stack_entry value = 0.0;
		if (data.pop(value) != success) {
			return underflow;
		}
		if (value < 0.0) {
			return bad_input;
		}
		return data.push(sqrt(value));
	}
};

const char *error_to_string(Error_code code) {
	switch (code) {
		case success:
			return "ok";
		case overflow:
			return "muisti loppui (overflow)";
		case underflow:
			return "pinossa liian vahan alkioita";
		case divide_by_zero:
			return "nollalla jako";
		case bad_input:
			return "virheellinen syote";
		case invalid_operation:
			return "tuntematon operaatio";
		default:
			return "virhe";
	}
}

int main() {
	PostfixCalculator calc;

	cout << "WK10 / TEH01 - Postfix-laskin linkitetylla pinolla" << endl;
	cout << "(Sisaltaa luvun 4 safeguards: destruktori, kopiokonstruktori, operator=)" << endl;
	cout << "Operaattorit: + - * / ^ v(sqrt)" << endl;
	cout << "Esimerkki: 5 1 2 + 4 * + 3 -" << endl;

	string line;
	while (true) {
		cout << "calc> ";
		if (!getline(cin, line)) {
			break;
		}
		if (line == "q" || line == "quit") {
			break;
		}

		Stack_entry result = 0.0;
		Error_code code = calc.evaluate_line(line, result);
		if (code != success) {
			cout << "VIRHE: " << error_to_string(code) << endl;
		} else {
			cout << "= " << result << endl;
		}
	}

	return 0;
}