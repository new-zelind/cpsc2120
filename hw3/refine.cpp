// Zach Lindler
// CPSC 2120
// Dr. Dean
// hw3, refine.cpp
// This is the iterative refinement algorithm

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

vector<candy> store;    //the candy store
vector<candy> bag1;     //bag 1
vector<candy> bag2;     //bag 2
vector<candy> bag3;     //bag 3
vector<candy> stomach;  //candy not stored in a bag is assumed to be eaten.

int best, oldYum, newYum, loopYum;

bool comp(const candy&A, const candy&B){
   return A.ratio > B.ratio;
}

int calcYum(void){
   int yumValue = 0;

   for(unsigned int i=0; i<bag1.size(); i++){
		 yumValue += bag1.at(i).yum;
   }

   for(unsigned int i=0; i<bag2.size(); i++){
		 yumValue += bag2.at(i).yum;
   }

   for(unsigned int i=0; i<bag3.size(); i++){
		 yumValue += bag3.at(i).yum;
   }

   return yumValue;
}

void fill(void){
   int bag1Weight, bag2Weight, bag3Weight = 0;

   for(unsigned int i=0; i<store.size(); i++){
	  if((bag1Weight + store.at(i).weight <= 2000) && store.at(i).used == false){
		 bag1Weight += store.at(i).weight;
		 bag1.push_back(store.at(i));
		 store.at(i).used = true;
	  }

	  if((bag2Weight + store.at(i).weight <= 2000) && store.at(i).used == false){
		 bag2Weight += store.at(i).weight;
		 bag2.push_back(store.at(i));
		 store.at(i).used = true;
	  }

	  if((bag3Weight + store.at(i).weight <= 2000) && store.at(i).used == false){
		 bag3Weight += store.at(i).weight;
		 bag3.push_back(store.at(i));
		 store.at(i).used = true;
	  }
   }
}

void doRefine(void){
   for(int T=0; T<1000; T++){
	    random_shuffle(store.begin(), store.end());
      fill();
      best = calcYum();

	    bool again = true;
	    while(again == true){
          again = false;
		      for(unsigned int i=0; i<store.size(); i++){
			         //for(unsigned int j=0; j<store.size(); j++){
			              oldYum = calcYum();
                    bag1.clear();
			              bag2.clear();
			              bag3.clear();
                    reverse(store.begin(), store.end() + 1);
                    fill();
                    newYum = calcYum();
			              if(newYum > oldYum){
				                  loopYum = newYum;
			              }
			         //}
          }
          if(loopYum > best){best = loopYum; again = true;}
		      else{again = false;}
    }

	  for(unsigned int i=0; i<store.size(); i++){
		 store.at(i).used = false;
	  }

	  bag1.clear();
	  bag2.clear();
	  bag3.clear();
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

  doRefine();

  cout<<"Refinement: "<<best<<endl;

  return 0;
}
