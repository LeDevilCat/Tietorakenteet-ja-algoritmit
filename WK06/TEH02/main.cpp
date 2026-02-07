#include <iostream>
#include <vector>

// Minimal Stack implementation (Stack_entry = int) for exercises
using Stack_entry = int;
enum Error_code { success, overflow, underflow, fail_code };

class Stack {
private:
    static const int MAX = 100;
    Stack_entry data[MAX];
    int top_index;
public:
    Stack() : top_index(0) {}
    bool empty() const { return top_index == 0; }
    bool full() const { return top_index == MAX; }
    int size() const { return top_index; }

    Error_code push(const Stack_entry &x) {
        if (full()) return overflow;
        data[top_index++] = x;
        return success;
    }

    Error_code pop(Stack_entry &x) {
        if (empty()) return underflow;
        x = data[--top_index];
        return success;
    }

    Error_code top(Stack_entry &x) const {
        if (empty()) return underflow;
        x = data[top_index - 1];
        return success;
    }
};

// Exercise 2 implementations

// (a) leaves s unchanged and returns whether it's full
bool full(Stack &s) {
    // Use public method full(); does not change s
    return s.full();
}

// (b) remove top entry and return via t
Error_code pop_top(Stack &s, Stack_entry &t) {
    return s.pop(t);
}

// (c) delete all entries and return s empty
void clear(Stack &s) {
    Stack_entry tmp;
    while (s.pop(tmp) == success) { /* pop until empty */ }
}

// (d) leave s unchanged and return count of entries
int size(Stack &s) {
    // Use public size() method
    return s.size();
}

// (e) delete all occurrences of x, preserve relative order of remaining entries
void delete_all(Stack &s, Stack_entry x) {
    Stack temp;
    Stack_entry val;

    // Pop all entries from s; push only those != x into temp
    while (s.pop(val) == success) {
        if (val != x) {
            temp.push(val);
        }
    }

    // Now temp has kept elements in reverse of desired order; restore to s
    while (temp.pop(val) == success) {
        s.push(val);
    }
}

// --- small test driver ---
void print_stack_copy(Stack s, const char *name) {
    // pass-by-value copies stack (here we rely on copy semantics of this simple class)
    std::vector<Stack_entry> vals;
    Stack_entry v;
    while (s.pop(v) == success) vals.push_back(v);

    std::cout << name << " (top..bottom): ";
    for (size_t i = 0; i < vals.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << vals[i];
    }
    std::cout << '\n';
}

int main() {
    Stack s;
    for (int i = 1; i <= 7; ++i) s.push(i); // 1..7

    print_stack_copy(s, "s before");

    std::cout << "full(s)? " << (full(s) ? "yes" : "no") << '\n';
    std::cout << "size(s) = " << size(s) << '\n';

    Stack_entry t;
    if (pop_top(s, t) == success) std::cout << "popped top = " << t << '\n';
    else std::cout << "pop_top failed\n";

    print_stack_copy(s, "s after pop_top");

    // delete all occurrences of 3
    delete_all(s, 3);
    print_stack_copy(s, "s after delete_all(3)");

    // clear
    clear(s);
    print_stack_copy(s, "s after clear");

    return 0;
}
