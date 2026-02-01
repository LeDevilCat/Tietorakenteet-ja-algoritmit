/* Program to implement and test the full() method of Extended_stack class.
   Part (b) of assignment 5.
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

// Test driver program for full() method
int main()
{
    Extended_stack test_stack;
    Stack_entry item;

    cout << "=== Testing full() method ===" << endl << endl;

    // Test 1: Check full on empty stack
    cout << "Test 1: Check full on empty stack" << endl;
    cout << "Stack size: " << test_stack.size() << endl;
    cout << "Stack is full? " << (test_stack.full() ? "Yes" : "No") << endl;
    cout << endl;

    // Test 2: Check full after adding items
    cout << "Test 2: Check full while adding items" << endl;
    cout << "Adding items one by one and checking full status:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << "  Adding item " << i << "... ";
        if (test_stack.push(i * 10) == success) {
            cout << "Size: " << test_stack.size() << ", Full? " << (test_stack.full() ? "Yes" : "No") << endl;
        }
    }
    cout << endl;

    // Test 3: Try to overflow and check full status
    cout << "Test 3: Try to overflow when full" << endl;
    cout << "Stack is currently full? " << (test_stack.full() ? "Yes" : "No") << endl;
    cout << "Stack size: " << test_stack.size() << " (max: " << maxstack << ")" << endl;
    cout << "\nAttempting to push another item..." << endl;
    Error_code result = test_stack.push(999);
    if (result == overflow)
        cout << "Push returned: overflow (as expected)" << endl;
    cout << "Stack is still full? " << (test_stack.full() ? "Yes" : "No") << endl;
    cout << "Stack size: " << test_stack.size() << endl;
    cout << endl;

    // Test 4: Pop items and check full status
    cout << "Test 4: Pop items and check full status" << endl;
    cout << "Popping items one by one:" << endl;
    for (int i = 10; i >= 1; i--) {
        if (test_stack.top(item) == success) {
            cout << "  Top element: " << item << ", ";
            test_stack.pop();
            cout << "After pop - Size: " << test_stack.size() << ", Full? " << (test_stack.full() ? "Yes" : "No") << endl;
        }
    }
    cout << endl;

    // Test 5: Full status on empty stack after operations
    cout << "Test 5: Full status after clearing all items" << endl;
    cout << "Stack size: " << test_stack.size() << endl;
    cout << "Stack is empty? " << (test_stack.empty() ? "Yes" : "No") << endl;
    cout << "Stack is full? " << (test_stack.full() ? "Yes" : "No") << endl;
    cout << endl;

    // Test 6: Fill exactly to capacity and pop one
    cout << "Test 6: Fill to capacity then pop one" << endl;
    cout << "Filling to capacity..." << endl;
    for (int i = 1; i <= maxstack; i++) {
        test_stack.push(i);
    }
    cout << "Stack size: " << test_stack.size() << endl;
    cout << "Stack is full? " << (test_stack.full() ? "Yes" : "No") << endl;

    cout << "\nPopping one item..." << endl;
    test_stack.pop();
    cout << "Stack size: " << test_stack.size() << endl;
    cout << "Stack is full? " << (test_stack.full() ? "Yes" : "No") << endl;
    cout << endl;

    cout << "=== All tests completed ===" << endl;

    return 0;
}
