#ifndef POSTFIX_CALCULATOR_H
#define POSTFIX_CALCULATOR_H

#include <string>

#include "Stack.h"

class PostfixCalculator {
public:
   PostfixCalculator();

   Error_code process_token(const std::string &token);
   Error_code result(Stack_entry &value) const;
   int stack_size() const;
   void reset();

private:
   Stack data;

   bool try_parse_number(const std::string &token, Stack_entry &value) const;
   Error_code binary_operation(char op);
   Error_code unary_operation(char op);
   Error_code sum_operation();
   Error_code average_operation();
};

#endif