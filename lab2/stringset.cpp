#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int myhash(string s, int table_size)
{
   unsigned int i, h = 0;
   for (i=0; i<s.length(); i++)
	  h = (h * 2917 + (unsigned int)s[i]) % table_size;
   return h;
}

Stringset::Stringset()
{
   size = 4; // initial size of table    
   table = new Node *[size]; // allocate table, initialize head ptrs all to NULL
   for (int i=0; i<size; i++) 
	  table[i] = NULL;
   num_elems = 0; 
}

Stringset::~Stringset()
{
   for (int i=0; i<size; i++) {
	  while (table[i] != NULL) {
		 Node *temp = table[i];
		 table[i] = table[i]->next;
		 delete temp;
	  }
   }
   delete[] table;
}

bool Stringset::find(string key)
{ 
   int h = myhash(key, size);
   Node *n = table[h];
   while (n != NULL) {
	  if (n->key == key){
		 return true;
	  }
	  n = n->next;
   }
   return false;
}

void Stringset::insert(string key)
{
   assert (!find(key));
   num_elems++;
   int oldH=myhash(key, size);
   int newH;

   //Check to see if the number of elements is equal to the size. If it is,
   if(num_elems == size) {

	  //Double `size` and make a new table, and initialize the pointers in
	  //the hash table to point to NULL.
	  int oldSize = size;
	  size = size * 2;
	  Node ** newTable = new Node * [size];
	  for(int i=0; i<size; i++){
		 newTable[i] = NULL;
	  }

	  //Iterate through the old table.
	  for(int j=0; j<oldSize; j++){

		 //Create two Node pointers: one that points to the hash table, and
		 //another that points to the linked lists in each bucket of the
		 //hash table.
		 Node * oldCurr = table[j];
		 Node * oldTemp = NULL;

		 //Whiel the table doesn't point to NULL,
		 while(oldCurr != NULL){

			//re-hash the key from the old table, and insert it into the
			//new table.
			newH = myhash(oldCurr->key, size);
			newTable[newH] = new Node(oldCurr->key, newTable[newH]);

			//iterate through the list in each hash bucket.
			oldTemp=oldCurr;
			oldCurr=oldCurr->next;

			//Delete the old member of the linked list
			delete oldTemp;
		 }
	  }

	  //After all that, delete the old table and re-assign the table
	  //pointer to the new table.
	  delete table;
	  table = newTable;
   }

   //Otherwise, insert the new key into the hash table.
   table[oldH] = new Node(key, table[oldH]);
}

void Stringset::remove(string key)
{  
   assert (find(key));
   num_elems--;
   
   //Determine the hash location of the provided key, then declare two node
   //pointers: one that points to the table bucket, and another that will
   //eventually lag behind the first pointer by one member.
   int h = myhash(key, size);
   Node * curr = table[h];
   Node * prev;

   //If the first member of the linked list doesn't need to be removed,
   //move the curr pointer to the next member of the linked list. Have the
   //prev pointer point to the hash table.
   if(curr->key != key){
	  curr=curr->next;
	  prev=table[h];
   }

   //Otherwise, have previous point to the beginning of the linked list,
   //and have current iterate to the next Node. Delete the first member of
   //the list, and have the hash table point to the next node.
   else{
	  prev = table[h];
	  curr = prev->next;
	  delete prev;
	  table[h] = curr;
	  return;
   }


   //While the current pointer doens't point to NULL,
   while(curr != NULL){

	  //If the key provided is equal to the current Node key, iterate
	  //through the list once more and delete the current node.
	  if(curr->key == key){
		 prev->next = curr->next;
		 delete curr;
		 return;
	  }

	  //Otherwise, move down the linked list.
	  else{
		 prev=curr;
		 curr=curr->next;
	  }
   }
   return;
}

void Stringset::print(void)
{
   //Create a pointer to the linked list.
   Node * curr;

   //Iterate though each bucket of the hash table.
   for(int i=0; i<size; i++){
	  curr = table[i];

	  //As long as the linked list node isn't pointing to NULL, print the
	  //key in the list and iterate to the next member.
	  while(curr!=NULL){
		 cout << curr->key << endl;
		 curr = curr->next;
	  }
   }
}
