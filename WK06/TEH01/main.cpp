#include <iostream>
#include <vector>
#include <string>

// Error codes for stack operations
enum Error_code { success, overflow, underflow, fail_code };

class Stack {
private:
    static const int MAX = 100;
    int data[MAX];
    int top_index; // number of items in stack

public:
    Stack() : top_index(0) {}
    bool empty() const { return top_index == 0; }
    bool full() const { return top_index == MAX; }
    int size() const { return top_index; }

    Error_code push(int value) {
        if (full()) return overflow;
        data[top_index++] = value;
        return success;
    }

    Error_code pop(int &value) {
        if (empty()) return underflow;
        value = data[--top_index];
        return success;
    }

    Error_code top(int &value) const {
        if (empty()) return underflow;
        value = data[top_index - 1];
        return success;
    }

    // Friend declaration for the friend-version of copy_stack (part C)
    friend Error_code copy_stack_friend(Stack &dest, const Stack &source);
};

// -------------------------
// Tehtävä 1, osa A
// (a) Simply use an assignment statement: dest = source;
// -------------------------
Error_code copy_stack_assign(Stack &dest, Stack &source) {
    dest = source; // uses compiler-generated assignment
    return success;
}

// -------------------------
// Tehtävä 1, osa B
// (b) Use Stack methods and a temporary Stack to retrieve entries from
//     source and add each entry to dest, restoring source.
// -------------------------
Error_code copy_stack_using_methods(Stack &dest, Stack &source) {
    Stack temp;
    int value;

    // Move all items from source to temp (this empties source)
    while (source.pop(value) == success) {
        if (temp.push(value) != success) return fail_code;
    }

    // Move items from temp back to source and also push into dest
    while (temp.pop(value) == success) {
        if (source.push(value) != success) return fail_code;
        if (dest.push(value) != success) return fail_code;
    }

    return success;
}

// -------------------------
// Tehtävä 1, osa C
// (c) Friend function that copies using access to private members.
// -------------------------
Error_code copy_stack_friend(Stack &dest, const Stack &source) {
    dest.top_index = source.top_index;
    for (int i = 0; i < source.top_index; ++i) dest.data[i] = source.data[i];
    return success;
}

// Utility: copy for printing without mutating original (uses friend copy)
void print_stack(const Stack &s, const std::string &name) {
    Stack temp;
    copy_stack_friend(temp, s);
    std::vector<int> vals;
    int v;
    while (temp.pop(v) == success) vals.push_back(v);

    std::cout << name << " (top..bottom): ";
    for (size_t i = 0; i < vals.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << vals[i];
    }
    std::cout << "\n";
}

// Answers to the conceptual questions (as comments):
/*
Which of these is easiest to write?
- The assignment (`copy_stack_assign`) is the easiest to write.

Which will run most quickly if the stack is nearly full?
- The friend version (`copy_stack_friend`) is fastest when nearly full because it copies the internal array directly with minimal per-element overhead.

Which will run most quickly if the stack is nearly empty?
- For nearly empty stacks, the assignment (`dest = source`) typically is fastest because it is implemented by the compiler/runtime efficiently (often a shallow copy or small loop), but the friend version is also very fast; method-based version does more push/pop overhead.

Which would be the best method if the implementation might be changed?
- Use the public-methods version (`copy_stack_using_methods`) because it relies only on the class's public interface and is robust to changes in internal representation.

In which could we pass the parameter source as a constant reference?
- The friend version `copy_stack_friend` can take `const Stack &source` since it accesses private data directly and does not modify the source. The assignment form can also accept `const Stack&` for the source if we wrote a function wrapper that assigns from a const ref. The methods-based version cannot take a `const` source because it uses `pop`/`push` to temporarily modify and restore `source`.
*/

int main() {
    Stack s;
    for (int i = 1; i <= 5; ++i) s.push(i); // push 1..5

    std::cout << "Original stack:\n";
    print_stack(s, "s");

    // Test assignment copy
    Stack dest1;
    copy_stack_assign(dest1, s);
    print_stack(dest1, "dest1 (assign)");

    // Test methods-based copy (note: this will temporarily modify s but restore it)
    Stack dest2;
    copy_stack_using_methods(dest2, s);
    print_stack(dest2, "dest2 (methods)");
    print_stack(s, "s (after methods copy, should be unchanged)");

    // Test friend copy
    Stack dest3;
    copy_stack_friend(dest3, s);
    print_stack(dest3, "dest3 (friend)");

    return 0;
}
