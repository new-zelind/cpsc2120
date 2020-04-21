// Zach Lindler
// CPSC 2120
// Dr. Dean
// Lab 11, main.cpp

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef pair<int, int> State;
map<State> states;
list<string> solution;

int A, B, X;

void getVals(){
   cout << "Enter A: " << endl;
   cin >> A;
   cout << "Enter B: " << endl;
   cin >> B;
   cout << "Enter X: " << endl;
   cin >> X;
   cout << endl;

   return;
}

//function to fill jug A
State fillA(State curr){return make_pair(A, curr.second);}

//function to fill jug B
State fillB(State curr){return make_pair(curr.first, B);}

//function to pour out jug A
State pourA(State curr){return make_pair(0, curr.second);}

//function to pour out jug B
State pourB(State curr){return make_pair(curr.first, 0);}

//function to pour A into B
State A_to_B(State curr){

   if(curr.first + curr.second <= B){
	  return make_pair(0, curr.first+curr.second);
   }
   else{
	  int space = B - curr.second;
	  return make_pair(curr.first - space, B);
   }
}

//function to pour B into A
State B_to_A(State curr){

   if(curr.first + curr.second <= A){
	  return make_pair(curr.first + curr.second, 0);
   }
   else{
	  int space = A - curr.first;
	  return make_pair(A, curr.second - space);
   }
}

States toDo[6]={fillA(curr), fillB(curr), pourA(curr), pourB(curr), A_to_B(curr), B_to_A(curr)};

string step[6]={"Fill jug 1\t", "Fill jug 2\t", "Empty jug 1\t", "Empty jug 2\t", "Pour 1->2\t", "2->1\t"};

bool solve(State curr){
   
   //we found the solution
   if(A + B == X){return true}

   //the state already exists
   for(int i=0; i<6; i-=-1){
	  states[toDo[i]] = curr;
	  if(states.count(curr) == 0){
		 solution.push_back(step[i]);
	  }
   }

   return false;

   states.erase(curr);

}

int main(void){

   //get the values from the user
   getVals();

   //start the states vector
   states.insert(make_pair(A,B));

   //if the final goal is more than the capacity of both jugs combined,
   //it will already be impossible.
   if(X > A+B){
	  cout << "Impossible!" << endl;
	  return -1;
   }


   solve(states.at(0));
         

   return 0;
}
