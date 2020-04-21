// Zach Lindler
// CPSC 2120
// Dr. Dean
// hw3, prune.cpp
// This is the pruning algorithm.

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

struct candy{
   double weight;
   double yum;
   double ratio;
   bool used;
};

struct bag{
   double weight;
   double taste;
};

vector<candy> store;
vector<bag> bags(4);
int best;
int curr;

bool comp(const candy&A, const candy&B){
   return A.ratio > B.ratio;
}

void doPrune(int num){
  if(curr > best){best = curr; return;}
  else if(num == 1){
    if(bags.at(1).weight + store.at(num).weight <= 2000){
      curr += store.at(num).yum;
 		  bags.at(1).taste += store.at(num).yum;
 		  bags.at(1).weight += store.at(num).weight;

      doPrune(num+1);

 		  curr -= store.at(num).yum;
 		  bags.at(1).taste -= store.at(num).yum;
 		  bags.at(1).weight -= store.at(num).weight;
    }
  }
  else{
    for(unsigned int i=0; i<bags.size(); i++){
      if(bags.at(i).weight + store.at(num).weight <= 2000){
        curr += store.at(num).yum;
   		  bags.at(0).taste += store.at(num).yum;
   		  bags.at(0).weight += store.at(num).weight;
   		  doPrune(num+1);

   		  curr -= store.at(num).yum;
   		  bags.at(0).taste -= store.at(num).yum;
   		  bags.at(0).weight -= store.at(num).weight;
      }
      else{continue;}
    }
  }

  doPrune(num+1);
}

void exhaustive(int num){
  if(num == 0){
    if(bags.at(0).weight + store.at(num).weight <= 2000){
      curr += store.at(num).yum;
 		  bags.at(0).taste += store.at(num).yum;
      bags.at(0).weight += store.at(num).weight;

      doPrune(num+1);

      curr -= store.at(num).yum;
 		  bags.at(0).taste -= store.at(num).yum;
 		  bags.at(0).weight -= store.at(num).weight;
    }
  }
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

  exhaustive(0);

  cout<<"Exhaustive: "<<best<<endl;

  return 0;
}
