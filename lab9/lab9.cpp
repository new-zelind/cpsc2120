// Zach Lindler
// CPSC 2120
// Dr. Dean
// lab9.cpp, Lab 9

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int** board;
int numSolutions;

bool checkClear(int row, int col, int size){

   int i, j;

   //check rest of column
   for(i = 0; i<size; i++){
	  if(board[i][col] == 1){return false;}
   }
   
   //check first diagonal (SE -> NW)
   for(i = row, j=col; i>=0 && j>=0; i--, j--){
		 if(board[i][j] == 1){return false;}
   }

   //check other diagonal (SW -> NE)
   for(i = row, j=col; i >= 0 && j < size; i--, j++){
		 if(board[i][j] == 1){return false;}
   }

   //if these conditions are met, then a queen can legally be placed there.
   return true;
}

void check_row(int row, int size){
   
   //base case - past the end of the table, this means we
   //found something that worked;
   if(row >= size){
	  numSolutions++;
	  return;
   }

   //iterate through each space in the row
   for(int i=0; i<size; i++){
	  
	  //if that space is clear, set the queen value in that space to '1', then
	  // call the check_row function again recursively, iterating to the next row.
	  if(checkClear(row, i, size) == true){
		 board[row][i] = 1;
		 check_row(row+1, size);

		 //after the recursive function ends, reset that space to '0', removing
		 // the queen.
		 board[row][i] = 0;
	  }
   }
}

int main(int argc, char* argv[]){
   
   //command line arg verification
   if(argc != 2){
	  cout<<"Usage: ./<executable> <size>"<<endl;
	  return 1;
   }
   
   //get input size from command line and create a 2d array of size n^2;
   int size = atoi(argv[1]);
   board = new int*[size];
   for(int i=0; i<size; i++){
	  board[i] = new int[size];
   }
   
   //initialize the array to all 0's.
   for(int i=0; i<size; i++){
	  for(int j=0; j<size; j++){
		 board[i][j] = 0;
	  }
   }

   //n-queens algorithm
   check_row(0, size);

   //print the number of solutions.
   cout << numSolutions <<" solutions."<<endl;   

   return 0;
}
