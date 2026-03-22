// WK12 / TEH05
// Exercise 5: Analyze recursive Fibonacci behavior

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

struct FibStats {
	unsigned long long calls = 0;
	int maxDepth = 0;
};

unsigned long long fibonacciRecursive(int n, FibStats& stats, int currentDepth)
{
	stats.calls++;

	if (currentDepth > stats.maxDepth) {
		stats.maxDepth = currentDepth;
	}

	if (n <= 0) {
		return 0;
	}

	if (n == 1) {
		return 1;
	}

	return fibonacciRecursive(n - 1, stats, currentDepth + 1)
		+ fibonacciRecursive(n - 2, stats, currentDepth + 1);
}

int main()
{
	const int maxN = 40;

	cout << "Exercise 5 - Recursive Fibonacci analysis\n";
	cout << "CSV output for Excel:\n";
	cout << "n,fibonacci_value,total_fibonacci_calls,max_call_depth,cpu_seconds\n";

	for (int n = 0; n <= maxN; n++) {
		FibStats stats;

		const clock_t begin = clock();
		const unsigned long long value = fibonacciRecursive(n, stats, 1);
		const clock_t end = clock();

		const double cpuSeconds = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

		cout << n << ','
			 << value << ','
			 << stats.calls << ','
			 << stats.maxDepth << ','
			 << fixed << setprecision(6) << cpuSeconds << '\n';
	}

	return 0;
}
