#ifndef LIFE_H
#define LIFE_H

const int MAXROW = 80, MAXCOL = 200;    //  maximum grid dimensions
extern int maxrow, maxcol;              //  actual grid dimensions set by user

class Life {
public:
   void initialize();
   void print();
   void update();
private:
   int grid[MAXROW + 2][MAXCOL + 2];  //  allows for two extra rows and columns
   int neighbor_count(int row, int col);
};

#endif
