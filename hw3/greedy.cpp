//Zach Lindler
//CPSC 2120
//Dr. Dean
//HW3, greedy.cpp
//this is the "greedy" sorting algorithm

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
using namespace std;

struct candy{
  double weight;
  double yum;
  double ratio;
  bool used;
};

struct bag{
  double weight;
  int tasty;
};

vector<candy> store;

bool comp(const candy&A, const candy&B){
   return A.ratio > B.ratio;
}

void doGreedy(vector<candy> &store){
   sort(store.begin(), store.end(), comp);
   vector<bag> bags(3);

   //iterator that will traverse the 'store' vector
   //int it=0;
   double maxTaste=0;

   for(int i=0; i<3; i++){
	  for(unsigned int j=0; j<store.size(); j++){
		 if((store.at(j).weight + bags.at(i).weight <= 2000) && store.at(j).used == false){
			bags.at(i).weight += store.at(j).weight;
			maxTaste += store.at(j).yum;
			store.at(j).used = true;
		 }
	  }
   }

   cout << "Greedy: " << maxTaste << endl;
}

int main(void){

  ifstream infile;
  infile.open("candy.txt");

  double newWeight, newYum;

  for(int i=0; i<16; i++){
   infile >> newWeight >> newYum;
   candy newCandy;
   newCandy.weight = newWeight;
   newCandy.yum = newYum;
   newCandy.ratio = newYum / newWeight;
   store.push_back(newCandy);
  }

  doGreedy(store);

  return 0;
}
