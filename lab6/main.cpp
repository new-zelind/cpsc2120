// Zach Lindler
// CPSC 2121
// Dr. Dean
// Lab 6, main.cpp

#include "lab6.hpp"

bool operator< (const Node& A, const Node& B);

int main(void){

   int numLines;
   ifstream infile("input.txt");
   infile>>numLines;
   Node* ptr = new Node[numLines];
   
   for(int i=0; i<numLines; i++){
	  infile >> ptr[i].location;
	  infile >> ptr[i].height;
	  ptr[i].order = i;
   }

   infile.close();

   sort(ptr, ptr+numLines);

   Node* T = NULL;
   Node* pred = NULL;
   Node* succ = NULL;

   for(int i=0; i<numLines; i++){
	  
	  pred = predFind(T, ptr[i].location);
	  if(pred != NULL){
		 ptr[i].before = (ptr[i].location) - (pred->location);
	  }

	  succ = succFind(T, ptr[i].location);
	  if(succ != NULL){
		 ptr[i].after = (succ->location) - (ptr[i].location);
	  }

	  T = insert(T, ptr[i].location);
   }

   cout<<"RESULTS:"<<endl;

   for(int i=0; i<numLines; i++){
	  ptr[i].height = ptr[i].order;
   }

   sort(ptr, ptr+numLines); 

   for(int i=numLines-1; i>=0; i--){
	  cout<<"Predecessor: "<<ptr[i].before<<endl;
	  cout<<"  Successor: "<<ptr[i].after<<endl<<endl;
   }

   return 0;
}
