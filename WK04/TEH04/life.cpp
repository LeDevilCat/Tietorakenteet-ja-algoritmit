#include "life.h"
#include "Utility.h"
#include <iostream>
#include <string>
using namespace std;

int maxrow = 20, maxcol = 60;  //  default grid dimensions

int Life::neighbor_count(int row, int col)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell within the grid.
Post: The number of living neighbors of the specified cell is returned.
*/

{
   int i, j;
   int count = 0;
   
   // Determine loop bounds once, before nested loops
   int row_lower = (row == 0) ? 0 : row - 1;
   int row_upper = (row == maxrow - 1) ? maxrow - 1 : row + 1;
   int col_lower = (col == 0) ? 0 : col - 1;
   int col_upper = (col == maxcol - 1) ? maxcol - 1 : col + 1;
   
   for (i = row_lower; i <= row_upper; i++)
      for (j = col_lower; j <= col_upper; j++)
         count += grid[i][j];  //  Increase the count if neighbor is alive.
   count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
   return count;
}

void Life::update()
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/

{
   int row, col;
   int new_grid[MAXROW][MAXCOL];

   for (row = 0; row < maxrow; row++)
      for (col = 0; col < maxcol; col++)
         switch (neighbor_count(row, col)) {
         case 2:
            new_grid[row][col] = grid[row][col];  //  Status stays the same.
            break;
         case 3:
            new_grid[row][col] = 1;                //  Cell is now alive.
            break;
         default:
            new_grid[row][col] = 0;                //  Cell is now dead.
         }

   for (row = 0; row < maxrow; row++)
      for (col = 0; col < maxcol; col++)
         grid[row][col] = new_grid[row][col];
}


void instructions()
/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/

{
   cout << "Welcome to Conway's game of Life." << endl;
   cout << "This game uses a grid of size "
        << maxrow << " by " << maxcol << " in which" << endl;
   cout << "each cell can either be occupied by an organism or not." << endl;
   cout << "The occupied cells change from generation to generation" << endl;
   cout << "according to the number of neighboring cells which are alive."
        << endl;
}


void Life::initialize()
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{
   int row, col;
   
   // Ask user for grid dimensions
   cout << "Enter grid dimensions (rows columns, max " << MAXROW << " x " << MAXCOL << "): ";
   cin >> maxrow >> maxcol;
   
   // Validate dimensions
   if (maxrow < 1 || maxrow > MAXROW || maxcol < 1 || maxcol > MAXCOL) {
      cout << "Invalid dimensions. Using default 20 x 60." << endl;
      maxrow = 20;
      maxcol = 60;
   }
   
   for (row = 0; row < maxrow; row++)
      for (col = 0; col < maxcol; col++)
         grid[row][col] = 0;
   
   cout << "Enter the initial configuration (" << maxrow << " rows)." << endl;
   cout << "Use 'x' for living cells and blank spaces for dead cells." << endl;
   cout << "Each row should have " << maxcol << " characters." << endl;
   
   cin.ignore();  // Clear the newline left in the buffer
   
   string line;
   for (row = 0; row < maxrow; row++) {
      cout << "Row " << row << ": ";
      getline(cin, line);
      
      // Process each character in the line
      for (col = 0; col < maxcol && col < line.length(); col++) {
         if (line[col] == 'x' || line[col] == 'X')
            grid[row][col] = 1;
         else
            grid[row][col] = 0;
      }
      
      // Fill remaining columns with 0 if line is shorter than maxcol
      for (; col < maxcol; col++)
         grid[row][col] = 0;
   }
}


void Life::print()
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
   int row, col;
   cout << "\nThe current Life configuration is:" <<endl;
   for (row = 0; row < maxrow; row++) {
      for (col = 0; col < maxcol; col++)
         if (grid[row][col] == 1) cout << '*';
         else cout << ' ';
      cout << endl;
   }
   cout << endl;
}