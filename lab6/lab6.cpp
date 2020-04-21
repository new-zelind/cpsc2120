// Zach Lindler
// CPSC 2121
// Dr. Dean
// Lab 6, lab6.cpp

#include "lab6.hpp"

Node* insert(Node* T, int loc){
   if(!T){return new Node(loc);} 
   if(rand() % T->size == 0){
	  Node* newNode = new Node(loc);
	  newNode->size += T->size;
	  split(T, loc, &newNode->left, &newNode->right);
	  return newNode;
   }
   if(loc < T->location){T->left = insert(T->left, loc);}
   else{T->right = insert(T->right, loc);}
   T->size += 1;
   return T;
}

Node* join(Node* L, Node* R){
   if(!L) return R;
   if(!R) return L;
   if(rand() % (L->size + R->size) < L->size){
	  L->size += R->size;
	  L->right = join(L->right, R);
	  return L;
   }
   else{
	  R->size += L->size;
	  R->left = join(L, R->left);
	  return R;
   }
}

void split(Node* T, int loc, Node** L, Node** R){
   if(!T){
	  *L = NULL;
	  *R = NULL;
	  return;
   }
   if(T->location > loc){
	  *R = T;
	  split(T->left, loc, L, &(T->left));
	  if(*L){(*R)->size -= (*L)->size;}
   }
   else{
	  *L = T;
	  split(T->right, loc, &(T->right), R);
	  if(*R){(*L)->size -= (*R)->size;}
   }
}

Node* predFind(Node* T, int loc){
   if(T == NULL){return NULL;}
   if(T->location == loc){return T;}
   if(loc < T->location){return predFind(T->left, loc);}
   else{
	  Node* temp = predFind(T->right, loc);
	  if(temp == NULL){return T;}
	  else{return temp;}
   }
}

Node* succFind(Node* T, int loc){
   if(T == NULL){return NULL;}
   if(T->location == loc){return T;}
   if(loc < T->location){
	  Node* temp = succFind(T->left, loc);
	  if(temp == NULL){return T;}
	  else{return temp;}
   }
   else{return succFind(T->right, loc);} 
}

bool operator< (const Node& A, const Node& B){
   return A.height > B.height;
}
