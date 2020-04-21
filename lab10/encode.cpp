// Zach Lindler
// CPSC 2120
// Dr. Dean
// lab 10, encode.cpp

#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
using namespace std;

struct Node{
   int address;
   char c;
   unordered_map<char, int> map;
   Node(int n){address = n;}
};

int main(void)
{
   vector<Node*> word;
   word.push_back(new Node(0));
   int i = 0;

   char c;
   
   do {
	  // read one character from standard input, whitespace included
	  c = cin.get();

	  if(word[i]->map.find(c) == word[i]->map.end()){
		 Node* newNode = new Node(word.size());
		 word.push_back(newNode);
		 
		 word[i]->map.insert({c, word.size()-1});

		 cout << i << " " << int(c) << endl;
		 i=0;
	  }
	  else{
		 i = word[i]->map[c];
	  }  

   } while (c != EOF);
   return 0;
}
