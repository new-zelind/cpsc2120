// Zach Lindler
// CPSC 2121
// Dr. Dean
// Lab 6, input.cpp

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Input{
   private:
	  struct Node{
		 int val;
		 Node* next;
		 Node(int _val){val = _val; next = NULL;}
		 Node(){val = -1; next = NULL;}
	  };
	  
	  Node** pTable;
	  Node** hTable;
	  int size;

   public:

	  Input(int _size);
	  ~Input();
	  void newTable(int _size);
	  bool find(int hash, Node** table);
	  int myHash(int num, int size);
	  void insert(int num, int hash, Node** table);
};

Input::Input(int _size){
   pTable = new Node*[size];
   hTable = new Node*[size];
   for(int i=0; i<size; i++){
	  pTable[i]=NULL;
	  hTable[i]=NULL;
   }

   size = _size;
}

Input::~Input(){
   for(int i=0; i<size; i++){
	  while(pTable[i] != NULL){
		 Node* temp = pTable[i];
		 pTable[i] = pTable[i]->next;
		 delete temp;
	  }
	  while(hTable[i] != NULL){
		 Node* temp = hTable[i];
		 hTable[i] = hTable[i]->next;
		 delete temp;
	  }
   }
   delete[] pTable;
   delete[] hTable;
}

void Input::newTable(int _size){
   ofstream out;
   out.open("input.txt");
   out << size << endl;

   size = _size;
   srand(time(NULL));
   for(int i=0; i<size; i++){
	  int newVal = rand() % (10*size);
	  int h = myHash(newVal, size);
	  while(find(newVal, pTable)){
		 newVal = rand() % (10*size);
		 h = myHash(newVal, size);
	  }
	  insert(newVal, h, pTable);

	  out << newVal <<" ";

	  newVal = rand() % (10*size);
	  h = myHash(newVal, size);
	  while(find(newVal, hTable)){
		 newVal = rand() % (10*size);
		 h = myHash(newVal, size);
	  }
	  insert(newVal, h, hTable);

	  out << newVal << endl;
   }

   out.close();
}

bool Input::find(int num, Node** table){
   int hash = myHash(num, size);
   Node* curr = table[hash];
   while(curr != NULL){
	  if(curr->val == num){
		 return true;
	  }
	  curr=curr->next;
   }
   return false;
}

int Input::myHash(int num, int size){
   unsigned int h = (2917 + (unsigned int)num) % size;
   return h;
}

void Input::insert(int num, int hash, Node** table){
   table[hash] = new Node(num);
}

int main(int argc, char* argv[]){
   if(argc != 2){
	  cout<<"Please provide an input size to be generated."<<endl;
	  return 1;
   }
   
   int size = atoi(argv[1]);
   Input I(size);

   I.newTable(size);
      
   return 0;
}
