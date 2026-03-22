// WK12 / TEH02
// Exercise 5.1 E2

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int f(int n)
{
	if (n <= 1) {
		return n;
	}

	if (n % 2 == 0) {
		return n + f(n / 2);
	}

	return f((n + 1) / 2) + f((n - 1) / 2);
}

void printRecursionTree(int n, const string& indent = "", bool isLast = true)
{
	cout << indent;
	cout << (isLast ? "└─ " : "├─ ");
	cout << "f(" << n << ")";

	if (n <= 1) {
		cout << " = " << n << "\n";
		return;
	}

	if (n % 2 == 0) {
		cout << " = " << n << " + f(" << n / 2 << ")\n";
		printRecursionTree(n / 2, indent + (isLast ? "   " : "│  "), true);
	}
	else {
		cout << " = f(" << (n + 1) / 2 << ") + f(" << (n - 1) / 2 << ")\n";
		printRecursionTree((n + 1) / 2, indent + (isLast ? "   " : "│  "), false);
		printRecursionTree((n - 1) / 2, indent + (isLast ? "   " : "│  "), true);
	}
}

int main()
{
	const vector<int> testValues = {1, 2, 3, 4, 5, 6};

	cout << "Exercise 5.1 E2\n";
	cout << "f(n) = n, if n <= 1\n";
	cout << "f(n) = n + f(n/2), if n is even and n > 1\n";
	cout << "f(n) = f((n+1)/2) + f((n-1)/2), if n is odd and n > 1\n\n";

	for (int n : testValues) {
		cout << "Recursion tree for n = " << n << ":\n";
		printRecursionTree(n);
		cout << "Result: f(" << n << ") = " << f(n) << "\n\n";
	}

	return 0;
}
