/* Program extracts from Chapter 2 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


// Section 2.1:


#include   <iostream>
#include   <stack>
#include   <string>

using namespace std;

int main()
/*
Pre:   The user supplies a line of text.
Post:  The program outputs whether the line is a palindrome or not.
Uses:  The STL class stack and its methods
*/

{
   string line;
   stack<char> characters;  //  declares and initializes a stack of characters

   cout << "Type in a line of text." << endl
        << "The program will check if it is a palindrome." << endl;
   getline(cin, line);

   // Push all characters onto the stack
   for (int i = 0; i < line.length(); i++) {
      characters.push(line[i]);
   }

   // Check if the line is a palindrome
   bool isPalindrome = true;
   for (int i = 0; i < line.length(); i++) {
      if (line[i] != characters.top()) {
         isPalindrome = false;
         break;
      }
      characters.pop();
   }

   cout << endl << endl;
   if (isPalindrome) {
      cout << "The text is a palindrome!" << endl;
   } else {
      cout << "The text is not a palindrome." << endl;
   }
}
