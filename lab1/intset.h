/* Zach Lindler
   CPSC 2120 - 003
   Lab1, intset.h
   Dean */

#ifndef INTSET_H /* Prevent multiple inclusion... */
#define INTSET_H


//Struct declaration for each node in the list, containing:
struct Node{
   int data;	  //The data contained in the node, and
   Node * next;	  //A pointer to the next node in the list.
};

//Integer list class declaration, containing:
class Intset {

   private: 
	  Node * head;			  //A head pointer for the linked list

   public:
	  Intset();				  //The node constructor and
	  ~Intset();			  //destructor,
	  bool find(int key);	  //a function to find whether or not a node
							  //with the specified integer exists,
	  void insert(int key);	  //a function to insert a node in the list
							  //containing the specified integer,
	  void remove(int key);	  //a function to remove a node containing the
							  //specified data, and
	  void print(void);		  //a function to print the contents of the
							  //whole list.
};

#endif
