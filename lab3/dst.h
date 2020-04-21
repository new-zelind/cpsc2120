#ifndef DST_H
#define DST_H
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

class Graph{

   private:
	  
	  struct Node{
		 double x;						  //x coordinate
		 double y;						  //y coordinate
		 Node* next;					  //pointer to next node
		 Node(double xCoord, double yCoord, Node * n){x = xCoord; y=yCoord; next=n;};
										  //Overriden constructor
		 Node(){x=0; y=0; next = NULL;};  //Default constructor
	  };

	  int size;							  //the size of the superimposed
										  //"array:
	  Node *** table;					  //pointer to the hash table
	  
   public:
	  Graph();							  //constructor
	  ~Graph();							  //destructor
	  void readData(void);				  //function to read in the data
	  void insert(double x, double y);	  //function to insert a new point
	  void findDistance(void);			  //function to find the smallest
										  //distance between points
};

#endif
