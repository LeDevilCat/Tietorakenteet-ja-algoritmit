#include "life.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
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
   
   // Initialize grid to all dead cells
   for (row = 0; row < MAXROW; row++)
      for (col = 0; col < MAXCOL; col++)
         grid[row][col] = 0;
   
   // Ask user for input method
   cout << "Read initial configuration from a file? ";
   bool from_file = user_says_yes();
   
   if (from_file) {
      // Read from file
      string filename;
      cout << "Enter the filename: ";
      cin >> filename;
      
      ifstream input_file(filename);
      if (!input_file) {
         cout << "Cannot open file " << filename << endl;
         cout << "Using default configuration." << endl;
         maxrow = 20;
         maxcol = 60;
         return;
      }
      
      // Read the first line (configuration name/comment)
      string config_name;
      getline(input_file, config_name);
      cout << "Configuration: " << config_name << endl;
      
      // Read rows and determine grid dimensions
      string line;
      row = 0;
      maxcol = 0;
      
      while (getline(input_file, line) && row < MAXROW) {
         // Update maxcol if this line is longer
         if (line.length() > maxcol)
            maxcol = line.length();
         
         // Process each character in the line
         for (col = 0; col < line.length() && col < MAXCOL; col++) {
            if (line[col] == 'x' || line[col] == 'X')
               grid[row][col] = 1;
            else
               grid[row][col] = 0;
         }
         row++;
      }
      
      maxrow = row;
      input_file.close();
      
      // Validate dimensions
      if (maxrow < 1 || maxcol < 1) {
         cout << "Invalid configuration in file. Using default." << endl;
         maxrow = 20;
         maxcol = 60;
      }
      else if (maxcol > MAXCOL) {
         maxcol = MAXCOL;
      }
      
      cout << "Grid size: " << maxrow << " x " << maxcol << endl;
   }
   else {
      // Read from keyboard
      cout << "Enter grid dimensions (rows columns, max " << MAXROW << " x " << MAXCOL << "): ";
      cin >> maxrow >> maxcol;
      
      // Validate dimensions
      if (maxrow < 1 || maxrow > MAXROW || maxcol < 1 || maxcol > MAXCOL) {
         cout << "Invalid dimensions. Using default 20 x 60." << endl;
         maxrow = 20;
         maxcol = 60;
      }
      
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


void Life::save_to_file()
/*
Pre:  The Life object contains a configuration.
Post: The configuration is saved to a file specified by the user.
      The file format has a comment/name on the first line,
      followed by rows with 'x' for living cells and spaces for dead cells.
*/

{
   string filename, config_name;
   
   cout << "Enter the filename to save to: ";
   cin >> filename;
   
   ofstream output_file(filename);
   if (!output_file) {
      cout << "Cannot create file " << filename << endl;
      return;
   }
   
   cin.ignore();  // Clear the newline
   cout << "Enter a name/description for this configuration: ";
   getline(cin, config_name);
   
   // Write the configuration name/comment as the first line
   output_file << config_name << endl;
   
   // Write each row
   for (int row = 0; row < maxrow; row++) {
      for (int col = 0; col < maxcol; col++) {
         if (grid[row][col] == 1)
            output_file << 'x';
         else
            output_file << ' ';
      }
      output_file << endl;
   }
   
   output_file.close();
   cout << "Configuration saved to " << filename << endl;
}