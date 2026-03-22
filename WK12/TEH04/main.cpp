// WK12 / TEH04
// Exercise 4: Compare two Hanoi algorithms

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Stats {
	unsigned long long moves = 0;
	unsigned long long calls = 0;
};

void recursiveHanoi(int count, int start, int finish, int temp, ostringstream& out, Stats& stats)
{
	stats.calls++;

	if (count > 0) {
		recursiveHanoi(count - 1, start, temp, finish, out, stats);
		out << "Move disk " << count << " from " << start << " to " << finish << ".\n";
		stats.moves++;
		recursiveHanoi(count - 1, temp, finish, start, out, stats);
	}
}

void hanoiWithoutTailRecursion(int count, int start, int finish, int temp, ostringstream& out, Stats& stats)
{
	stats.calls++;

	int swapTower;
	while (count > 0) {
		recursiveHanoi(count - 1, start, temp, finish, out, stats);
		out << "Move disk " << count << " from " << start << " to " << finish << ".\n";
		stats.moves++;

		count--;
		swapTower = start;
		start = temp;
		temp = swapTower;
	}
}

int main()
{
	const int disks = 5;

	ostringstream recursiveOutput;
	ostringstream iterativeOutput;

	Stats recursiveStats;
	Stats iterativeStats;

	recursiveHanoi(disks, 1, 3, 2, recursiveOutput, recursiveStats);
	hanoiWithoutTailRecursion(disks, 1, 3, 2, iterativeOutput, iterativeStats);

	const string output1 = recursiveOutput.str();
	const string output2 = iterativeOutput.str();

	cout << "Exercise 4 - Compare Hanoi outputs\n";
	cout << "Disks: " << disks << "\n\n";

	cout << "Recursive: moves=" << recursiveStats.moves << ", calls=" << recursiveStats.calls << '\n';
	cout << "Tail-recursion-removed: moves=" << iterativeStats.moves << ", calls=" << iterativeStats.calls
		 << "\n\n";

	if (output1 == output2) {
		cout << "RESULT: Outputs are identical. Both algorithms solve Hanoi in the same way.\n";
	}
	else {
		cout << "RESULT: Outputs differ.\n";
	}

	return 0;
}
