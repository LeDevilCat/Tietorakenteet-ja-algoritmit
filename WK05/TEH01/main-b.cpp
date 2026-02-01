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
Post:  The characters are printed in reverse order.
Uses:  The STL class stack and its methods
*/

{
   string line;
   stack<char> characters;  //  declares and initializes a stack of characters

   cout << "Type in a line of text." << endl
        << "The characters will be printed in reverse order." << endl;
   getline(cin, line);

   for (int i = 0; i < line.length(); i++) {
      characters.push(line[i]);
   }

   cout << endl << endl;
   while (!characters.empty()) {
      cout << characters.top();
      characters.pop();
   }
   cout << endl;
}
