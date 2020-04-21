// Zach Lindler
// CPSC 2120
// Dr. Dean
// lab10, decoder.cpp

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
   int previous;
   int index;
   char c;
   Node(int n, char _c){previous = n; c = _c;}
};

void decode(int i, vector<Node*> &vec){
   if(i == 0){return;}
   decode(vec[i]->previous, vec);
   cout << vec[i]->c;
}

int main(int argc, char* argv[]){

   int prev, code;
   vector<Node*> text = {1,0};
   int i=0;
   char c;

   do{
	  cin >> prev;
	  cin >> code;
	  c = char(code);

	  Node* newNode = new Node(prev, c);
	  text.push_back(newNode);

	  decode(i, text);
	  i++;

   } while(code != -1);
   return 0;
}
