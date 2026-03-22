// WK12 / TEH06
// Exercise 6: gcd by three methods

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

int gcdSearch(int x, int y)
{
	if (x <= 0 || y <= 0) {
		throw invalid_argument("x and y must be positive integers");
	}

	int best = 1;
	const int limit = (x < y) ? x : y;

	for (int candidate = 1; candidate <= limit; candidate++) {
		if (x % candidate == 0 && y % candidate == 0) {
			best = candidate;
		}
	}

	return best;
}

int gcdRecursiveEuclid(int x, int y)
{
	if (x <= 0 || y < 0) {
		throw invalid_argument("x must be positive and y must be nonnegative");
	}

	if (y == 0) {
		return x;
	}

	return gcdRecursiveEuclid(y, x % y);
}

int gcdIterativeEuclid(int x, int y)
{
	if (x <= 0 || y < 0) {
		throw invalid_argument("x must be positive and y must be nonnegative");
	}

	while (y != 0) {
		const int remainder = x % y;
		x = y;
		y = remainder;
	}

	return x;
}

int main()
{
	const vector<pair<int, int>> pairs = {
		{8, 12},
		{9, 18},
		{16, 25},
		{252, 105},
		{1071, 462}
	};

	cout << "Exercise 6 - gcd methods\n";
	cout << "x,y,gcd_search,gcd_recursive_euclid,gcd_iterative_euclid\n";

	for (const auto& p : pairs) {
		const int x = p.first;
		const int y = p.second;

		const int a = gcdSearch(x, y);
		const int b = gcdRecursiveEuclid(x, y);
		const int c = gcdIterativeEuclid(x, y);

		cout << x << ',' << y << ',' << a << ',' << b << ',' << c << '\n';
	}

	cout << "\nDiscussion:\n";
	cout << "1) Search method is easy to understand but usually slow (checks many candidates).\n";
	cout << "2) Recursive Euclid is short and mathematically elegant, but uses call stack frames.\n";
	cout << "3) Iterative Euclid is typically fastest and uses constant extra memory.\n";

	return 0;
}
