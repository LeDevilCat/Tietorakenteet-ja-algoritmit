/* Program to read integers in increasing order and print them in decreasing order using a Stack.
   Uses the Stack class from the lecture material.
*/

#include <iostream>
#include "stack.h"

using namespace std;

typedef int Stack_entry;

int main()
/*
Pre:   The user supplies a sequence of integers in increasing order.
Post:  The integers are printed in decreasing order.
Uses:  The Stack class and its methods
*/
{
   Stack numbers;
   int current, previous;

   cout << "Enter a sequence of integers in increasing order." << endl
        << "When you enter a number that does not exceed the previous one, input ends." << endl
        << "The numbers will then be printed in decreasing order." << endl
        << endl;
   
   cout << "Enter first integer: ";
   cin >> current;
   previous = current;
   
   if (numbers.push(current) == overflow) {
      cout << "Warning: Stack full, lost number" << endl;
   }

   cout << "Enter next integers (non-increasing to stop): ";
   while (cin >> current && current > previous) {
      previous = current;
      if (numbers.push(current) == overflow) {
         cout << "Warning: Stack full, lost number" << endl;
      }
   }

   cout << endl << endl;
   cout << "Numbers in decreasing order:" << endl;
   
   // Pop and print numbers in decreasing order
   while (!numbers.empty()) {
      if (numbers.top(current) == success) {
         cout << current << " ";
         numbers.pop();
      }
   }
   cout << endl;

   return 0;
}
