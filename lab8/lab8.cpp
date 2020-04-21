// Zach Lindler
// CPSC 2120 Lab
// Dr. Dean
// Lab 8, lab8.cpp

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

//city struct
struct City{
   double xCoord, yCoord;
   int index;
};

//global array containing the information from the file - don't kill me, Ethan
City path[50];

//function that calculates the length of the tour
double calcLength(int* arr){
   double sum = 0;

   double x,y;

   for(int i=0; i<49; i++){
	  x = path[arr[i]].xCoord - path[arr[(i+1)%50]].xCoord;
	  y = path[arr[i]].yCoord - path[arr[(i+1)%50]].yCoord;
	  sum += sqrt((x*x) + (y*y));
   }

   x = path[arr[49]].xCoord - path[arr[0]].xCoord;
   y = path[arr[49]].xCoord - path[arr[0]].yCoord;
   sum += sqrt((x*x) + (y*y));

   return sum;
}

//function to shuffle a certain length of an array
void shuffle(int* arr, int i, int j){
   
   //i can't be greater than j, otherwise the function won't work.
   if(i >= j){return;}

   //simple swap function, swapping the integers in locations i and j.
   int temp;
   temp = arr[i];
   arr[i] = arr[j];
   arr[j] = temp;

   //recursive call to move along the array.
   shuffle(arr, i+1, j+1);


}

//function to refine the tour order
bool refineTour(int* arr){

   // double containing the initial length of the array passed in
   double oldLength = calcLength(arr);

   // iterate through each member of the array, where i is the beginning of the
   // section to be shuffled, and j is the end of said section.
   for(int i=0; i<50; i++){  
	  for(int j = i+2; j<50; j++){

		 //shuffle the array the first time;
		 shuffle(arr, i+1, j);

		 //if the length is less than the old length, keep going.
		 if(calcLength(arr) < oldLength){return true;}

		 //otherwise, shuffle it and try again.
		 shuffle(arr, i+1, j);
	  }
   }
   return false;
}

int main(void){

   //declare input file
   ifstream in;
   in.open("tsp_points.txt");

   //read the data into the path struct array.
   for(int i=0; i<50; i++){\
	  path[i].index = i;
	  in >> path[i].xCoord >> path[i].yCoord;
   }
   in.close();

   //double that holds the shortest length found so far.
   double bestLength = 100000;
   
   //two integer arrays that will hold the city numbers for each path.
   int bestPath[50];
   int currPath[50];
   
   //iterate 50 times
   for(int i=0; i<50; i++){

	  //seed random generation function
	  srand(time(NULL));

	  //shuffle the current path
	  for(int j=0; j<50; j++){
		 currPath[i]=i;
		 swap(currPath[i], currPath[rand() % (i+1)]);
	  }

	  // while refineTour returns true, keep refining the path.
	  while(refineTour(currPath));

	  // Once this is done, calculate the new length.
	  double newLength = calcLength(currPath);

	  // if this length is less than the previous lengths, store it as the new
	  // shortest/best length. Then, fill in the bestPath array with the data
	  // in the current path.
	  if(newLength < bestLength){
		 bestLength = newLength;
		 for(int j=0; j<50; j++){
			bestPath[i] = currPath[i];
		 }
	  }
   }
   
   // print the results
   cout << "The shortest length is: " << bestLength << endl;
   cout << "Path: ------------------" << endl;

   for(int i=0; i<50; i++){
	  cout << bestPath[i] << " ";
   }

   cout << endl;

   //done
   return 0;
}
