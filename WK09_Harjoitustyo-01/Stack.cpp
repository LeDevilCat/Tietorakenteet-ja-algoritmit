#include "Stack.h"

#include <utility>

bool Stack::empty() const {
   return entries.empty();
}

int Stack::size() const {
   return static_cast<int>(entries.size());
}

Error_code Stack::push(const Stack_entry &item) {
   entries.push_back(item);
   return success;
}

Error_code Stack::pop(Stack_entry &item) {
   if (empty()) {
      return underflow;
   }

   item = entries.back();
   entries.pop_back();
   return success;
}

Error_code Stack::top(Stack_entry &item) const {
   if (empty()) {
      return underflow;
   }

   item = entries.back();
   return success;
}

Error_code Stack::exchange_top() {
   if (size() < 2) {
      return underflow;
   }

   std::swap(entries[entries.size() - 1], entries[entries.size() - 2]);
   return success;
}

void Stack::clear() {
   entries.clear();
}