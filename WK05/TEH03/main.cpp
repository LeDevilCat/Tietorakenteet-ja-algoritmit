/* Program to reverse a line of text using a Stack.
   Uses the Stack class from the lecture material.
*/

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

typedef char Stack_entry;

int main()
/*
Pre:   The user supplies a line of text.
Post:  The characters are printed in reverse order using a Stack.
Uses:  The Stack class and its methods
*/
{
   string line;
   Stack stored_characters;
   char character;

   cout << "Type in a line of text." << endl
        << "The characters will be printed in reverse order." << endl;
   getline(cin, line);

   // Push all characters onto the stack
   for (int i = 0; i < line.length(); i++) {
      if (stored_characters.push(line[i]) == overflow) {
         cout << "Warning: Stack full, lost character" << endl;
      }
   }

   cout << endl << endl;
   
   // Pop and print characters in reverse order
   while (!stored_characters.empty()) {
      if (stored_characters.top(character) == success) {
         cout << character;
         stored_characters.pop();
      }
   }
   cout << endl;

   return 0;
}
