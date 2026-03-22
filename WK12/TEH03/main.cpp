// WK12 / TEH03
// Exercise 3: Hanoi performance analysis

#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct HanoiStats {
	unsigned long long moves = 0;
	unsigned long long calls = 0;
};

void moveHanoi(int count, int start, int finish, int temp, HanoiStats& stats)
{
	stats.calls++;

	if (count > 0) {
		moveHanoi(count - 1, start, temp, finish, stats);
		stats.moves++;
		moveHanoi(count - 1, temp, finish, start, stats);
	}
}

int main()
{
	const int firstDisks = 10;
	const int lastDisks = 15;

	cout << "Exercise 3 - Towers of Hanoi timing and counts\n";
	cout << "CSV output for Excel:\n";
	cout << "disks,moves,move_calls,cpu_seconds,time_ratio_to_previous\n";

	double previousTime = 0.0;

	for (int disks = firstDisks; disks <= lastDisks; disks++) {
		HanoiStats stats;

		const clock_t begin = clock();
		moveHanoi(disks, 1, 3, 2, stats);
		const clock_t end = clock();

		const double cpuSeconds = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
		const double ratio = (previousTime > 0.0) ? cpuSeconds / previousTime : 0.0;

		cout << disks << ','
			 << stats.moves << ','
			 << stats.calls << ','
			 << fixed << setprecision(6) << cpuSeconds << ',';

		if (disks == firstDisks) {
			cout << "-";
		}
		else {
			cout << fixed << setprecision(3) << ratio;
		}
		cout << '\n';

		previousTime = cpuSeconds;
	}

	return 0;
}
