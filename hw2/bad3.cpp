// Zach Lindler
// CPSC 2120
// Dr. Dean
// HW2, bad3.cpp

#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = NULL; }
};

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left){T->size += T->left->size;}
  if (T->right){ T->size += T->right->size;}
}

// prints out the inorder traversal of T (i.e., the contents of T in sorted order)
void print(Node *T)
{
  if (T == NULL) return;
  print(T->left);
  cout << T->key << " ";
  print(T->right);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{
   //If T doesn't exist, create a new tree split.
   if(T == NULL){
	  *L = NULL;
	  *R = NULL;
	  return;
   }
   //otherwise, calculate the rank of the root.
   int rankOfRoot = T->left ? T->left->size : 0;
   //if the rank is greater than r, split to the left as normal
   if(r <= rankOfRoot){
	  split(T->left, r, L, &T->left);
	  *R = T;
   }
   //if not, split to the right and ignore the left side of the split node.
   else{
	  split(T->right, r-rankOfRoot-1, &T->right, R);
	  *L = T;
   }
   fix_size(T);
}

// insert value v at rank r
Node *insert(Node *T, int v, int r)
{
  // if there's no tree, make one
  if(T == NULL){return new Node(v);}

  //calculate the rank of the root
  int rankOfRoot = T->left ? T->left->size : 0;
  //function to place the node to keep the tree balanced
  if(rand() % (T->size + 1) == 0){
	  Node * new_root = new Node(v);
	  split(T, r, &new_root->left, &new_root->right);
	  fix_size(new_root);
	  return new_root;
  }
  //if the rank is greater than r, recurse on the left side.
  if(r <= rankOfRoot){T->left = insert(T->left, v, r);}

  //otherwise, recurse to the right and ignore the ranks on the left.
  else{T->right = insert(T->right, v, r-rankOfRoot-1);}
  fix_size(T);
  return T;
}

int main(int argc, char* argv[]){
   
   //command line argument checking
   if(argc != 2){
	  cout << "Usage: bad3 <input size>" << endl;
	  return 1;
   }

   //store the size of the input to be generated
   int size = atoi(argv[1]);

   //check to make sure the user didn't input a negative number
   if(size <= 0){
	  cout << "Invalid input size" <<endl;
	  return 1;
   }

   //print the size of the input to the file
   cout << size << endl;

   //declare a binary search tree to hold all the input
   Node* T = NULL;

   //insert each element in the new tree
   for(int i=0; i < size; i++){
	  T = insert(T, (size - i), 123456789 % (i + 1));
   }

   //print the contents of the array to the input file.
   print(T); 

   return 0;
}
