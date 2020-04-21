// Zach Lindler
// CPSC 2120 Lab
// Dr. Dean
// Lab 7, main.cpp

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> Point;
typedef vector<Point> Vec;

int main(void){

   Point p;
   Vec v;
   double inX, inY;

   //declare the input file and read in each pair of points
   ifstream in;
   in.open("points.txt");
   while(in >> inX >> inY) {v.push_back(make_pair(inX, inY));}
   in.close();
   
   //sort the vector
   sort(v.begin(), v.end());

   //declare new variables for set s
   double d = 2.0;
   int i = 0;
   set<Point> s;
   set<Point>::iterator it;

   for(unsigned int j=0; j<v.size(); j++){
	  //while difference between point i and point j is less than d, iterate i forward
	  //and delete the ith element from the set.
	  while((v[j].first - v[i].first) > d){
		 s.erase(Point(v[i].second, v[i].first));
		 i++;
	  }

	  //then, insert pair j
	  s.insert(make_pair(v[j].second, v[j].first));

	  //
	  it = s.find(Point(v[j].second, v[j].first));
	  it++;
	  if(it == s.end()){
		 
	  }
	  it = s.find(Point(v[j].second, v[j].first));
	  it--;
	  if(it == s.begin()){
		 
	  }

   }


   return 0;
}
