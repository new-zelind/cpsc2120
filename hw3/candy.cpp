// Zach Lindler
// CPSC 2120
// Dr. Dean
// HW3, candy.cpp

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

int calcYum(vector<candy> &store, vector<candy> &bag1, vector<candy> &bag2, vector<candy> &bag3){
   int yumValue = 0;
   double bagWeight = 0.0;
   for(unsigned int i=0; i<bag1.size(); i++){
	  if(bagWeight + bag1.at(i).weight <= 2000){
		 bagWeight += bag1.at(i).weight;
		 yumValue += bag1.at(i).yum;
	  }
   }

   bagWeight = 0;

   for(unsigned int i=0; i<bag2.size(); i++){
	  if(bagWeight + bag2.at(i).weight <= 2000){
		 bagWeight += bag2.at(i).weight;
		 yumValue += bag2.at(i).yum;
	  }
   }

   bagWeight = 0;

   for(unsigned int i=0; i<bag3.size(); i++){
	  if(bagWeight + bag3.at(i).weight <= 2000){
		 bagWeight += bag3.at(i).weight;
		 yumValue += bag3.at(i).yum;
	  }
   }

   return yumValue;
}

void fill(vector<candy> &store, vector<candy> &bag1, vector<candy> &bag2, vector<candy> &bag3){
   double bag1Weight, bag2Weight, bag3Weight = 0;

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

void doRefine(vector<candy> &store){
   
   int best = 0;
   int oldYum, newYum, loopYum;
   vector<candy> bag1;
   vector<candy> bag2;
   vector<candy> bag3;
   vector<candy> stash;
   
   for(int T=0; T<1000; T++){
	  random_shuffle(store.begin(), store.end());
   
	  for(unsigned int i=0; i<store.size(); i++){
		 int bagNum = rand()%4 + 1;
		 if(bagNum == 1){bag1.push_back(store.at(i));}
		 if(bagNum == 2){bag2.push_back(store.at(i));}
		 if(bagNum == 3){bag3.push_back(store.at(i));}
		 if(bagNum == 4){stash.push_back(store.at(i));}

		 store.at(i).used = true;
	  }

	  best = calcYum(store, bag1, bag2, bag3);
	  bool again = true;
	  while(again == true){
		 for(unsigned int i=0; i<store.size(); i++){
			for(unsigned int j=0; j<store.size(); j++){
			   oldYum = calcYum(store, bag1, bag2, bag3);
			
			   bag1.clear();
			   bag2.clear();
			   bag3.clear();
			
			   reverse(store.begin(), store.end() + j + 1);

			   fill(store, bag1, bag2, bag3);

			   newYum = calcYum(store, bag1, bag2, bag3);
			   if(newYum > oldYum){
				  loopYum = newYum;
			   }
			}
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

   cout << "Refinement: " << best << endl;
}

int pruneBest = 0;

void doPrune(vector<candy> &store, unsigned int num){
   int curr = 0;

   vector<bag> bags(4);

   if(num == store.size()){
	  if(curr > pruneBest){
		 pruneBest = curr;
	  }
	  return;
   }

   else if(num == 0){
	  if(bags.at(0).weight + store.at(num).weight <= 2000){
		 curr += store.at(num).yum;
		 bags.at(0).taste += store.at(num).yum;
		 bags.at(0).weight += store.at(num).weight;
		 doPrune(store, num+1);

		 curr -= store.at(num).yum;
		 bags.at(0).taste -= store.at(num).yum;
		 bags.at(0).weight -= store.at(num).weight;
	  }
   }

   else if(num == 1){
	  if(bags.at(1).weight + store.at(num).weight <= 2000){
		 curr += store.at(num).yum;
		 bags.at(1).taste += store.at(num).yum;
		 bags.at(1).weight += store.at(num).weight;
		 doPrune(store, num+1);

		 curr -= store.at(num).yum;
		 bags.at(1).taste -= store.at(num).yum;
		 bags.at(1).weight -= store.at(num).weight;
	  }
   }

   else{
	  for(unsigned int i=0; i<store.size(); i++){
		 if(bags.at(i).weight + store.at(num).weight <= 2000){
			curr += store.at(num).yum;
			bags.at(i).taste += store.at(num).yum;
			bags.at(i).weight += store.at(num).weight;
			doPrune(store, num+1);

			curr -= store.at(num).yum;
			bags.at(i).taste -= store.at(num).yum;
			bags.at(i).weight -= store.at(num).weight;
		 }
		 else{continue;}
	  }
   }

   doPrune(store, num+1);
   

}

int main(void){

   vector<candy> store;

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
   doRefine(store);
   doPrune(store, 0);
   cout << "Exhaustive: " << pruneBest << endl;
      
   return 0;
}


