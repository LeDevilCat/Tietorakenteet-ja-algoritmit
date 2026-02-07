#include <iostream>
#include <vector>
#include <cmath>

// Simple Stack for integers
class Stack {
private:
    std::vector<long long> data;
public:
    void push(long long v) { data.push_back(v); }
    bool pop(long long &out) {
        if (data.empty()) return false;
        out = data.back(); data.pop_back(); return true;
    }
    bool empty() const { return data.empty(); }
};

int main() {
    long long n;
    if (!(std::cin >> n)) return 0;

    if (n < 0) n = -n; // handle negative numbers by absolute value

    Stack st;

    // Factorization: try divisors starting from 2 upwards
    for (long long d = 2; d * d <= n; ++d) {
        while (n % d == 0) {
            st.push(d);
            n /= d;
        }
    }
    if (n > 1) st.push(n); // remaining prime

    // Pop and print to produce descending order
    bool first = true;
    long long v;
    while (st.pop(v)) {
        if (!first) std::cout << ' ';
        std::cout << v;
        first = false;
    }
    if (!first) std::cout << '\n';

    return 0;
}
