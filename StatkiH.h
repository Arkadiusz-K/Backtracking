#pragma once


#define DEPTH_MIN 7

#define N 10 
//x
#define M 10 
//y

int CreateMatrix( int*** pTab, int nRow, int nCol );

int DeleteMatrix( int*** pTab, int nRow );


int move( int** pTab, int nRow, int nCol, int nDepth, int move_nr, int x, int y, int* px, int* py, int** pRoot );

int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest );



// Typ wyliczeniowy (do zmiennych, które mog¹ przyjmowaæ tylko z górt okreœlone wartoœci) 
typedef enum { UP, RIGHT, DOWN, LEFT } kierunek;