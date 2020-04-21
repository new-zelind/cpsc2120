//Zach Lindler
//CPSC 2121
//Lab 3, main.cpp

#include "dst.h"

int main(void){
   Graph g;			 //Declare an instance of the graph
   g.readData();	 //read in the data
   g.findDistance(); //find the smallest distance
   return 0;
}
