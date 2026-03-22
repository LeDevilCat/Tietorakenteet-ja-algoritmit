// WK12 / TEH01
// Exercise 5.1 E1

#include <iostream>
#include <vector>

using namespace std;

int f(int n)
{
	if (n == 0) {
		return 0;
	}

	if (n % 2 == 0) {
		return f(n / 2);
	}

	return 1 + f(n - 1);
}

int main()
{
	const vector<int> testValues = {1, 2, 3, 99, 100, 128};

	cout << "Exercise 5.1 E1\n";
	cout << "f(n) = 0, if n = 0\n";
	cout << "f(n) = f(n/2), if n is even and n > 0\n";
	cout << "f(n) = 1 + f(n-1), if n is odd and n > 0\n\n";

	for (int n : testValues) {
		cout << "n = " << n << " -> f(n) = " << f(n) << "\n";
	}

	return 0;
}
