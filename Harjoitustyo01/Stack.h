#ifndef STACK_H
#define STACK_H

#include <vector>

typedef double Stack_entry;

enum Error_code {
   success,
   overflow,
   underflow,
   bad_input,
   divide_by_zero,
   invalid_operation
};

class Stack {
public:
   bool empty() const;
   int size() const;
   Error_code push(const Stack_entry &item);
   Error_code pop(Stack_entry &item);
   Error_code top(Stack_entry &item) const;
   Error_code exchange_top();
   void clear();

private:
   std::vector<Stack_entry> entries;
};

#endif