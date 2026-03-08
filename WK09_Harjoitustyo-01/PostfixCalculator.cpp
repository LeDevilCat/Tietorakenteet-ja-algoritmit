#include "PostfixCalculator.h"

#include <cmath>
#include <sstream>
#include <vector>

PostfixCalculator::PostfixCalculator() {}

Error_code PostfixCalculator::process_token(const std::string &token)
/*
Pre:   token is a single postfix item (number or operator).
Post:  token is executed against the calculator stack.
Uses:  Stack operations and arithmetic helpers.
*/
{
   Stack_entry value = 0.0;

   if (try_parse_number(token, value)) {
      return data.push(value);
   }

   if (token.size() != 1) {
      return bad_input;
   }

   const char op = token[0];

   switch (op) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
      case '^':
         return binary_operation(op);
      case 'v':
         return unary_operation(op);
      case 'x':
         return data.exchange_top();
      case 's':
         return sum_operation();
      case 'a':
         return average_operation();
      default:
         return invalid_operation;
   }
}

Error_code PostfixCalculator::result(Stack_entry &value) const {
   return data.top(value);
}

int PostfixCalculator::stack_size() const {
   return data.size();
}

void PostfixCalculator::reset() {
   data.clear();
}

bool PostfixCalculator::try_parse_number(const std::string &token, Stack_entry &value) const {
   std::istringstream input(token);
   input >> value;
   return input && input.eof();
}

Error_code PostfixCalculator::binary_operation(char op) {
   Stack_entry right = 0.0;
   Stack_entry left = 0.0;

   if (data.pop(right) != success || data.pop(left) != success) {
      return underflow;
   }

   Stack_entry answer = 0.0;

   switch (op) {
      case '+':
         answer = left + right;
         break;
      case '-':
         answer = left - right;
         break;
      case '*':
         answer = left * right;
         break;
      case '/':
         if (right == 0.0) {
            return divide_by_zero;
         }
         answer = left / right;
         break;
      case '%':
         if (right == 0.0) {
            return divide_by_zero;
         }
         answer = std::fmod(left, right);
         break;
      case '^':
         answer = std::pow(left, right);
         break;
      default:
         return invalid_operation;
   }

   return data.push(answer);
}

Error_code PostfixCalculator::unary_operation(char op) {
   Stack_entry value = 0.0;

   if (data.pop(value) != success) {
      return underflow;
   }

   if (op == 'v') {
      if (value < 0.0) {
         return bad_input;
      }
      return data.push(std::sqrt(value));
   }

   return invalid_operation;
}

Error_code PostfixCalculator::sum_operation() {
   if (data.empty()) {
      return underflow;
   }

   const int count = data.size();
   Stack_entry total = 0.0;
   Stack_entry value = 0.0;

   for (int i = 0; i < count; ++i) {
      data.pop(value);
      total += value;
   }

   return data.push(total);
}

Error_code PostfixCalculator::average_operation() {
   if (data.empty()) {
      return underflow;
   }

   const int count = data.size();
   Stack_entry total = 0.0;
   Stack_entry value = 0.0;

   for (int i = 0; i < count; ++i) {
      data.pop(value);
      total += value;
   }

   return data.push(total / static_cast<Stack_entry>(count));
}