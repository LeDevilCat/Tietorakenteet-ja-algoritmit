#ifndef LIFE_H
#define LIFE_H

const int MAXROW = 80, MAXCOL = 200;    //  maximum grid dimensions
extern int maxrow, maxcol;              //  actual grid dimensions set by user

class Life {
public:
   void initialize();
   void print();
   void update();
   void save_to_file();
private:
   int grid[MAXROW][MAXCOL];  //  no hedge - exact dimensions
   int neighbor_count(int row, int col);
};

#endif
