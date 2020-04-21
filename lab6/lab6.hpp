// Zach Lindler
// CPSC 2121
// Dr. Dean
// Lab 6, lab6.hpp

#ifndef LAB6_H
#define LAB6_H

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Node{
   int location;
   int height;
   int order;
   int size;
   int before;
   int after;
   Node* left;
   Node* right;
   Node(int _location){
	  location = _location;
	  height = order = 0;
	  size = 1;
	  before = after = -1;
	  left = right = NULL;
   }
   Node(){
	  location = height = order = 0;
	  size = 1;
	  before = after = -1;
	  left = right = NULL;
   }
};

Node* insert(Node* T, int loc);
Node* find(Node* T, int h);
Node* join(Node* L, Node* R);
void split(Node* T, int loc, Node** L, Node** R);
Node* predFind(Node* T, int loc);
Node* succFind(Node* T, int loc);

#endif
