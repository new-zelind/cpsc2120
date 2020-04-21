#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
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
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert value v at rank r
Node *insert(Node *T, int v, int r)
{
   //if the tree is empty, make a new one.
  if(T == NULL){return new Node(v);}
   //calculate the rank of the root
  int rank_of_root = T->left ? T->left->size : 0;
   //if the root is less than the rank, insert to the left of the root; otherwise,
   //insert to the right, ignoring all the roots to the left.
  if(r <= rank_of_root){T->left = insert(T->left, v, r);}
  else T->right = insert(T->right, v, r - rank_of_root - 1);
   //fix the size, and return the T node.
  fix_size(T);
  return T;
}

// prints out the inorder traversal of T (i.e., the contents of T in sorted order)
void print_inorder(Node *T)
{
  if (T == NULL) return;
  print_inorder(T->left);
  cout << T->key << " ";
  print_inorder(T->right);
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=NULL && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  if (L == NULL) return R;
  if (R == NULL) return L;
  int random = rand() % (L->size + R->size);
  if (random < L->size) {
    // L stays root
    L->right = join(L->right, R);
    fix_size(L);
    return L;
  } else {
    // R stays root
    R->left = join(L, R->left);
    fix_size(R);
    return R;
  }
}

// Remove the node of rank r from T, returning a pointer to the resulting tree
Node *remove(Node *T, int r)
{
  assert(T!=NULL && r>=0 && r<T->size);
   //calculate the rank of the root
  int rank_of_root = T->left ? T->left->size :0;
  //if the root and rank are equal
  if(r == rank_of_root){
	  //identify the node to remove, join the left and right branches, and delete T.
	  Node *to_delete = T;
	  T = join(T->left, T->right);
	  delete to_delete;
	  return T;
  }
   //otherwise, if the rank of the root is greater than r, remove to the left.
  if(r <= rank_of_root){T->left = remove(T->left, r);}
   //if it's not, remove to the right.
  else{T->right = remove(T->right, r-rank_of_root-1);}
  fix_size(T);
  return T;
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
   int rank_of_root = T->left ? T->left->size : 0;
   //if the rank is greater than r, split to the left as normal
   if(r <= rank_of_root){
	  split(T->left, r, L, &T->left);
	  *R = T;
   }
   //if not, split to the right and ignore the left side of the split node.
   else{
	  split(T->right, r-rank_of_root-1, &T->right, R);
	  *L = T;
   }
   fix_size(T);
}

// insert value v at rank r
Node *insert_keep_balanced(Node *T, int v, int r)
{
  // if there's no tree, make one
  if(T == NULL){return new Node(v);}

  //calculate the rank of the root
  int rank_of_root = T->left ? T->left->size : 0;
  //function to place the node to keep the tree balanced
  if(rand() % (T->size + 1) == 0){
	  Node * new_root = new Node(v);
	  split(T, r, &new_root->left, &new_root->right);
	  fix_size(new_root);
	  return new_root;
  }
  //if the rank is greater than r, recurse on the left side.
  if(r <= rank_of_root){T->left = insert_keep_balanced(T->left, v, r);}

  //otherwise, recurse to the right and ignore the ranks on the left.
  else{T->right = insert_keep_balanced(T->right, v, r-rank_of_root-1);}
  fix_size(T);
  return T;
}

// Returns true if team x defeated team y
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  // Hash the pair (x,y) to an integer in {0,1} to see if x wins or loses
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n)
{
  Node *T = NULL;

  // start by inserting the first team
  T = insert_keep_balanced(T, 0, 0);

  // now insert the other teams...
  for (int i=1; i<n; i++) {
    // insert team i so the sequence encoded by the BST remains valid
    if (did_x_beat_y(i, select(T,0)->key))
	  T = insert_keep_balanced(T, i, 0); // can we insert at beginning?
    else{ 
      if (did_x_beat_y(select(T,T->size-1)->key, i))
		 T = insert_keep_balanced(T, i, T->size); // can we insert at end?
      else {
		 // nope -- now we need to binary search for correct position
		 int low = 0;			 //low boundary
		 int high = T->size-1;	 //high boundary
		 int mid;				 //middle of the search

		 //while the low and high boundaries aren't right next to each other
		 while(low != high-1){
			//calculate the middle of the search area
			mid = (low+high)/2;
			//if the first number is greater than the second one, the lower boundary
			//becomes the middle of the region.
			if(did_x_beat_y(select(T, mid)->key, i)){low=mid;}
			//otherwise, the high boundary becomes the middle of the region.
			else{high=mid;}
		 }
		 //then, insert the team.
		 T = insert_keep_balanced(T, i, high );
      }
	}
  }
  return T;
}

int main(void)
{
  Node *T = NULL;

  // test insert at beginning
  for (int i=0; i<5; i++){T = insert(T, i+1, 0);}
  
  cout << "Tree should contain 5 4 3 2 1\n";
  cout << "Inorder traversal:  "; print_inorder(T); cout << "\n\n";

  // test insert at end
  for (int i=5; i<10; i++){T = insert(T, i+1, T->size);}
  
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10\n";
  cout << "Inorder traversal:  "; print_inorder(T); cout << "\n\n";
  
  // test insert at middle
  for (int i=10; i<15; i++){T = insert(T, i+1, T->size/2);}
  
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10\n";
  cout << "Inorder traversal:  "; print_inorder(T); cout << "\n\n";

  // test remove
  cout << "Tree should contain 4 3 2 1 12 14 15 13 11 6 7 8 9 10\n";
  T = remove(T, 0);
  cout << "Inorder traversal:  "; print_inorder(T); cout << "\n\n";

  cout << "Tree should contain 4 3 2 1 12 14 15 13 11 6 7 8 9\n";
  T = remove(T, 13); 
  cout << "Inorder traversal:  "; print_inorder(T); cout << "\n\n";

  cout << "Tree should contain 4 3 2 1 12 14 13 11 6 7 8 9\n";
  T = remove(T, 6);  
  cout << "Inorder traversal:  "; print_inorder(T); cout << "\n\n";
  
  // once insert is working, the next step is to build the
  // insert_keep_balanced function -- to test this, just change
  // calls to insert above to insert_keep_balanced.

  // the next bit should run quickly even for very large N.
  // once you have it running correctly for N=10, try N=1 million
  int N = 1000000; 
  Node *S = order_n_teams(N);
  if (S == NULL || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    // if N is small, print team ordering ...
    if (N<=10) { cout << "Team ordering: "; print_inorder(S); cout << "\n"; } 
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
	cout << "Invalid sequence: team " << x->key << " (position " << i <<
	  ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}
