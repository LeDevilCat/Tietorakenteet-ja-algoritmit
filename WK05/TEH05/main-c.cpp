/* Program to implement and test the size() method of Extended_stack class.
   Part (c) of assignment 5.
*/

#include <iostream>

using namespace std;

// Error code enumeration
enum Error_code { success, overflow, underflow, fail };

// Stack entry type
typedef int Stack_entry;

const int maxstack = 10;

class Extended_stack {
public:
    Extended_stack();
    Error_code pop();
    Error_code push(const Stack_entry &item);
    Error_code top(Stack_entry &item) const;
    bool empty() const;
    void clear();              // Reset the stack to be empty.
    bool full() const;         // If the stack is full, return true; else return false.
    int size() const;          // Return the number of entries in the stack.

private:
    int count;
    Stack_entry entry[maxstack];
};

// Constructor: Initialize the stack to be empty
Extended_stack::Extended_stack()
{
    count = 0;
}

// Push an item onto the stack
Error_code Extended_stack::push(const Stack_entry &item)
{
    Error_code outcome = success;
    if (count >= maxstack)
        outcome = overflow;
    else
        entry[count++] = item;
    return outcome;
}

// Pop the top item from the stack
Error_code Extended_stack::pop()
{
    Error_code outcome = success;
    if (count == 0)
        outcome = underflow;
    else
        --count;
    return outcome;
}

// Return the top item without removing it
Error_code Extended_stack::top(Stack_entry &item) const
{
    Error_code outcome = success;
    if (count == 0)
        outcome = underflow;
    else
        item = entry[count - 1];
    return outcome;
}

// Check if the stack is empty
bool Extended_stack::empty() const
{
    return (count == 0);
}

// (a) clear(): Reset the stack to be empty.
void Extended_stack::clear()
{
    count = 0;
}

// (b) full(): Return true if the stack is full, else false.
bool Extended_stack::full() const
{
    return (count >= maxstack);
}

// (c) size(): Return the number of entries in the stack.
int Extended_stack::size() const
{
    return count;
}

// Test driver program for size() method
int main()
{
    Extended_stack test_stack;
    Stack_entry item;

    cout << "=== Testing size() method ===" << endl << endl;

    // Test 1: Size of new stack
    cout << "Test 1: Size of newly created stack" << endl;
    cout << "Stack size: " << test_stack.size() << endl;
    cout << "Expected: 0" << endl;
    cout << endl;

    // Test 2: Size increases with push
    cout << "Test 2: Size increases with each push" << endl;
    cout << "Pushing 5 items..." << endl;
    for (int i = 1; i <= 5; i++) {
        test_stack.push(i * 100);
        cout << "  After push " << i << ": size = " << test_stack.size() << endl;
    }
    cout << endl;

    // Test 3: Size decreases with pop
    cout << "Test 3: Size decreases with each pop" << endl;
    cout << "Popping 3 items..." << endl;
    for (int i = 1; i <= 3; i++) {
        test_stack.pop();
        cout << "  After pop " << i << ": size = " << test_stack.size() << endl;
    }
    cout << endl;

    // Test 4: Size reaches maximum
    cout << "Test 4: Size reaching maximum capacity" << endl;
    cout << "Current size: " << test_stack.size() << endl;
    cout << "Maximum capacity: " << maxstack << endl;
    cout << "Items needed to fill: " << (maxstack - test_stack.size()) << endl;

    cout << "\nFilling the stack to capacity..." << endl;
    int items_added = 0;
    for (int i = 1; i <= 10; i++) {
        if (test_stack.push(i * 1000) == success) {
            items_added++;
        } else {
            break;
        }
    }
    cout << "Added " << items_added << " items" << endl;
    cout << "Stack size: " << test_stack.size() << endl;
    cout << endl;

    // Test 5: Size after clear
    cout << "Test 5: Size after clear" << endl;
    cout << "Size before clear: " << test_stack.size() << endl;
    test_stack.clear();
    cout << "Size after clear: " << test_stack.size() << endl;
    cout << endl;

    // Test 6: Verify empty stack size
    cout << "Test 6: Verify empty stack size" << endl;
    cout << "Stack is empty? " << (test_stack.empty() ? "Yes" : "No") << endl;
    cout << "Stack size: " << test_stack.size() << endl;
    cout << endl;

    // Test 7: Multiple push/pop cycles
    cout << "Test 7: Size during multiple push/pop cycles" << endl;
    cout << "Cycle 1: Push 3 items" << endl;
    for (int i = 1; i <= 3; i++) {
        test_stack.push(i);
    }
    cout << "  Size: " << test_stack.size() << endl;

    cout << "Cycle 1: Pop all items" << endl;
    while (!test_stack.empty()) {
        test_stack.pop();
    }
    cout << "  Size: " << test_stack.size() << endl;

    cout << "Cycle 2: Push 7 items" << endl;
    for (int i = 1; i <= 7; i++) {
        test_stack.push(i * 10);
    }
    cout << "  Size: " << test_stack.size() << endl;

    cout << "Cycle 2: Pop 4 items" << endl;
    for (int i = 0; i < 4; i++) {
        test_stack.pop();
    }
    cout << "  Size: " << test_stack.size() << endl;
    cout << endl;

    // Test 8: Size consistency
    cout << "Test 8: Size consistency check" << endl;
    cout << "Filling stack to capacity..." << endl;
    test_stack.clear();
    int expected_size = 0;
    bool consistent = true;

    for (int i = 1; i <= maxstack; i++) {
        test_stack.push(i);
        expected_size++;
        if (test_stack.size() != expected_size) {
            cout << "  Inconsistency at push " << i << endl;
            consistent = false;
        }
    }

    cout << "Popping all items..." << endl;
    while (!test_stack.empty()) {
        test_stack.pop();
        expected_size--;
        if (test_stack.size() != expected_size) {
            cout << "  Inconsistency during pop" << endl;
            consistent = false;
        }
    }

    if (consistent)
        cout << "  All sizes consistent throughout operations" << endl;
    cout << "  Final size: " << test_stack.size() << endl;
    cout << endl;

    cout << "=== All tests completed ===" << endl;

    return 0;
}
