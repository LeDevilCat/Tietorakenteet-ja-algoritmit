#include "Utility.h"
#include "life.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main()  //  Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

{
   Life configuration;
   configuration.initialize();
   configuration.print();
   
   // Ask for animation settings
   int delay_seconds;
   int num_generations;
   
   cout << "Enter delay between generations (in seconds): ";
   cin >> delay_seconds;
   
   if (delay_seconds < 0) delay_seconds = 0;
   
   cout << "Enter number of generations to run (0 for infinite, terminate with Ctrl-C): ";
   cin >> num_generations;
   
   if (num_generations <= 0) {
      // Infinite mode
      cout << "Running continuously. Press Ctrl-C to stop." << endl;
      int generation = 1;
      while (true) {
         this_thread::sleep_for(chrono::seconds(delay_seconds));
         configuration.update();
         cout << "Generation " << generation << ":" << endl;
         configuration.print();
         generation++;
      }
   }
   else {
      // Run for specified number of generations
      for (int i = 1; i <= num_generations; i++) {
         this_thread::sleep_for(chrono::seconds(delay_seconds));
         configuration.update();
         cout << "Generation " << i << ":" << endl;
         configuration.print();
      }
   }
   
   // Ask if the user wants to save the final configuration
   cout << "Save the final configuration to a file? " << endl;
   if (user_says_yes()) {
      configuration.save_to_file();
   }
}
