/* Zach Lindler
   CPSC 2120 - 003
   Lab 1, intset.cpp
   Dean */

#include <iostream>
#include <assert.h>
#include "intset.h"
using namespace std;

/*Default Constructor*/
Intset::Intset()
{
   //Create a new node pointing to NULL.
   head = NULL;
}

/*Destructor*/
Intset::~Intset()
{
   //Declare a temporary node and have it point to the first node in the list.
   Node * temp = head;

   //Destroy the specified node and fill the gap created in the list.
   while(head){
	  temp = temp -> next;
	  delete(head);
	  head = temp;
   }

   //Since the "head" node does not exist anymore, it needs to point to NULL.
   head=NULL;
}

/* Return true if key is in the set */
bool Intset::find(int key)
{
   //Declare the temporary iterator node.
   Node * temp = head;

   //While the temporary node doesn't point to NULL, check the data of the current
   //node to see if it equals the specified key. If it does, return true;
   //otherwise, iterate to the next one and repeat.
   while(temp != NULL){
	  if(temp->data==key){
		 return true;
	  }
	  else{
		 temp = temp->next;
	  }
   }
   
   //At this point, the key does not exist in the list, so return false.
   return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Intset::insert(int key)
{
   //Make sure the key exists in the list.
   assert(!find(key));
   
   //Declare a new node. Have the data equal the specified key, and have it point
   //to nothing. Delcare a temporary node and have it point to the beginning of
   //the list.
   Node* newNode = new Node;
   newNode->data = key;
   newNode->next = NULL;
   Node* temp = head;

   //If the head equals null, then the list doesn't exist. The head node is the
   //newly-created node.
   if(head == NULL){
	  head = newNode;
	  return;
   }

   //If the key is less than the data of the first node, have the new node point
   //to the first node.
   if(key < head->data){
	  newNode->next = head;
	  head = newNode;
	  return;
   }

   //While the temporary node isn't pointing to NULL,
   while(temp != NULL){

	  //check to make sure that the node afterwards isn't pointing to null. If it
	  //is, then have the last node point to the new node - it's now the end of
	  //the list.
	  if(temp->next == NULL){
		 temp->next = newNode;
		 newNode->next = NULL;
		 return;
	  }

	  //Then, check to see if the data is less than the next node's data. If so,
	  //The new node points to temp->next, and temp->next is the new node.
	  if(newNode->data < temp->next->data){
		newNode->next = temp->next;
		temp->next = newNode;
		return;
	 }

	 //Otherwise, iterate to the next node in the list.
	 else{
		temp = temp -> next;
	 }
   }

   temp->next = newNode;
   return;
}

/* Removes a key.  It is an error if key isn't in the set */
void Intset::remove(int key)
{

   //Make sure the key exists in the list.
   assert (find(key));

   //Declare two temporary node: one that points to the current node in the list,
   //and another that points to the previous one.
   Node * curr = head;
   Node * prev;

   //If the data of the head doesn't equal the key, initialize the two temporary
   //nodes.
   if(head->data != key){
	  curr = curr -> next;
	  prev = head;
   }

   //Otherwise, remove the head node.
   else{
	  head = head->next;
	  delete curr;
	  return;
   }

   //While the current node doesn't point to NULL, check to see if the current
   //node's data equals the key. If so, then remove the current node and have the
   //previous node point to the next node down the list to fill the gap.
   while(curr != NULL){
	 if(curr->data == key){		
		 prev->next = curr->next;
		 delete curr;
		 return;
	  }
	  
	  //Otherwise, iterate through the list.
	  else{
		 prev=curr;
		 curr = curr->next;
	  }
   }

   return;
}

void Intset::print(void)
{
   //Declare a temporary node to iterate through the list.
   Node * temp = head;

   //While the node doesn't point to NULL, print the current node's data, then
   //move down the list.
   while(temp != NULL){
		 cout << temp->data << endl;
		 temp = temp -> next;
   }
   return;
}
