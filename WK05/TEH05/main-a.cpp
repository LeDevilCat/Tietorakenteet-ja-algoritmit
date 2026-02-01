/* Program to implement and test the clear() method of Extended_stack class.
   Part (a) of assignment 5.
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

// Test driver program for clear() method
int main()
{
    Extended_stack test_stack;
    Stack_entry item;

    cout << "=== Testing clear() method ===" << endl << endl;

    // Test 1: Clear an empty stack
    cout << "Test 1: Clear an empty stack" << endl;
    cout << "Stack size before clear: " << test_stack.size() << endl;
    test_stack.clear();
    cout << "Stack size after clear: " << test_stack.size() << endl;
    cout << "Stack is empty? " << (test_stack.empty() ? "Yes" : "No") << endl;
    cout << endl;

    // Test 2: Push some items then clear
    cout << "Test 2: Push items then clear" << endl;
    cout << "Pushing items: 10, 20, 30, 40, 50" << endl;
    test_stack.push(10);
    test_stack.push(20);
    test_stack.push(30);
    test_stack.push(40);
    test_stack.push(50);

    cout << "Stack size after pushing 5 items: " << test_stack.size() << endl;
    if (test_stack.top(item) == success)
        cout << "Top element: " << item << endl;

    cout << "\nClearing the stack..." << endl;
    test_stack.clear();

    cout << "Stack size after clear: " << test_stack.size() << endl;
    cout << "Stack is empty? " << (test_stack.empty() ? "Yes" : "No") << endl;
    cout << endl;

    // Test 3: Verify we can push again after clear
    cout << "Test 3: Push items after clear" << endl;
    cout << "Pushing new items: 100, 200" << endl;
    test_stack.push(100);
    test_stack.push(200);

    cout << "Stack size: " << test_stack.size() << endl;
    if (test_stack.top(item) == success)
        cout << "Top element: " << item << endl;

    cout << "\nClearing again..." << endl;
    test_stack.clear();
    cout << "Stack size after clear: " << test_stack.size() << endl;
    cout << endl;

    // Test 4: Fill stack then clear
    cout << "Test 4: Fill stack then clear" << endl;
    cout << "Filling the stack to capacity (10 items)..." << endl;
    for (int i = 1; i <= 10; i++) {
        test_stack.push(i * 100);
    }

    cout << "Stack size: " << test_stack.size() << endl;
    cout << "Stack is full? " << (test_stack.full() ? "Yes" : "No") << endl;

    cout << "\nClearing the full stack..." << endl;
    test_stack.clear();

    cout << "Stack size after clear: " << test_stack.size() << endl;
    cout << "Stack is empty? " << (test_stack.empty() ? "Yes" : "No") << endl;
    cout << "Stack is full? " << (test_stack.full() ? "Yes" : "No") << endl;
    cout << endl;

    cout << "=== All tests completed ===" << endl;

    return 0;
}
